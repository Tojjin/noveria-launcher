#include "desktopentrydelegate.h"
#include "desktopentrymodel.h"

#include <QFontMetrics>
#include <QIcon>

namespace {
    constexpr int ICON_SIZE{40};
    constexpr int PADDING{5};
    constexpr int ITEM_MARGIN_BOTTOM{6};
    const QColor NAME_COLOR{255, 255, 255};
    const QColor NAME_COLOR_SELECTED{0, 0, 0};
    const QColor COMMENT_COLOR{100, 100, 100};
}

DesktopEntryDelegate::DesktopEntryDelegate(QObject *parent) : QStyledItemDelegate(parent) {}

void DesktopEntryDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const {

    //Drawing base ListView boxes
    QStyledItemDelegate::paint(painter, option, index);

    // painter->setPen(Qt::red);
    // painter->drawRect(option.rect);

    //Setting up box for Icon
    QIcon icon = index.data(IconRole).value<QIcon>();
    const qreal dpr = painter->device()->devicePixelRatioF();
    QPixmap iconMap = icon.pixmap(QSize(ICON_SIZE, ICON_SIZE),dpr);

    int visualHeight = option.rect.height() - ITEM_MARGIN_BOTTOM;
    int listCenter = option.rect.top() + visualHeight/2;
    int iconLeft = option.rect.left() + PADDING;
    int iconTop = listCenter - ICON_SIZE/2;

    // painter->setPen(Qt::green);
    // painter->drawRect(iconLeft, iconTop, ICON_SIZE, ICON_SIZE);

    //Drawing Icon

    painter->drawPixmap(iconLeft, iconTop, ICON_SIZE, ICON_SIZE, iconMap);

    //Setting up fonts

    QFont nameFont = painter->font();
    nameFont.setPointSize(10);
    QFontMetrics fmName(nameFont);

    QFont commentFont = painter->font();
    commentFont.setPointSize(9);
    QFontMetrics fmComment(commentFont);

    //Setting up data

    QString name = index.data(NameRole).value<QString>();
    QString comment = index.data(CommentRole).value<QString>();
    QString genericName = index.data(GenericNameRole).value<QString>();

    if (comment.trimmed().isEmpty()) {
        comment = genericName;
    }

    int totalTextHeight = fmName.height();
    if(!comment.trimmed().isEmpty()) {
        totalTextHeight += fmComment.height();
    }

    //Setting up box for Name

    int textLeft = option.rect.left() + PADDING + ICON_SIZE + PADDING;
    int textWidth = option.rect.width() - ICON_SIZE - 5*PADDING;
    name = fmName.elidedText(name, Qt::ElideRight, textWidth);

    QRect nameRect(textLeft, listCenter - totalTextHeight/2, textWidth, fmName.height());
    QRect noComment(textLeft, listCenter - fmName.height()/2, textWidth, fmName.height());

    // painter->setPen(Qt::green);
    // painter->drawRect(nameRect);

    //Setting up box for Comment

    comment = fmComment.elidedText(comment, Qt::ElideRight, textWidth);

    QRect commentRect(textLeft, nameRect.bottom(), textWidth, fmComment.height());

    // painter->setPen(Qt::blue);
    // painter->drawRect(commentRect);

    QColor penColor;
    if (option.state & (QStyle::State_Selected | QStyle::State_MouseOver)) {
        penColor = NAME_COLOR_SELECTED;
    }
    else {
        penColor = NAME_COLOR;
    }

    //Drawing Text

    if (!comment.trimmed().isEmpty()) {
        painter->setPen(penColor);
        painter->setFont(nameFont);
        painter->drawText(nameRect, Qt::AlignVCenter | Qt::AlignLeft, name);

        painter->setPen(COMMENT_COLOR);
        painter->setFont(commentFont);
        painter->drawText(commentRect, Qt::AlignVCenter | Qt::AlignLeading, comment);
    }
    else {
        painter->setPen(penColor);
        painter->setFont(nameFont);
        painter->drawText(noComment, Qt::AlignVCenter | Qt::AlignLeft, name);
    }
}

QSize DesktopEntryDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {

    int contentHeight = PADDING + ICON_SIZE + PADDING;
    return QSize(0, contentHeight + ITEM_MARGIN_BOTTOM);
}