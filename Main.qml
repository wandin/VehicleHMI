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

    Speedometer {
        anchors.centerIn: parent
        width: Math.min(parent.width, parent.height) * 0.9
        height: width

        speedKph: root.vehicleState.speedKph
        hasSample: root.vehicleState.hasSpeedSample
    }
}
