#include "mainwindow.h"

#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {

    setFixedSize(QSize(540,600));

    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint);

    setAttribute(Qt::WA_TranslucentBackground);

    QWidget* central = new QWidget(this);
    setCentralWidget(central);
    QVBoxLayout* layout = new QVBoxLayout(central);

    m_searchInput = new QLineEdit(this);
    m_appsView = new QListView(this);

    m_searchInput->setText("Search applications...");

    m_appsView->setUniformItemSizes(true);
    m_appsView->setSelectionMode(QAbstractItemView::SingleSelection);

    layout->addWidget(m_searchInput);
    layout->addWidget(m_appsView);

    DesktopParser parser;
    QList<DesktopEntry> entries = parser.parseAll();

    m_model = new DesktopEntryModel(entries,this);
    m_appsView->setModel(m_model);
}