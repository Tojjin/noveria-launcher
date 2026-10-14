#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "desktopentrymodel.h"
#include "desktopparser.h"
#include "desktopentrydelegate.h"

#include <QMainWindow>
#include <QLineEdit>
#include <QListView>

class MainWindow : public QMainWindow {

    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = nullptr);

private:

    QLineEdit* m_searchInput;
    QListView* m_appsView;
    DesktopEntryModel* m_model;
};

#endif // MAINWINDOW_H