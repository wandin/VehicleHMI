#pragma once

#include <QCanBusFrame>
#include <QObject>
#include <QString>
#include <QTimer>
#include <QtQml/qqmlregistration.h>

#include <memory>

class QCanBusDevice;

class SpeedTransmitter : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("SpeedTransmitter is provided by C++.")
    Q_PROPERTY(bool transmitting READ transmitting NOTIFY transmittingChanged FINAL)
    Q_PROPERTY(QString errorMessage READ errorMessage NOTIFY errorMessageChanged FINAL)

public:
    explicit SpeedTransmitter(QObject *parent = nullptr);
    ~SpeedTransmitter() override;

    bool transmitting() const { return m_timer.isActive(); }
    QString errorMessage() const { return m_errorMessage; }

    Q_INVOKABLE void setSpeedKph(int speedKph);
    Q_INVOKABLE void start();
    Q_INVOKABLE void pause();

signals:
    void transmittingChanged();
    void errorMessageChanged();

private:
    void sendCurrentFrame();
    void discardReceivedFrames();
    void setErrorMessage(const QString &message);

    QTimer m_timer;
    std::unique_ptr<QCanBusDevice> m_device;
    QCanBusFrame m_frame;
    QString m_errorMessage;
};
