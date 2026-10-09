#ifndef DESKTOPENTRY_H
#define DESKTOPENTRY_H

#include <QString>
#include <QStringList>

struct DesktopEntry {

    QString name;
    QString comment;
    QString exec;
    QString icon;
    bool terminal = false;
    bool noDisplay = false;
    QStringList keywords;
    QStringList categories;

    bool isValid() const;
    bool hasComment() const;
};

#endif // DESKTOPENTRY_H
