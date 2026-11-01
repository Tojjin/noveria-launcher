#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QIcon>

int main (int argc, char *argv[]) {

    QGuiApplication app(argc,argv);

    QGuiApplication::setApplicationName("noveria-launcher");
    QGuiApplication::setApplicationDisplayName("Noveria Launcher");
    QGuiApplication::setApplicationVersion("0.1.0");
    QGuiApplication::setDesktopFileName("noveria-launcher");

    QIcon::setThemeName("Adwaita");

    QQmlApplicationEngine engine;

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed, &app, []() { QCoreApplication::exit(-1); }, Qt::QueuedConnection);

    engine.loadFromModule("Noveria", "Main");

    return app.exec();
}