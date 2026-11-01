#ifndef DESKTOPENTRYMODEL_H
#define DESKTOPENTRYMODEL_H

#include "desktopentry.h"

#include <QAbstractListModel>
#include <QModelIndex>
#include <QVariant>
#include <QList>
#include <QHash>
#include <QIcon>

enum Roles {
    NameRole = Qt::UserRole + 1,
    GenericNameRole,
    CommentRole,
    ExecRole,
    IconRole,
    CategoriesRole,
    KeywordsRole,
};

class DesktopEntryModel : public QAbstractListModel {

    Q_OBJECT

public:

    explicit DesktopEntryModel(QObject *parent = nullptr);
    explicit DesktopEntryModel(const QList<DesktopEntry>& entries, QObject *parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    const DesktopEntry* at(const QModelIndex& index) const;

private:

    QList<DesktopEntry> m_entries;
    mutable QHash<QString, QIcon> m_iconCache;

    QIcon loadIcon(const QString& iconName) const;
};

#endif // DESKTOPENTRYMODEL_H
