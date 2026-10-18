#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "desktopentrymodel.h"
#include "desktopparser.h"
#include "desktopentrydelegate.h"
#include "desktopentryproxymodel.h"

#include <QMainWindow>
#include <QLineEdit>
#include <QListView>
#include <QLabel>

class MainWindow : public QMainWindow {

    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = nullptr);

private:

    void launchApplication(const QModelIndex& index);

    QLineEdit* m_searchInput;
    QListView* m_appsView;
    QLabel* m_emptyLabel;
    DesktopEntryModel* m_model;
    DesktopEntryProxyModel* m_proxy;

protected:

    bool eventFilter(QObject *watched, QEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
};

#endif // MAINWINDOW_H