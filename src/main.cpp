#include <QApplication>
#include <QFile>
#include "mainwindow.h"

int main(int argc, char *argv[]) {

    QApplication app(argc, argv);
    QApplication::setApplicationName("noveria-launcher");
    QApplication::setApplicationDisplayName("Noveria Launcher");
    QApplication::setApplicationVersion("0.1.0");

    QIcon::setThemeName("Adwaita");

    QFile styleFile(":/styles.qss");
    if (styleFile.open(QFile::ReadOnly | QFile::Text)) {
        qApp->setStyleSheet(styleFile.readAll());
    }

    MainWindow window;
    window.show();

    return app.exec();
}