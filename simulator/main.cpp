#include "speedtransmitter.h"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QVariant>

#include <cstdlib>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    SpeedTransmitter transmitter;

    QQmlApplicationEngine engine;
    engine.setInitialProperties({{QStringLiteral("transmitter"), QVariant::fromValue(&transmitter)}});
    engine.loadFromModule("VehicleSim", "SimulatorMain");

    if (engine.rootObjects().isEmpty())
        return EXIT_FAILURE;

    return app.exec();
}
