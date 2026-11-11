#include "speedtransmitter.h"
#include "VehicleCanSpeedEncoder.h"

#include <QByteArray>
#include <QCanBus>
#include <QCanBusDevice>

#include <utility>

SpeedTransmitter::SpeedTransmitter(QObject *parent)
    : QObject(parent)
{
    m_timer.setInterval(100);
    connect(&m_timer, &QTimer::timeout, this, &SpeedTransmitter::sendCurrentFrame);
    setSpeedKph(0);
}

SpeedTransmitter::~SpeedTransmitter()
{
    if (m_device)
        m_device->disconnectDevice();
}

void SpeedTransmitter::setSpeedKph(int speedKph)
{
    const auto bytes = VehicleCanProtocol::encodeWholeSpeedKph(speedKph);
    const QByteArray payload(reinterpret_cast<const char *>(bytes.data()),
                             static_cast<qsizetype>(bytes.size()));
    m_frame = QCanBusFrame(VehicleCanProtocol::SpeedFrameId, payload);
}

void SpeedTransmitter::start()
{
    if (transmitting())
        return;

    QString error;
    std::unique_ptr<QCanBusDevice> device(QCanBus::instance()->createDevice(
        QStringLiteral("socketcan"), QStringLiteral("vcan0"), &error));
    if (!device) {
        setErrorMessage(tr("Falha ao criar o dispositivo CAN. %1").arg(error).trimmed());
        return;
    }
    if (!device->connectDevice()) {
        setErrorMessage(tr("Falha ao conectar à vcan0. %1").arg(device->errorString()).trimmed());
        return;
    }

    m_device = std::move(device);
    connect(m_device.get(), &QCanBusDevice::framesReceived,
            this, &SpeedTransmitter::discardReceivedFrames);
    setErrorMessage({});
    m_timer.start();
    emit transmittingChanged();
    sendCurrentFrame();
}

void SpeedTransmitter::pause()
{
    if (!transmitting())
        return;

    m_timer.stop();
    m_device->disconnectDevice();
    m_device.reset();
    emit transmittingChanged();
}

void SpeedTransmitter::sendCurrentFrame()
{
    if (m_device && !m_device->writeFrame(m_frame)) {
        const QString error = m_device->errorString();
        pause();
        setErrorMessage(tr("Falha ao transmitir pela vcan0. %1").arg(error).trimmed());
    }
}

void SpeedTransmitter::discardReceivedFrames()
{
    // Other writers can share vcan0. This transmitter has no incoming signals to decode.
    if (m_device)
        m_device->clear(QCanBusDevice::Input);
}

void SpeedTransmitter::setErrorMessage(const QString &message)
{
    if (m_errorMessage == message)
        return;
    m_errorMessage = message;
    emit errorMessageChanged();
}
