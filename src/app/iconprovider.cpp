#include "iconprovider.h"

#include <QPixmap>

IconProvider::IconProvider() : QQuickImageProvider(QQuickAsyncImageProvider::Pixmap) {}

QPixmap IconProvider::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) {

    const int edge = (!requestedSize.isEmpty()) ? qMin(requestedSize.width(), requestedSize.height()) : 40;

    if (size) {
        *size = QSize(edge, edge);
    }

    return resolve(id).pixmap(QSize(edge, edge));
}

QIcon IconProvider::resolve(const QString &id) const {

    if (m_cache.contains(id)) {
        return m_cache.value(id);
    }

    QIcon icon = id.startsWith('/') ? QIcon(id) : QIcon::fromTheme(id);

    if (icon.isNull()) {
        icon = QIcon::fromTheme("application-x-executable");
    }

    m_cache.insert(id, icon);

    return icon;
}