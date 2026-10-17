#include "mainwindow.h"

#include <QVBoxLayout>
#include <QKeyEvent>
#include <QRegularExpression>
#include <QProcess>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

    setFixedSize(QSize(540,510));

    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    setAttribute(Qt::WA_TranslucentBackground);

    QWidget* central = new QWidget(this);
    setCentralWidget(central);
    central->setObjectName("central");
    QVBoxLayout* layout = new QVBoxLayout(central);

    m_searchInput = new QLineEdit(this);
    m_appsView = new QListView(this);

    m_searchInput->installEventFilter(this);

    m_searchInput->setPlaceholderText("Search applications...");
    m_searchInput->setFocus();

    m_appsView->setUniformItemSizes(true);
    m_appsView->setSelectionMode(QAbstractItemView::SingleSelection);
    m_appsView->setMouseTracking(true);
    m_appsView->setContentsMargins(0, 0, 0, 0);
    m_appsView->setItemDelegate(new DesktopEntryDelegate(this));

    layout->addWidget(m_searchInput);
    layout->addWidget(m_appsView);
    layout->setContentsMargins(0, 0, 0, 0);

    DesktopParser parser;
    QList<DesktopEntry> entries = parser.parseAll();

    m_model = new DesktopEntryModel(entries,this);
    m_proxy = new DesktopEntryProxyModel(this);
    m_proxy->setSourceModel(m_model);
    m_appsView->setModel(m_proxy);
    m_appsView->setCurrentIndex(m_proxy->index(0, 0));

    connect(m_searchInput, &QLineEdit::textChanged, m_proxy, &DesktopEntryProxyModel::setQuery);

    connect(m_proxy, &DesktopEntryProxyModel::filterUpdated, this, [this]() {
        if (m_proxy->rowCount() > 0) {
            m_appsView->setCurrentIndex(m_proxy->index(0, 0));
        }
    });

    connect(m_appsView, &QListView::clicked, this, &MainWindow::launchApplication);
    connect(m_searchInput, &QLineEdit::returnPressed, this, [this]() {
        launchApplication(m_appsView->currentIndex());
    });
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event) {

    if (watched == m_searchInput && event->type() == QEvent::KeyPress) {

        QKeyEvent* pressedKey = static_cast<QKeyEvent*>(event);

        if (pressedKey->key() == Qt::Key_Down) {

            int row = m_appsView->currentIndex().row();

            if (row + 1 < m_proxy->rowCount()) {
                m_appsView->setCurrentIndex(m_proxy->index(row + 1, 0));
            }

            return true;
        }
        if (pressedKey->key() == Qt::Key_Up) {

            int row = m_appsView->currentIndex().row();

            if (row > 0) {
                m_appsView->setCurrentIndex(m_proxy->index(row - 1, 0));
            }

            return true;
        }
    }

    return QMainWindow::eventFilter(watched, event);
}

void MainWindow::launchApplication(const QModelIndex &index) {

    if (!index.isValid()) {
        return;
    }

    QString exec = index.data(ExecRole).value<QString>();
    static const QRegularExpression placeholderRegex("%[fFuUick]");
    exec.remove(placeholderRegex);
    exec = exec.trimmed();

    if (exec.isEmpty()) {
        return;
    }

    QStringList parts = QProcess::splitCommand(exec);

    if(parts.isEmpty()) {
        return;
    }

    QString app = parts.takeFirst();
    QStringList args = parts;

    QProcess::startDetached(app, args);
    close();
}