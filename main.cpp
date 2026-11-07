#include "VehicleState.h"
#include "CanReceiver.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTimer>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    VehicleState vehicleState;
    CanReceiver canReceiver;

    QObject::connect(
        &canReceiver,
        &CanReceiver::speedReceived,
        &vehicleState,
        &VehicleState::SetSpeedKph);

    if(!canReceiver.start(QStringLiteral("vcan0")))
    {
        return 1;
    }

    QQmlApplicationEngine engine;

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.setInitialProperties({
        {"vehicleState", QVariant::fromValue(&vehicleState)}
    });

    engine.loadFromModule("VehicleHMI", "Main");

    return app.exec();
}
