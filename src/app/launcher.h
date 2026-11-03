#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QObject>
#include <QtQml/qqmlregistration.h>
#include <QAbstractItemModel>

class DesktopEntryModel;
class DesktopEntryProxyModel;

class Launcher : public QObject {

    Q_OBJECT

    QML_ELEMENT
    QML_SINGLETON

    Q_PROPERTY(QAbstractItemModel* model READ model CONSTANT)

public:

    explicit Launcher(QObject* parent = nullptr);
    QAbstractItemModel* model() const;

private:

    DesktopEntryModel* m_model;
    DesktopEntryProxyModel* m_proxy;
};

#endif // LAUNCHER_H
