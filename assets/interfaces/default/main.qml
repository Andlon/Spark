import QtQuick 2.2
import Spark 0.1

FocusScope {
    id: root
    focus: true

    states: [
        State {
            when: spark.processState === Spark.NotRunning
            AnchorChanges { target: viewContainer; anchors.top: undefined; anchors.bottom: microcopy.top }
            AnchorChanges { target: microcopy; anchors.bottom: root.bottom; anchors.top: undefined }
            PropertyChanges { target: viewContainer; opacity: 1 }
            PropertyChanges { target: microcopy; opacity: 1 }
        },
        State {
            when: spark.processState !== Spark.NotRunning
            AnchorChanges { target: viewContainer; anchors.top: root.bottom; anchors.bottom: undefined }
            AnchorChanges { target: microcopy; anchors.top: viewContainer.bottom; anchors.bottom: undefined }
            PropertyChanges { target: viewContainer; opacity: 0 }
            PropertyChanges { target: microcopy; opacity: 0 }
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
        }
    }

    LauncherMicrocopy {
        id: microcopy
        anchors {
            bottom: root.bottom
            bottomMargin: root.height * 0.03
        }

        x : view.x + view.currentIndex * view.delegateWidth
        width: view.delegateWidth

        Behavior on x {
            SmoothedAnimation {
                duration: view.highlightMoveDuration
                velocity: -1
            }
        }
    }
}
