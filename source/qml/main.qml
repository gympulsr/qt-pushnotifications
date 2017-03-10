import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Qt Push Notifications Demo")

    Rectangle{
        anchors.fill: parent
        Text{
            id: text
            text: "This app demonstrates how to implement push notifications on " + Qt.platform.os;
            width: parent.width
            wrapMode: Text.WordWrap
        }
    }
}
