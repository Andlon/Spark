import QtQuick 2.2
import Navigation 0.1

FocusScope {
    id: root

    onActiveFocusChanged: if (activeFocus) shutdown.focus = true

    property int selectionWidth: Math.max(exit.implicitWidth, shutdown.implicitWidth, restart.implicitWidth)

    Row {
        anchors.centerIn: parent
        height: childrenRect.height
        spacing: 20

        Text {
            id: exit
            text: "Exit"
            width: root.selectionWidth

            font.family: "Roboto"
            font.weight: Font.Light
            font.pointSize: 18
            color: activeFocus ? "#ffffff" : "#999999"
            horizontalAlignment: Text.AlignRight

            KeyNavigation.right: shutdown

            Keys.forwardTo: Nav { onOk: Qt.quit() }
        }

        Rectangle {
            width: 1
            color: "#999999"
            anchors {
                top: exit.top
                bottom: exit.bottom
            }
        }

        Text {
            id: shutdown
            text: "Shutdown"
            width: root.selectionWidth

            font.family: "Roboto"
            font.weight: Font.Light
            font.pointSize: 18
            color: activeFocus ? "#ffffff" : "#999999"

            KeyNavigation.left: exit
            KeyNavigation.right: restart

            Keys.forwardTo: Nav { onOk: power.shutdown() }
        }

        Rectangle {
            width: 1
            color: "#999999"
            anchors {
                top: exit.top
                bottom: exit.bottom
            }
        }

        Text {
            id: restart
            text: "Restart"
            width: root.selectionWidth

            font.family: "Roboto"
            font.weight: Font.Light
            font.pointSize: 18
            color: activeFocus ? "#ffffff" : "#999999"
            horizontalAlignment: Text.AlignLeft

            KeyNavigation.left: shutdown

            Keys.forwardTo: Nav { onOk: power.reboot() }
        }
    }
}
