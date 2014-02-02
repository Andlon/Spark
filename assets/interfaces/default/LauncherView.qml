import QtQuick 2.2
import Navigation 0.1

ListView {
    id: view
    orientation: ListView.Horizontal

    boundsBehavior: Flickable.StopAtBounds
    highlightFollowsCurrentItem: true
    highlightMoveDuration: 250
    highlightMoveVelocity: -1
    highlightRangeMode: ListView.ApplyRange
    highlightResizeDuration: 0
    highlightResizeVelocity: -1
    preferredHighlightBegin: view.width / 3
    preferredHighlightEnd: 2 * view.width / 3
    highlight: Rectangle {
        //color: "#e9c329"
        color: "#ffae00"
    }

    property int delegateWidth: view.width / 3

    delegate: Item {
        id: delegateRoot
        height: view.height
        width: view.delegateWidth

        property int launcherId: model.id

        Rectangle {
            anchors.fill: delegateRoot
            parent: view.contentItem
            z: -1
            color: "transparent"
            border.width: 1
            border.color: "#292929"
        }

        Column {
            anchors {
                left: parent.left
                right: parent.right
                verticalCenter: parent.verticalCenter
            }
            clip: true

            height: childrenRect.height

            Text {
                id: title
                anchors {
                    left: parent.left
                    right: parent.right
                    margins: 20
                }

                clip: true

                text: model.title
                font: {
                    var fontProperties = {}
                    fontProperties.family = robotoThin.name
                    fontProperties.weight = Font.Light
                    fontProperties.pointSize = 40

                    return Qt.font(fontProperties)
                }

                horizontalAlignment: Text.AlignHCenter
                color: parent.parent.ListView.isCurrentItem ? "#151515" : "#ffffff"

                Behavior on color {
                    ColorAnimation {
                        duration: 250
                        easing.type: Easing.InOutQuad
                    }
                }
            }

            Text {
                id: usage
                anchors {
                    left: parent.left
                    right: parent.right
                }

                text: model.usage
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                fontSizeMode: Text.Fit

                font.family: "Roboto"
                font.weight: Font.Light
                font.pointSize: 18

                color: parent.parent.ListView.isCurrentItem ? "#353535" : "#999999"

                Behavior on color {
                    ColorAnimation {
                        duration: 250
                        easing.type: Easing.InOutQuad
                    }
                }
            }


        }


    }

    FontLoader {
        id: robotoThin
        source: "fonts/Roboto-Thin.ttf"
    }

    Keys.forwardTo: Nav {
        onRight: view.incrementCurrentIndex()
        onLeft: view.decrementCurrentIndex()
        onOk: if (view.currentItem) spark.launch(view.currentItem.launcherId)
    }
}
