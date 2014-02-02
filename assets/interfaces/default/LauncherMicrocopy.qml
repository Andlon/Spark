import QtQuick 2.2

BorderImage {
    source: "images/borderimage.png"
    border {
        left: 50
        right: 50
    }

    horizontalTileMode: BorderImage.Repeat
    verticalTileMode: BorderImage.Repeat

    Text {
        anchors {
            fill: parent
            leftMargin: parent.border.left + 5
            rightMargin: parent.border.right + 5
            topMargin: parent.border.top + 5
            bottomMargin: parent.border.bottom + 5
        }

        text: "Press to launch"
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        fontSizeMode: Text.Fit

        font.family: "Roboto"
        font.weight: Font.Light
        font.pointSize: 20
        color: "#999999"
    }
}
