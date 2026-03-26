import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls as QQC2
import org.kde.kirigami as Kirigami
import org.kde.taskmanager as TaskManager

Window {
    id: root

    flags: Qt.FramelessWindowHint
    color: "transparent"
    visible: false
    height: shelfConfig.dockHeight

    Timer {
        interval: 100
        running: true
        onTriggered: root.visible = true
    }

    TaskManager.TasksModel {
        id: tasksModel
        sortMode: TaskManager.TasksModel.SortManual
        groupMode: TaskManager.TasksModel.GroupDisabled
        filterByVirtualDesktop: true
        filterByActivity: true
        filterByScreen: false
        launchInPlace: true
    }

    property real mouseXPos: -10000
    property bool mouseInDock: false
    readonly property int iconSize: shelfConfig.iconSize
    readonly property int cellWidth: iconSize + shelfConfig.iconSpacing

    function calcScale(iconCenterX: real): real {
        if (!mouseInDock) return 1.0;
        var distance = Math.abs(mouseXPos - iconCenterX);
        var spread = shelfConfig.zoomRange;
        if (distance >= spread) return 1.0;
        return 1.0 + (shelfConfig.maxZoom - 1.0) * 0.5
                    * (1.0 + Math.cos(Math.PI * distance / spread));
    }

    // --- Glass shelf background ---
    Rectangle {
        id: shelfBg
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 8
        width: shelfRow.width + 24
        height: iconSize + 24
        radius: 18
        color: Qt.rgba(0.08, 0.08, 0.12, 0.6)
        border.width: 1
        border.color: Qt.rgba(1, 1, 1, 0.12)

        Rectangle {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.margins: 1
            height: parent.height * 0.45
            radius: 17
            gradient: Gradient {
                GradientStop { position: 0.0; color: Qt.rgba(1, 1, 1, 0.09) }
                GradientStop { position: 1.0; color: "transparent" }
            }
        }

        Behavior on width {
            NumberAnimation { duration: 250; easing.type: Easing.OutCubic }
        }
    }

    // --- Global mouse tracking ---
    MouseArea {
        anchors.fill: parent
        hoverEnabled: true
        acceptedButtons: Qt.NoButton
        propagateComposedEvents: true

        onPositionChanged: function(mouse) {
            root.mouseXPos = mapToItem(shelfRow, mouse.x, mouse.y).x;
            root.mouseInDock = true;
        }

        onExited: {
            root.mouseInDock = false;
            root.mouseXPos = -10000;
        }
    }

    // --- Icon row (fixed-width cells, no reflow) ---
    Row {
        id: shelfRow
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 14
        spacing: 0
        z: 10

        ShelfIcon {
            iconSource: "firefox"
            tooltipText: "firefox"
            onIconClicked: shelfConfig.launch("firefox")
        }

        Repeater {
            model: tasksModel
            delegate: ShelfIcon {
                required property var model
                required property int index
                iconSource: model.decoration
                tooltipText: model.display || ""
                visible: {
                    var name = (model.display || "").toLowerCase();
                    return name.indexOf("firefox") === -1
                        && name.indexOf("konsole") === -1
                        && !model.IsLauncher;
                }
                showDot: !model.IsLauncher
                isActive: model.IsActive
                onIconClicked: tasksModel.requestActivate(tasksModel.makeModelIndex(index))
            }
        }

        ShelfIcon {
            iconSource: "start-here-archlinux"
            tooltipText: "menu"
            onIconClicked: shelfConfig.launch("plasmawindowed org.kde.plasma.kickoff")
        }

        ShelfIcon {
            iconSource: "utilities-terminal"
            tooltipText: "konsole"
            onIconClicked: shelfConfig.launch("konsole")
        }
    }

    // --- Shelf icon: fixed-width cell, icon scales inside without reflowing ---
    component ShelfIcon: Item {
        id: cell

        property string iconSource
        property string tooltipText
        property bool showDot: false
        property bool isActive: false
        signal iconClicked()

        // Fixed cell width — never changes, prevents jitter
        width: cellWidth
        height: iconSize * shelfConfig.maxZoom + 20

        // Scale is based on this cell's fixed center position
        readonly property real cellCenter: x + cellWidth / 2
        property real currentScale: root.calcScale(cellCenter)

        Kirigami.Icon {
            id: img
            source: cell.iconSource
            // Only the image scales, not the cell
            width: iconSize * cell.currentScale
            height: width
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: cell.showDot ? 12 : 4

            // Smooth animation — no Behavior, direct binding for zero-lag tracking
        }

        // Bounce on click
        SequentialAnimation {
            id: bounce
            NumberAnimation {
                target: img; property: "anchors.bottomMargin"
                to: (cell.showDot ? 12 : 4) + 28
                duration: 180; easing.type: Easing.OutQuad
            }
            NumberAnimation {
                target: img; property: "anchors.bottomMargin"
                to: cell.showDot ? 12 : 4
                duration: 300; easing.type: Easing.OutBounce
            }
        }

        // Running indicator dot
        Rectangle {
            visible: cell.showDot
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 2
            width: 5; height: 5; radius: 2.5
            color: cell.isActive ? Kirigami.Theme.highlightColor : Kirigami.Theme.textColor
            opacity: cell.isActive ? 1.0 : 0.4
        }

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true
            acceptedButtons: Qt.LeftButton

            onPositionChanged: function(mouse) {
                root.mouseXPos = mapToItem(shelfRow, mouse.x, mouse.y).x;
                root.mouseInDock = true;
            }

            onEntered: root.mouseInDock = true

            onClicked: {
                bounce.start();
                cell.iconClicked();
            }

            QQC2.ToolTip.visible: containsMouse
            QQC2.ToolTip.text: cell.tooltipText
            QQC2.ToolTip.delay: 400
        }
    }
}
