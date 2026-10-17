#include "mainwindow.h"

#include <QVBoxLayout>

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

    connect(m_searchInput, &QLineEdit::textChanged, m_proxy, &DesktopEntryProxyModel::setQuery);
    connect(m_proxy, &DesktopEntryProxyModel::filterUpdated, this, [this]() {
        if (m_proxy->rowCount() > 0) {
            m_appsView->setCurrentIndex(m_proxy->index(0, 0));
        }
    });

}