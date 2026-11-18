#pragma once

#include <QCanBusDevice>
#include <QObject>
#include <QString>

class CanReceiver : public QObject
{
    Q_OBJECT
public:
    explicit CanReceiver(QObject *parent = nullptr);
    ~CanReceiver() override;

    bool start(const QString &interfaceName);

signals:
    void speedReceived(double speedKph);

private:
    void processReceivedFrames();
    void handleError(QCanBusDevice::CanBusError error);

    QCanBusDevice *m_device = nullptr;
};
