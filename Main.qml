import QtQuick

Window {
    id: root
    required property VehicleState vehicleState

    width: 960
    height: 540
    minimumWidth: 480
    minimumHeight: 270

    visible: true
    title: "Vehicle HMI - CAN"
    color: "#151b23"

    Text {
        anchors.centerIn: parent

        readonly property bool hasSample: root.vehicleState.hasSpeedSample

        text: hasSample ? root.vehicleState.speedKph.toFixed(2) + " km/h"
                        : qsTr("Waiting speed's transmission")
        font.pixelSize: hasSample ? 64 : 26
        color: hasSample ? "#e6edf3" : "#a5b2c2"
    }

    Speedometer {
        anchors.centerIn: parent
        width: Math.min(parent.width, parent.height) * 0.9
        height: width

        speedKph: root.vehicleState.speedKph
        hasSample: root.vehicleState.hasSpeedSample
    }
}
