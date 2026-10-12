#include "desktopentrymodel.h"
#include <QIcon>

DesktopEntryModel::DesktopEntryModel(QObject *parent) : QAbstractListModel(parent){}

DesktopEntryModel::DesktopEntryModel(const QList<DesktopEntry> &entries, QObject *parent) : QAbstractListModel(parent), m_entries(entries) {}

int DesktopEntryModel::rowCount(const QModelIndex &parent) const {

    return m_entries.size();
}

QVariant DesktopEntryModel::data(const QModelIndex &index, int role) const {

    if (!index.isValid() || index.row() >= m_entries.size()) {
        return {};
    }

    const DesktopEntry& entry = m_entries.at(index.row());

    switch (role) {

    case Qt::DisplayRole:
        return entry.name;
    case Qt::DecorationRole:
        return loadIcon(entry.icon);
    case Qt::ToolTipRole:
        return entry.comment;
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

QIcon DesktopEntryModel::loadIcon(const QString &iconName) const {

    if (iconName.isEmpty()) {
        return QIcon::fromTheme("application-x-executable");
    }

    if (m_iconCache.contains(iconName)) {
        return m_iconCache.value(iconName);
    }

    QIcon icon;
    if (iconName.startsWith('/')) {
        icon = QIcon(iconName);
    }
    else {
        icon = QIcon::fromTheme(iconName);
    }

    if (icon.isNull()) {
        icon = QIcon::fromTheme("application-x-executable");
    }

    m_iconCache.insert(iconName, icon);

    return icon;
}