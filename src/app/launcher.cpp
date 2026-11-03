#include "launcher.h"

#include "core/desktopparser.h"
#include "core/desktopentrymodel.h"
#include "core/desktopentryproxymodel.h"

Launcher::Launcher(QObject* parent) : QObject(parent), m_model(new DesktopEntryModel(DesktopParser().parseAll(), this)), m_proxy(new DesktopEntryProxyModel(this)) {
    m_proxy->setSourceModel(m_model);
    m_proxy->sort(0, Qt::AscendingOrder);

    connect(m_proxy, &DesktopEntryProxyModel::filterUpdated, this, &Launcher::resultCountChanged);
}

QAbstractItemModel* Launcher::model() const {

    return m_proxy;
}

QString Launcher::query() const {

    return m_query;
}

void Launcher::setQuery(const QString &query) {

    if (m_query == query) {
        return;
    }

    m_query = query;
    m_proxy->setQuery(query);
    emit queryChanged();
}

int Launcher::resultCount() const {

    return m_proxy->rowCount();
}