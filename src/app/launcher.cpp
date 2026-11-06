#include <QProcess>
#include <QRegularExpression>

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

bool Launcher::launch(int row) const {

    const QModelIndex index = m_proxy->index(row, 0);

    if (!index.isValid()) {
        return false;
    }

    QString exec = index.data(ExecRole).value<QString>();
    static const QRegularExpression placeholderRegex("%[fFuUdDnNickvm]");
    exec.remove(placeholderRegex);
    exec = exec.trimmed();

    if (exec.isEmpty()) {
        return false;
    }

    QStringList parts = QProcess::splitCommand(exec);

    if (parts.isEmpty()) {
        return false;
    }

    QString app = parts.takeFirst();
    QStringList args = parts;

    return QProcess::startDetached(app, args);
}