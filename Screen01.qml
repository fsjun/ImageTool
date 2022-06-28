/*
This is a UI file (.ui.qml) that is intended to be edited in Qt Design Studio only.
It is supposed to be strictly declarative and only uses a subset of QML. If you edit
this file manually, you might introduce QML code that is not supported by Qt Design Studio.
Check out https://doc.qt.io/qtcreator/creator-quick-ui-forms.html for details on .ui.qml files.
*/

import QtQuick
import QtQuick.Controls
import Qt.labs.platform
import com.image

Pane {
    property string title: "图片浏览器"
    padding: 2

    Pane {
        id: header
        height: 40
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right

        Text {
            width: 120
            height: 40
            visible: true
            color: "#cccccc"

            anchors{
                verticalCenter: parent.verticalCenter
                left: parent.left
                leftMargin: 20
            }

            text: img.sourceSize.width+"x"+img.sourceSize.height+"@"+img.scale.toFixed(1)+" "+(img.sourceSize.width*img.scale).toFixed(0)+"x"+(img.sourceSize.height*img.scale).toFixed(0)
            verticalAlignment: Text.AlignVCenter
            font.pointSize: 15
        }

        Rectangle {
            id: inputBox
            radius: 5
            width: 350
            height: 40
            anchors.centerIn: parent
            color: "#000000"

            TextEdit {
                id: inputBoxText
                text:fileDialog.file
                color: "#cccccc"
                font.pixelSize: 16
                activeFocusOnTab: true
                selectByMouse: true //是否可以选择文本
                verticalAlignment: TextInput.AlignVCenter
                horizontalAlignment: TextInput.AlignLeft
                anchors.fill: parent

                leftPadding: 3
                rightPadding: 3
            }
        }

        Button{
            id: btn
            text: qsTr("选择路径")
            height: 40
            width: 120

            anchors{
                verticalCenter: inputBox.verticalCenter
                left: inputBox.right
                leftMargin: 20
            }
            background: Rectangle {
                anchors.fill: parent
                color: btn.down ? "#0000ff" : "#21be2b"
                radius: 2
            }

            onClicked: {
                fileDialog.open()
            }
        }

        FileDialog {
            id: fileDialog
            folder: StandardPaths.standardLocations(StandardPaths.PicturesLocation)[0] //默认打开Pictures文件夹
            nameFilters: ["Picture files (*.png *.jpg *.jpeg)", "All files (*)"]
            onAccepted: {
                imgProcess.process(fileDialog.file);
            }
        }
        ImageProcess {
            id: imgProcess
            path: fileDialog.file
        }
    }
    Pane {
        id: view
        clip: true
        anchors.top: header.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right



        MouseArea{
            anchors.fill: parent
            onWheel: (wheel)=>{
                if (wheel.angleDelta.y > 0) {
                    img.scale += 0.1;
                } else {
                    img.scale -= 0.1;
                }
            }
        }
        Image {
            id: img
            fillMode: Image.Pad
            source: "image://colors/gray"
            onStatusChanged: {
                if (img.status == Image.Ready) {
//                    img.anchors.centerIn = parent;
                    img.x = (view.width-img.width)/2;
                    img.y = (view.height-img.height)/2;
                }
            }


            MouseArea{
                anchors.fill: parent

                drag.target: img
                drag.axis: Drag.XAndYAxis
                cursorShape: Qt.PointingHandCursor
                hoverEnabled: true
            }
        }

        Component.onCompleted: {
            if (img.status == Image.Ready) {
                img.x = (view.width-img.width)/2;
                img.y = (view.height-img.height)/2;
            }
        }
    }
    Connections{
        target: ImageProvider
        function onCallQmlRefeshImg(){
            img.source = "image://colors/other"+Math.random();
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
