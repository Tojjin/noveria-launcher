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
    bool lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const override;

    int fuzzySearch(const QString& query, const QString& target) const;
    QString m_query;
    int getMaxScore(const QModelIndex& index) const;


signals:

    void filterUpdated();
};

#endif // DESKTOPENTRYPROXYMODEL_H