#include "VehicleState.h"
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

    const bool speedChanged = m_speedKph != speedKph;
    m_speedKph = speedKph;

    if(!m_hasSpeedSample)
    {
        m_hasSpeedSample = true;
        emit hasSpeedSampleChanged();
    }

    if(speedChanged)
    {
        emit speedKphChanged();
    }

}

bool VehicleState::hasSpeedSample() const
{
    return m_hasSpeedSample;
}
