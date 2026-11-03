#ifndef ICONPROVIDER_H
#define ICONPROVIDER_H

#include <QHash>
#include <QIcon>
#include <QQuickImageProvider>

class IconProvider : public QQuickImageProvider {

public:

    IconProvider();
    QPixmap requestPixmap(const QString &id, QSize *size, const QSize &requestedSize) override;

private:

    QIcon resolve(const QString& id) const;
    mutable QHash<QString, QIcon> m_cache;
};

#endif // ICONPROVIDER_H