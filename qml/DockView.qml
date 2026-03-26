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

    readonly property int iconSize: shelfConfig.iconSize
    readonly property int cellWidth: iconSize + shelfConfig.iconSpacing

    property real mouseLocalX: -10000
    property bool hovering: false
    property bool dockVisible: true

    // --- Auto-hide timer: hide after 1.5s of no mouse activity ---
    Timer {
        id: hideTimer
        interval: 1500
        onTriggered: {
            if (!root.hovering) {
                root.dockVisible = false;
            }
        }
    }

    // --- When mouse leaves, start the hide countdown ---
    onHoveringChanged: {
        if (hovering) {
            hideTimer.stop();
            dockVisible = true;
        } else {
            hideTimer.restart();
        }
    }

    // --- Dock content container that slides up/down ---
    Item {
        id: dockContainer
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        width: parent.width
        height: parent.height

        // Slide off bottom when hidden
        transform: Translate {
            y: root.dockVisible ? 0 : shelfConfig.dockHeight + 10

            Behavior on y {
                NumberAnimation {
                    duration: 300
                    easing.type: root.dockVisible ? Easing.OutCubic : Easing.InCubic
                }
            }
        }

        // Fade out when hidden
        opacity: root.dockVisible ? 1.0 : 0.0
        Behavior on opacity {
            NumberAnimation { duration: 250 }
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

        // --- Icon row ---
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
                id: runningAppsRepeater
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
    }

    // --- Full-width mouse sensor at the very bottom to bring dock back ---
    MouseArea {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        height: parent.height
        hoverEnabled: true
        acceptedButtons: Qt.NoButton
        propagateComposedEvents: true

        onPositionChanged: function(mouse) {
            root.mouseLocalX = Math.round(mapToItem(shelfRow, mouse.x, mouse.y).x);
            root.hovering = true;
        }

        onExited: {
            root.hovering = false;
        }
    }

    // --- Shelf icon ---
    component ShelfIcon: Item {
        id: cell

        property string iconSource
        property string tooltipText
        property bool showDot: false
        property bool isActive: false
        signal iconClicked()

        width: cellWidth
        height: iconSize * shelfConfig.maxZoom + 20

        layer.enabled: false
        readonly property int centerPx: Math.round(x) + Math.round(cellWidth * 0.5)
        readonly property real dist: Math.abs(root.mouseLocalX - centerPx)
        readonly property real zoomRange: shelfConfig.zoomRange
        readonly property real currentScale: {
            if (!root.hovering || dist >= zoomRange) return 1.0;
            return 1.0 + (shelfConfig.maxZoom - 1.0) * 0.5
                       * (1.0 + Math.cos(3.14159265 * dist / zoomRange));
        }

        Kirigami.Icon {
            id: img
            source: cell.iconSource
            width: Math.round(iconSize * cell.currentScale)
            height: width
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.bottom: parent.bottom
            anchors.bottomMargin: cell.showDot ? 12 : 4
            smooth: true
            antialiasing: true
        }

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
            acceptedButtons: Qt.LeftButton | Qt.RightButton

            onPositionChanged: function(mouse) {
                root.mouseLocalX = Math.round(mapToItem(shelfRow, mouse.x, mouse.y).x);
                root.hovering = true;
            }

            onEntered: root.hovering = true

            onClicked: function(mouse) {
                if (mouse.button === Qt.LeftButton) {
                    bounce.start();
                    cell.iconClicked();
                } else if (mouse.button === Qt.RightButton) {
                    contextMenu.cellName = cell.tooltipText;
                    // Position above the shelf
                    var globalPos = mapToItem(root.contentItem, cell.width / 2, 0);
                    contextMenu.x = globalPos.x - contextMenu.width / 2;
                    contextMenu.y = globalPos.y - contextMenu.height - 20;
                    contextMenu.open();
                }
            }

            QQC2.ToolTip.visible: containsMouse
            QQC2.ToolTip.text: cell.tooltipText
            QQC2.ToolTip.delay: 400
        }
    }

    // --- Right-click context menu ---
    QQC2.Menu {
        id: contextMenu
        property string cellName: ""

        QQC2.MenuItem {
            text: "remove from shelf"
            onTriggered: console.log("Remove: " + contextMenu.cellName)
        }
        QQC2.MenuSeparator {}
        QQC2.MenuItem {
            text: "add application..."
            onTriggered: shelfConfig.launch("plasmawindowed org.kde.plasma.kickoff")
        }
        QQC2.MenuSeparator {}
        QQC2.MenuItem {
            text: "shelf settings"
            onTriggered: console.log("Settings")
        }
    }
}
