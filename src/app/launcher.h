#ifndef LAUNCHER_H
#define LAUNCHER_H

#include <QString>
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
    Q_PROPERTY(QString query READ query WRITE setQuery NOTIFY queryChanged)
    Q_PROPERTY(int resultCount READ resultCount NOTIFY resultCountChanged)

public:

    explicit Launcher(QObject* parent = nullptr);
    QAbstractItemModel* model() const;

    QString query() const;
    void setQuery(const QString& query);
    int resultCount() const;

    Q_INVOKABLE bool launch(int row) const;

signals:

    void queryChanged();
    void resultCountChanged();

private:

    QString m_query;

    DesktopEntryModel* m_model;
    DesktopEntryProxyModel* m_proxy;
};

#endif // LAUNCHER_H
