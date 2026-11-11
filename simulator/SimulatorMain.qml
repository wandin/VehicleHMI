import QtQuick
import QtQuick.Controls
import VehicleSim

ApplicationWindow {
    id: root
    required property SpeedTransmitter transmitter

    width: 430
    height: 300
    minimumWidth: 330
    minimumHeight: controls.implicitHeight + 56
    visible: true
    title: qsTr("VehicleSimulator · vcan0")

    Column {
        id: controls
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        anchors.margins: 28
        spacing: 12

        Label {
            text: qsTr("Simulated speed")
        }

        Label {
            text: Math.round(speedSlider.value) + " km/h"
            font.pixelSize: 38
            font.weight: Font.DemiBold
        }

        Slider {
            id: speedSlider
            width: parent.width
            from: 0
            to: 200
            stepSize: 1
            snapMode: Slider.SnapAlways
            live: true
            Accessible.name: qsTr("Simulated Speed in km/h")
            onMoved: root.transmitter.setSpeedKph(Math.round(value))
        }

        Button {
            text: root.transmitter.transmitting ? qsTr("Pause transmission") : qsTr("Start transmission")
            onClicked: {
                if (root.transmitter.transmitting)
                    root.transmitter.pause()
                else
                    root.transmitter.start()
            }
        }

        Label {
            width: parent.width
            visible: root.transmitter.errorMessage.length > 0
            text: root.transmitter.errorMessage
            wrapMode: Text.Wrap
        }
    }
}
