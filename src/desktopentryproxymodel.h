#ifndef DESKTOPENTRYPROXYMODEL_H
#define DESKTOPENTRYPROXYMODEL_H

#include <QSortFilterProxyModel>
#include <QString>

class DesktopEntryProxyModel : public QSortFilterProxyModel {

    Q_OBJECT

public:

    explicit DesktopEntryProxyModel(QObject* parent = nullptr);
    void setQuery(const QString& query);

private:

    bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;
    QString m_query;

signals:

    void filterUpdated();
};

#endif // DESKTOPENTRYPROXYMODEL_H