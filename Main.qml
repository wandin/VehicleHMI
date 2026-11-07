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

        text: root.vehicleState.speedKph.toFixed(2) + " Km/h"
        color: "#e6edf3"
        font.pixelSize: 64
    }
}
