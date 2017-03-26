import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import com.example.example 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Qt Push Notifications Demo")

    Rectangle{
        anchors.fill: parent
        Text{
            id: introduction
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 20
            text: "This example demonstrates how to implement push notifications on " + Qt.platform.os;
            width: parent.width - 20
            wrapMode: Text.WordWrap
        }

        Text{
            id: registrationToken
            anchors.top: introduction.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 20
            wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            width: parent.width - 20
            text: Qt.platform.os === "ios" ?
                      ("Token: " + PushNotificationRegistrationTokenHandler.apnsRegistrationToken)
                    : ("Token: " + PushNotificationRegistrationTokenHandler.gcmRegistrationToken)
        }

        Text{
            id: info
            anchors.top: registrationToken.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 30
            wrapMode: Text.WordWrap
            width: parent.width - 20
            text: "Did you find this example useful? If so, it would really mean a lot to me "
                  + " if you tell your friends who are into fitness about gympulsr (https://www.gympulsr.com)."
                  + " Gympulsr is a hobby project of mine that connects fitness enthusiasts around the world with each other"
                  + " (and btw. it's also written in Qt. ;-)). Thanks a lot!"
        }
    }
}
