pragma ComponentBehavior: Bound
import QtQuick

Rectangle {
    id: dial

    required property real speedKph
    required property bool hasSample
    readonly property int maximumKph: 200
    readonly property int tickStepKph: 10
    readonly property color needleColor: "#64decb"

    implicitWidth: 360
    implicitHeight: implicitWidth
    radius: width / 2
    color: "#101a23"
    border.color: "#324352"

    function angleForSpeed(kph: real): real {
        const boundedKph = Math.max(0, Math.min(kph, dial.maximumKph))
        return -120 + 240 * boundedKph / dial.maximumKph
    }

    Repeater {
        model: dial.maximumKph / dial.tickStepKph + 1

        delegate: Item {
            id: tick
            required property int index
            readonly property int kph: index * dial.tickStepKph
            readonly property bool major: kph % 50 === 0

            anchors.fill: parent
            rotation: dial.angleForSpeed(tick.kph)

            Rectangle {
                anchors.horizontalCenter: parent.horizontalCenter
                y: dial.height * 0.12
                width: Math.max(1, dial.width * (tick.major ? 0.010 : 0.005))
                height: dial.height * (tick.major ? 0.065 : 0.036)
                radius: width / 2
                color: tick.major ? "#d8e5ed" : "#708392"
            }

            Text {
                visible: tick.major
                anchors.horizontalCenter: parent.horizontalCenter
                y: dial.height * 0.04
                text: String(tick.kph)
                font.pixelSize: Math.round(dial.width * 0.045)
                color: "#beccd6"
                rotation: -tick.rotation // Keep the label upright.
            }
        }
    }

    Rectangle {
        visible: dial.hasSample
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.verticalCenter
        width: Math.max(2, dial.width * 0.012)
        height: dial.height * 0.30
        radius: width / 2
        color: dial.needleColor
        transformOrigin: Item.Bottom
        rotation: dial.angleForSpeed(dial.speedKph)

        Behavior on rotation {
            enabled:dial.hasSample
            SmoothedAnimation {
                duration: 120
                velocity: -1
                reversingMode: SmoothedAnimation.Immediate
            }
        }
    }

    Rectangle {
        visible: dial.hasSample
        anchors.centerIn: parent
        width: dial.width * 0.045
        height: width
        radius: width / 2
        color: dial.needleColor
    }

    Text {
        anchors.centerIn: parent
        anchors.verticalCenterOffset: dial.hasSample ? dial.height * 0.26 : 0
        text: dial.hasSample ? dial.speedKph.toFixed(2) + " km/h"
                             : qsTr("Waiting speed's transmission")
        font.pixelSize: Math.round(dial.width * (dial.hasSample ? 0.082 : 0.052))
        color: dial.hasSample ? "#edf3f7" : "#a7b6c2"
    }
}
