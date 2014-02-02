import QtQuick 2.2
import Spark 0.1

FocusScope {
    id: root
    focus: true

    states: [
        State {
            when: spark.processState === Spark.NotRunning
            AnchorChanges { target: viewContainer; anchors.bottom: microcopy.top; anchors.top: undefined }
            AnchorChanges { target: microcopy; anchors.bottom: powerContainer.top; anchors.top: undefined }
            AnchorChanges { target: powerContainer; anchors.bottom: root.bottom; anchors.top: undefined }
            PropertyChanges { target: viewContainer; opacity: 1 }
            PropertyChanges { target: microcopy; opacity: 1 }
            PropertyChanges { target: powerContainer; opacity: 1 }
        },
        State {
            when: spark.processState !== Spark.NotRunning
            AnchorChanges { target: viewContainer; anchors.top: root.bottom; anchors.bottom: undefined }
            AnchorChanges { target: microcopy; anchors.top: viewContainer.bottom; anchors.bottom: undefined }
            AnchorChanges { target: powerContainer; anchors.top: microcopy.bottom; anchors.bottom: undefined }
            PropertyChanges { target: viewContainer; opacity: 0 }
            PropertyChanges { target: microcopy; opacity: 0 }
            PropertyChanges { target: powerContainer; opacity: 0 }
        }
    ]

    transitions: Transition {
        AnchorAnimation { duration: 250 }
        SmoothedAnimation { property: "opacity"; duration: 250; velocity: -1 }
    }

    Image {
        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop
        source: "testbackground.jpg"
    }

    Image {
        anchors.centerIn: parent
    }

    Pattern {
        id: viewContainer

        anchors {
            left: root.left
            right: root.right
            bottom: microcopy.top
            leftMargin: -border.width
            rightMargin: -border.width
        }

        pattern: "dark"
        border.color: "#292929"
        border.width: 1
        height: 125

        LauncherView {
            id: view
            anchors {
                top: parent.top
                bottom: parent.bottom
                topMargin: parent.border.width
                bottomMargin: parent.border.width
                horizontalCenter: parent.horizontalCenter
            }

            width: {
                switch (count)
                {
                case 0:
                    return 0
                case 1:
                    return parent.width / 3
                case 2:
                    return 2 * parent.width / 3
                default:
                    return parent.width
                }
            }

            delegateWidth: parent.width / 3

            focus: true
            model: spark.launchers

            onCountChanged: {
                currentIndex = 0
                positionViewAtBeginning()
            }

            KeyNavigation.down: powerMenu
        }
    }

    LauncherMicrocopy {
        id: microcopy
        anchors {
            bottom: powerContainer.top
            bottomMargin: microcopy.height
        }

        x: {
            var pos = 0
            if (view.currentIndex == view.count - 1)
                pos = view.width - view.delegateWidth
            else if (view.currentIndex != 0)
                pos = view.delegateWidth

            return view.x + pos
        }

        width: view.delegateWidth

        Behavior on x {
            SmoothedAnimation {
                duration: view.highlightMoveDuration
                velocity: -1
            }
        }
    }

    Pattern {
        id: powerContainer
        pattern: "dark"
        height: microcopy.height
        border.color: "#292929"
        border.width: 1

        anchors {
            bottom: parent.bottom
            left: parent.left
            right: parent.right
        }

        PowerMenu {
            id: powerMenu
            anchors.fill: parent
        }

        KeyNavigation.up: view
    }
}
