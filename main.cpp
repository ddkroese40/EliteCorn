#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "CppHandler.h"

int main(int argc, char *argv[]) {
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    CppHandler cppHandler;

    if(argc >= 2)
    {
        cppHandler.processFile(argv[1]);
    }

    engine.rootContext()->setContextProperty("cppHandler", &cppHandler);  // Expose to QML

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed,
                     &app, []() { QCoreApplication::exit(-1); },
                     Qt::QueuedConnection);

    engine.loadFromModule("EliteCorn", "Main");

    return app.exec();
}
