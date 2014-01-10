import QtQuick 2.0

Image {
    property string pattern
    property alias border: borders.border

    fillMode: Image.Tile

    Rectangle {
        id: borders
        color: "transparent"
        anchors.fill: parent
    }

    source: {
        switch (pattern)
        {
        case "dark":
            return "images/dark.png"
        case "medium":
            return "images/medium.png"
        case "light":
            return "images/light.png"

        default:
            return ""
        }
    }
}
