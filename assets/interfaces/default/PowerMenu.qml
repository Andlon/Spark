import QtQuick 2.2
import Navigation 0.1

FocusScope {
    id: root

    onActiveFocusChanged: if (activeFocus) updateFocus()

    property int selectionWidth: Math.max(exit.implicitWidth, shutdown.implicitWidth, restart.implicitWidth)
    property bool powerOptionsAvailable: spark.allowExit || shutdownAvailable() || restartAvailable()

    Row {
        anchors.centerIn: parent
        height: childrenRect.height
        spacing: 20

        Text {
            id: exit
            text: "Exit"
            width: root.selectionWidth
            visible: spark.allowExit

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
            visible: (spark.allowExit && shutdownAvailable()) || (spark.allowExit && restartAvailable())
            anchors {
                top: exit.top
                bottom: exit.bottom
            }
        }

        Text {
            id: shutdown
            text: "Shutdown"
            width: root.selectionWidth
            visible: shutdownAvailable()

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
            visible: restartAvailable() && shutdownAvailable()
            anchors {
                top: exit.top
                bottom: exit.bottom
            }
        }

        Text {
            id: restart
            text: "Restart"
            width: root.selectionWidth
            visible: restartAvailable()

            font.family: "Roboto"
            font.weight: Font.Light
            font.pointSize: 18
            color: activeFocus ? "#ffffff" : "#999999"
            horizontalAlignment: Text.AlignLeft

            KeyNavigation.left: shutdown

            Keys.forwardTo: Nav { onOk: power.reboot() }
        }
    }

    function shutdownAvailable()
    {
        return spark.allowShutdown && power.canShutdown
    }

    function restartAvailable()
    {
        return spark.allowRestart && power.canReboot
    }

    function updateFocus()
    {
        // Prioritized list of focus candidates, depending on availability
        if (shutdownAvailable())
            shutdown.focus = true
        else if (restartAvailable())
            restart.focus = true
        else if (spark.allowExit)
            exit.focus = true
        else
            root.focus = true
    }
}
