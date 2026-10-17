#include "desktopentryproxymodel.h"
#include "desktopentrymodel.h"

DesktopEntryProxyModel::DesktopEntryProxyModel(QObject *parent) : QSortFilterProxyModel(parent) {}

void DesktopEntryProxyModel::setQuery(const QString &query) {

    beginFilterChange();
    m_query = query;
    endFilterChange();
    emit filterUpdated();
}

bool DesktopEntryProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const {

    if (m_query.isEmpty()) {
        return true;
    }

    QModelIndex index = sourceModel()->index(source_row, 0, source_parent);

    QString name = index.data(NameRole).value<QString>();
    QString genericName = index.data(GenericNameRole).value<QString>();
    QString categories = index.data(CategoriesRole).value<QString>();
    QString keywords = index.data(KeywordsRole).value<QString>();

    return name.contains(m_query, Qt::CaseInsensitive)
            || genericName.contains(m_query, Qt::CaseInsensitive)
            || categories.contains(m_query, Qt::CaseInsensitive)
            || keywords.contains(m_query, Qt::CaseInsensitive);
}