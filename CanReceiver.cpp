#include "CanReceiver.h"
#include "VehicleCanProtocol.h"
#include <QCanBus>
#include <qdebug.h>

CanReceiver::CanReceiver(QObject *parent)
    : QObject{parent}
{}

CanReceiver::~CanReceiver()
{
    if(m_device && m_device->state() == QCanBusDevice::ConnectedState)
    {
        m_device->disconnectDevice();
    }
}

bool CanReceiver::start(const QString &interfaceName)
{
    if(m_device)
    {
        qWarning() << "CAN receiver is already initialized.";
        return false;
    }

    QString errorMessage;

    m_device = QCanBus::instance()->createDevice(
        QStringLiteral("socketcan"),
        interfaceName,
        &errorMessage);

    if(!m_device)
    {
        qCritical() << "Failed to create CAN device:" << errorMessage;
        return false;
    }

    m_device->setParent(this);

    QObject::connect(
        m_device,
        &QCanBusDevice::framesReceived,
        this,
        &CanReceiver::processRReceivedFrames);

    QObject::connect(
        m_device,
        &QCanBusDevice::errorOccurred,
        this,
        &CanReceiver::handleError);

    if(!m_device->connectDevice())
    {
        qCritical() << "Failed to connect CAN device:" << m_device->errorString();

        delete m_device;
        m_device = nullptr;
        return false;
    }

    qInfo().noquote() << "CAN connected on" << interfaceName;
    return true;

}

void CanReceiver::processRReceivedFrames()
{
    const auto frames = m_device->readAllFrames();

    for(const QCanBusFrame &frame : frames)
    {
        if(!frame.isValid() ||
            frame.frameType() != QCanBusFrame::DataFrame ||
            frame.hasExtendedFrameFormat() ||
            frame.hasFlexibleDataRateFormat() ||
            frame.frameId() != VehicleCanProtocol::SpeedFrameId)
        {
            continue;
        }

        const QByteArray payload = frame.payload();

        if(payload.size() != VehicleCanProtocol::SpeedPayloadBytes)
        {
            qWarning() << "Ignored speed frame: expected 2 bytes, received" << payload.size();

            continue;
        }

        const auto lowByte = static_cast<uint8_t>(payload.at(0));
        const auto highByte = static_cast<std::uint8_t>(payload.at(1));

        const double speedKph = VehicleCanProtocol::decodeSpeedKph(lowByte, highByte);

        emit speedReceived(speedKph);
    }
}

void CanReceiver::handleError(QCanBusDevice::CanBusError error)
{
    if(error == QCanBusDevice::NoError)
    {
        return;
    }

    qWarning() << "CAN error:" << m_device->errorString();
}


