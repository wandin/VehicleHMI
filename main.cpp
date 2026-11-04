#include "vehiclestate.h"
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QTimer>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    VehicleState vehicleState;

    QQmlApplicationEngine engine;

    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);

    engine.setInitialProperties(
            {
                {"vehicleState", QVariant::fromValue(&vehicleState)}
            }
        );

    engine.loadFromModule("VehicleHMI", "Main");

    QTimer demoTimer;

    QObject::connect(
        &demoTimer,
        &QTimer::timeout,
        &vehicleState,
        [&vehicleState]()
        {
        const double nextSpeedKph = vehicleState.speedKph() + 10.0;

            vehicleState.SetSpeedKph(nextSpeedKph > 120.0 ? 0.0 : nextSpeedKph);

        });

    demoTimer.start(1000);

    return app.exec();
}
