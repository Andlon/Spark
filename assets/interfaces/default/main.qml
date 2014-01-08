import QtQuick 2.2

Item {

    ListView {
        anchors.fill: parent
        model: spark.launchers
        delegate: Text {
            color: "Black"
            font.pointSize: 50
            text: model.title
        }
    }

}
