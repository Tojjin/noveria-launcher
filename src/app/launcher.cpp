#include "launcher.h"

#include "core/desktopparser.h"
#include "core/desktopentrymodel.h"
#include "core/desktopentryproxymodel.h"

Launcher::Launcher(QObject* parent) : QObject(parent), m_model(new DesktopEntryModel(DesktopParser().parseAll(), this)), m_proxy(new DesktopEntryProxyModel(this)) {
    m_proxy->setSourceModel(m_model);
    m_proxy->sort(0, Qt::AscendingOrder);
}

QAbstractItemModel* Launcher::model() const {

    return m_proxy;
}