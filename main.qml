import QtQuick
import QtQuick.Controls.Material

ApplicationWindow {
    width: 960
    height: 640
    visible: true
    title: qsTr("Hello World")

    Screen01 {
        anchors.fill: parent
        clip: true
    }
}
