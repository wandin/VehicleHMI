#include "vehiclestate.h"
#include <QDebug>

VehicleState::VehicleState(QObject *parent) : QObject{parent}
{

}

double VehicleState::speedKph() const
{
    return m_speedKph;
}

void VehicleState::SetSpeedKph(double speedKph)
{
    if(!std::isfinite(speedKph) || speedKph < 0.0)
    {
        qWarning() << "Rejected speed (km/h)" << speedKph;
        return;
    }

    if(m_speedKph == speedKph)
    {
        return;
    }

    m_speedKph = speedKph;
    emit speedKphChanged();
}
