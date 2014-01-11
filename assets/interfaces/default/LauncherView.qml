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
        color: "#e9c329"
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
        Text {
            id: title
            anchors.fill: parent
            anchors.margins: 20
            clip: true

            text: model.title
            font: {
                var fontProperties = {}
                fontProperties.family = "Roboto"
                fontProperties.weight = Font.Light
                fontProperties.pointSize = 35

                return Qt.font(fontProperties)
            }
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
            color: parent.ListView.isCurrentItem ? "#151515" : "#ffffff"

            Behavior on color {
                SmoothedAnimation {
                    duration: 250
                    velocity: -1
                }
            }
        }
    }

    Keys.forwardTo: Nav {
        onRight: view.incrementCurrentIndex()
        onLeft: view.decrementCurrentIndex()
        onOk: if (view.currentItem) console.log(spark.launch(view.currentItem.launcherId))
    }
}
