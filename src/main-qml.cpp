#include <QCommandLineParser>
#include <QDebug>
#include <QGuiApplication>
#include <QIcon>
#include <QLocalServer>
#include <QLocalSocket>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QThread>

#include "app/iconprovider.h"

namespace {

const QString appName{"noveria-launcher"};

bool notifyRunning(const QString &message) {

    QLocalSocket socket;
    socket.setSocketOptions(QLocalSocket::AbstractNamespaceOption);
    socket.connectToServer(appName, QIODevice::WriteOnly);

    if (!socket.waitForConnected(200)) {
        return false;
    }

    if (!message.isEmpty()) {
        socket.write(message.toUtf8());
        socket.flush();
        socket.waitForBytesWritten(200);
    }

    socket.disconnectFromServer();

    return true;
}

void invokeLauncherMethod(QQuickWindow *window, const char *method) {

    if (!window) {
        return;
    }

    if (!QMetaObject::invokeMethod(window, method, Qt::DirectConnection)) {
        qWarning() << "Failed to invoke QML method:" << method;
    }
}

}

int main(int argc, char *argv[]) {

    QGuiApplication app(argc, argv);

    QGuiApplication::setApplicationName("noveria-launcher");
    QGuiApplication::setApplicationDisplayName("Noveria Launcher");
    QGuiApplication::setApplicationVersion("0.1.0");
    QGuiApplication::setDesktopFileName("noveria-launcher");

    QCommandLineParser parser;
    parser.setApplicationDescription("Noveria Launcher");
    parser.addHelpOption();
    parser.addVersionOption();
    parser.addOption({"hidden", "Start the launcher without showing it"});
    parser.process(app);

    const bool startHidden = parser.isSet("hidden");

    const QString request = startHidden ? QStringLiteral("ping") : QStringLiteral("toggle");

    if (notifyRunning(request)) {
        return 0;
    }

    QLocalServer server;
    server.setSocketOptions(QLocalServer::AbstractNamespaceOption);

    if (!server.listen(appName)) {

        for (int attempt = 0; attempt < 10; ++attempt) {
            QThread::msleep(50);

            if (notifyRunning(request)) {
                return 0;
            }
        }

        qWarning() << "Failed to start single-instance server:" << server.errorString();
        return 1;
    }

    QQuickWindow *launcherWindow = nullptr;
    int pendingToggles = 0;

    QObject::connect(&server, &QLocalServer::newConnection, &app, [&]() {
        while (QLocalSocket *client = server.nextPendingConnection()) {
            QObject::connect(client, &QLocalSocket::disconnected, client, &QObject::deleteLater);
            client->waitForReadyRead(100);

            if (client->readAll() == "toggle") {
                if (launcherWindow) {
                    invokeLauncherMethod(launcherWindow, "toggleLauncher");
                }
                else {
                    ++pendingToggles;
                }
            }
        }
    });

    QIcon::setThemeName("Adwaita");

    QQmlApplicationEngine engine;
    engine.addImageProvider("icons", new IconProvider);

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreationFailed, &app, []() {
        QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.loadFromModule("Noveria", "Main");

    if (!engine.rootObjects().isEmpty()) {
        launcherWindow = qobject_cast<QQuickWindow *>(engine.rootObjects().constFirst());
    }

    if (!startHidden) {
        invokeLauncherMethod(launcherWindow, "showLauncher");
    }

    for (int i = 0; i < pendingToggles; ++i) {
        invokeLauncherMethod(launcherWindow, "toggleLauncher");
    }

    return app.exec();
}