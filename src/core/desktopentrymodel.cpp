#include "desktopentrymodel.h"

DesktopEntryModel::DesktopEntryModel(QObject *parent) : QAbstractListModel(parent){}

DesktopEntryModel::DesktopEntryModel(const QList<DesktopEntry> &entries, QObject *parent) : QAbstractListModel(parent), m_entries(entries) {}

int DesktopEntryModel::rowCount(const QModelIndex &parent) const {

    if (parent.isValid()) {
        return 0;
    }

    return m_entries.size();
}

QVariant DesktopEntryModel::data(const QModelIndex &index, int role) const {

    if (!index.isValid() || index.row() >= m_entries.size()) {
        return {};
    }

    const DesktopEntry& entry = m_entries.at(index.row());

    switch (role) {

    case NameRole:
        return entry.name;
    case GenericNameRole:
        return entry.genericName;
    case CommentRole:
        return entry.comment;
    case ExecRole:
        return entry.exec;
    case CategoriesRole:
        return entry.categories.join(" ");
    case KeywordsRole:
        return entry.keywords.join(" ");
    case IconNameRole:
        return entry.icon;
    default:
        return QVariant();
    }
}

const DesktopEntry* DesktopEntryModel::at(const QModelIndex &index) const {

    if (index.row() < m_entries.size()) {
        return &m_entries.at(index.row());
    }

    return nullptr;
}

QHash<int, QByteArray> DesktopEntryModel::roleNames() const {

    return {
        {NameRole, "name"},
        {GenericNameRole, "genericName"},
        {CommentRole, "comment"},
        {ExecRole, "exec"},
        {IconNameRole, "iconName"},
        {CategoriesRole, "categories"},
        {KeywordsRole, "keywords"},
    };
}