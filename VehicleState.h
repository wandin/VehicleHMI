#ifndef VEHICLESTATE_H
#define VEHICLESTATE_H

#include <QObject>
#include <QtQml/qqmlregistration.h>

class VehicleState : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_UNCREATABLE("VehicleState is provided in C++")

    Q_PROPERTY(double speedKph READ speedKph NOTIFY speedKphChanged)
    Q_PROPERTY(bool hasSpeedSample READ hasSpeedSample NOTIFY hasSpeedSampleChanged)

public:
    explicit VehicleState(QObject *parent = nullptr);

    double speedKph() const;
    void SetSpeedKph(double speedKph);

    bool hasSpeedSample() const;

signals:

    void speedKphChanged();
    void hasSpeedSampleChanged();

private:
    double m_speedKph = 0.0f;

    bool m_hasSpeedSample = false;
};

#endif // VEHICLESTATE_H
