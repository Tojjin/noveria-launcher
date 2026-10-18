#include "desktopentryproxymodel.h"
#include "desktopentrymodel.h"

#include <algorithm>

DesktopEntryProxyModel::DesktopEntryProxyModel(QObject *parent) : QSortFilterProxyModel(parent) {}

void DesktopEntryProxyModel::setQuery(const QString &query) {

    beginFilterChange();
    m_query = query;
    endFilterChange();
    invalidate();
    emit filterUpdated();
}

bool DesktopEntryProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const {

    if (m_query.isEmpty()) {
        return true;
    }

    QModelIndex index = sourceModel()->index(source_row, 0, source_parent);

    return getMaxScore(index) > 0;
}

bool DesktopEntryProxyModel::lessThan(const QModelIndex &source_left, const QModelIndex &source_right) const {

    if (m_query.isEmpty()) {

        QString leftName = source_left.data(NameRole).value<QString>();
        QString rightName = source_right.data(NameRole).value<QString>();

        return leftName.compare(rightName, Qt::CaseInsensitive) < 0;
    }

    int leftScore = getMaxScore(source_left);
    int rightScore = getMaxScore(source_right);

    if (leftScore == rightScore) {

        QString leftName = source_left.data(NameRole).value<QString>();
        QString rightName = source_right.data(NameRole).value<QString>();

        return leftName.compare(rightName, Qt::CaseInsensitive) < 0;
    }

    return leftScore > rightScore;
}

int DesktopEntryProxyModel::fuzzySearch(const QString &query, const QString &target) const {

    if (query.isEmpty()) {
        return 0;
    }

    const QString l_query = query.toLower();
    const QString l_target = target.toLower();

    int score{0};
    int queryIndex{0};
    int lastMatchIndex = -1;

    for (int i = 0; i < l_target.length(); ++i) {

        if (l_target[i] == l_query[queryIndex]) {
            score+=10;

            if (i == 0) {
                score+=25;
            }
            else if (l_target[i-1] == ' ' || l_target[i-1] == '-') {
                score+=15;
            }

            if (queryIndex > 0 && lastMatchIndex == i - 1) {
                score+=10;
            }

            if (lastMatchIndex != - 1) {
                int skipped = i - lastMatchIndex - 1;
                score -= skipped*3;
            }
            else {
                score -= i;
            }

            lastMatchIndex = i;
            queryIndex++;

            if (queryIndex == l_query.length()) {
                break;
            }
        }
    }

    if (queryIndex == l_query.length()) {
        return score;
    }

    return -1;
}

int DesktopEntryProxyModel::getMaxScore(const QModelIndex &index) const {

    QString name = index.data(NameRole).value<QString>();
    if (name.compare(m_query, Qt::CaseInsensitive) == 0) {
        return 10000;
    }

    int nameScore = fuzzySearch(m_query, name);
    if (nameScore > 0) {
        return nameScore + 200;
    }

    QString genericName = index.data(GenericNameRole).value<QString>();
    int genericScore = fuzzySearch(m_query, genericName);
    if (genericScore > 0) {
        return genericScore + 50;
    }

    QString keywords = index.data(KeywordsRole).value<QString>();
    if (keywords.contains(m_query, Qt::CaseInsensitive)) {
        return 30;
    }

    QString categories = index.data(CategoriesRole).value<QString>();
    if (categories.contains(m_query, Qt::CaseInsensitive)) {
        return 20;
    }

    QString comment = index.data(CommentRole).value<QString>();
    if (comment.contains(m_query, Qt::CaseInsensitive)) {
        return 10;
    }

    return -1;
}