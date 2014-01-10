import QtQuick 2.2

FocusScope {
    id: root
    focus: true

    Image {
        anchors.fill: parent
        fillMode: Image.PreserveAspectCrop
        source: "testbackground.jpg"
    }

    Pattern {
        anchors {
            bottom: root.bottom
            left: root.left
            right: root.right
            bottomMargin: root.height * 0.08
            leftMargin: -border.width
            rightMargin: -border.width
        }

        pattern: "dark"
        border.color: "#292929"
        border.width: 1
        height: 150

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
}
