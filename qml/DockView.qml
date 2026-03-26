import QtQuick
import QtQuick.Window
import QtQuick.Layouts
import QtQuick.Controls as QQC2
import org.kde.kirigami as Kirigami
import org.kde.taskmanager as TaskManager

Window {
    id: root

    flags: Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint | Qt.WA_TranslucentBackground
    color: "transparent"

    width: shelf.width + 40
    height: shelfConfig.dockHeight
    visible: true

    // --- Task Manager Model ---
    TaskManager.TasksModel {
        id: tasksModel
        sortMode: TaskManager.TasksModel.SortManual
        groupMode: TaskManager.TasksModel.GroupDisabled
        filterByVirtualDesktop: true
        filterByActivity: true
        filterByScreen: false
        launchInPlace: true
        launcherList: shelfConfig.pinnedLaunchers
    }

    TaskManager.VirtualDesktopInfo { id: virtualDesktopInfo }
    TaskManager.ActivityInfo { id: activityInfo }

    // --- Mouse tracking state ---
    property real mouseXPos: -10000
    property bool mouseInDock: false

    // --- Parabolic zoom calculation (cosine, like macOS) ---
    function calcScale(iconCenterX: real): real {
        if (!mouseInDock) return 1.0;
        var distance = Math.abs(mouseXPos - iconCenterX);
        var spread = shelfConfig.zoomRange;
        if (distance >= spread) return 1.0;
        var factor = (shelfConfig.maxZoom - 1.0) * 0.5
                     * (1.0 + Math.cos(Math.PI * distance / spread));
        return 1.0 + factor;
    }

    // --- Glass shelf background ---
    Rectangle {
        id: shelfBg
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 6
        width: shelf.width + 24
        height: shelfConfig.iconSize + 24
        radius: 16
        color: Qt.rgba(0.1, 0.1, 0.1, 0.55)
        border.width: 1
        border.color: Qt.rgba(1, 1, 1, 0.12)

        // Top highlight for glass depth
        Rectangle {
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.margins: 1
            height: parent.height * 0.4
            radius: 15
            gradient: Gradient {
                GradientStop { position: 0.0; color: Qt.rgba(1, 1, 1, 0.08) }
                GradientStop { position: 1.0; color: Qt.rgba(1, 1, 1, 0.0) }
            }
        }

        Behavior on width {
            NumberAnimation { duration: 200; easing.type: Easing.OutCubic }
        }
    }

    // --- Dock mouse area (tracks mouse across the full dock) ---
    MouseArea {
        id: dockMouseArea
        anchors.fill: parent
        hoverEnabled: true
        acceptedButtons: Qt.NoButton
        propagateComposedEvents: true

        onPositionChanged: function(mouse) {
            root.mouseXPos = mapToItem(shelf, mouse.x, mouse.y).x;
            root.mouseInDock = true;
        }

        onExited: {
            root.mouseInDock = false;
            root.mouseXPos = -10000;
        }
    }

    // --- Icon row ---
    Row {
        id: shelf
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 12
        spacing: shelfConfig.iconSpacing
        z: 10

        Repeater {
            model: tasksModel

            delegate: Item {
                id: dockItem

                required property var model
                required property int index

                property real iconCenterLocal: x + width / 2
                property real currentScale: root.calcScale(iconCenterLocal)

                width: shelfConfig.iconSize
                height: shelfConfig.iconSize * shelfConfig.maxZoom + 20

                // --- The icon ---
                Kirigami.Icon {
                    id: iconImage
                    source: dockItem.model.decoration
                    width: shelfConfig.iconSize * animScale
                    height: width
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: dotIndicator.height + 4

                    property real animScale: dockItem.currentScale
                    Behavior on animScale {
                        NumberAnimation {
                            duration: 120
                            easing.type: Easing.OutCubic
                        }
                    }
                }

                // --- Bounce animation on launch ---
                SequentialAnimation {
                    id: bounceAnim
                    NumberAnimation {
                        target: iconImage
                        property: "anchors.bottomMargin"
                        to: dotIndicator.height + 4 + 28
                        duration: 180
                        easing.type: Easing.OutQuad
                    }
                    NumberAnimation {
                        target: iconImage
                        property: "anchors.bottomMargin"
                        to: dotIndicator.height + 4
                        duration: 300
                        easing.type: Easing.OutBounce
                    }
                }

                // --- Running indicator dot ---
                Rectangle {
                    id: dotIndicator
                    visible: !dockItem.model.IsLauncher
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.bottom: parent.bottom
                    width: 5
                    height: 5
                    radius: 2.5
                    color: dockItem.model.IsActive
                           ? Kirigami.Theme.highlightColor
                           : Kirigami.Theme.textColor
                    opacity: dockItem.model.IsActive ? 1.0 : 0.4
                }

                // --- Click / hover handling ---
                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    acceptedButtons: Qt.LeftButton | Qt.MiddleButton | Qt.RightButton

                    onPositionChanged: function(mouse) {
                        var mapped = mapToItem(shelf, mouse.x, mouse.y);
                        root.mouseXPos = mapped.x;
                        root.mouseInDock = true;
                    }

                    onEntered: root.mouseInDock = true

                    onClicked: function(mouse) {
                        if (mouse.button === Qt.LeftButton) {
                            bounceAnim.start();
                            tasksModel.requestActivate(
                                tasksModel.makeModelIndex(dockItem.index));
                        } else if (mouse.button === Qt.MiddleButton) {
                            tasksModel.requestNewInstance(
                                tasksModel.makeModelIndex(dockItem.index));
                        } else if (mouse.button === Qt.RightButton) {
                            // TODO: context menu (pin/unpin, close, etc.)
                        }
                    }

                    QQC2.ToolTip.visible: containsMouse
                    QQC2.ToolTip.text: dockItem.model.display || ""
                    QQC2.ToolTip.delay: 400
                }
            }
        }
    }
}
