import QtQuick 2.2
import Navigation 0.1

FocusScope {
    id: root

    onActiveFocusChanged: if (activeFocus) shutdown.focus = true

    property int selectionWidth: Math.max(suspend.implicitWidth, shutdown.implicitWidth, restart.implicitWidth)

    Row {
        anchors.centerIn: parent
        height: childrenRect.height
        spacing: 20

        Text {
            id: suspend
            text: "Suspend"
            width: root.selectionWidth

            font.family: "Roboto"
            font.weight: Font.Light
            font.pointSize: 18
            color: activeFocus ? "#ffffff" : "#999999"

            KeyNavigation.right: shutdown
        }

        Rectangle {
            width: 1
            color: "#999999"
            anchors {
                top: suspend.top
                bottom: suspend.bottom
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

            KeyNavigation.left: suspend
            KeyNavigation.right: restart
        }

        Rectangle {
            width: 1
            color: "#999999"
            anchors {
                top: suspend.top
                bottom: suspend.bottom
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

            KeyNavigation.left: shutdown
        }
    }
}
