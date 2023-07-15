import QtQuick 2.15
import QtQuick.Controls 2.15
import QtMultimedia 6.5

Rectangle {
    id: rectangle
    width: 800
    height: 600
    visible: true
    color: "black"
    state: "backup"

    states: [
        State {
            name: "backup"
            StateChangeScript {
                script: {
                    camera.start()
                }
            }
        }
    ]


    CaptureSession {
       videoOutput: videoOutput

       camera: Camera {
           id: camera
       }
    }

    VideoOutput {
        id: videoOutput
        visible: true
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.leftMargin: parent.width
        anchors.rightMargin: -parent.width
        anchors.bottomMargin: 0
        anchors.topMargin: 0
        transform: Scale { xScale: -1 }
    }
}
