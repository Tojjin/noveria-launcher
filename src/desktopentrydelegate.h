#ifndef DESKTOPENTRYDELEGATE_H
#define DESKTOPENTRYDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>
#include <QStyleOptionViewItem>
#include <QModelIndex>

class DesktopEntryDelegate : public QStyledItemDelegate {

    Q_OBJECT

public:

    explicit DesktopEntryDelegate(QObject* parent = nullptr);

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

#endif // DESKTOPENTRYDELEGATE_H
