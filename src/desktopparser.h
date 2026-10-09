#ifndef DESKTOPPARSER_H
#define DESKTOPPARSER_H

#include "desktopentry.h"
#include <QList>
#include <QString>
#include <QStringList>

class DesktopParser {

public:

    DesktopParser();

    QList<DesktopEntry> parseAll() const;

private:

    QStringList m_directories;

    DesktopEntry parseFile(const QString& path) const;
    void parseLine(const QString& line, DesktopEntry& entry) const;
};

#endif // DESKTOPPARSER_H
