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

public:
    explicit VehicleState(QObject *parent = nullptr);

    double speedKph() const;
    void SetSpeedKph(double speedKph);

signals:

    void speedKphChanged();

private:
    double m_speedKph = 0.0f;
};

#endif // VEHICLESTATE_H
