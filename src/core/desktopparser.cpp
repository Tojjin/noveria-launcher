#include "desktopparser.h"

#include <QStandardPaths>
#include <QFile>
#include <QTextStream>
#include <QDir>

DesktopParser::DesktopParser() : m_directories(QStandardPaths::standardLocations(QStandardPaths::ApplicationsLocation)) {}

QList<DesktopEntry> DesktopParser::parseAll() const {

    QList<DesktopEntry> entries;

    for (const auto& path : m_directories) {

        QDir dir(path);

        if(!dir.exists()) {
            continue;
        }

        QStringList fileNames = dir.entryList({"*.desktop"}, QDir::Files);

        for (const auto& name : fileNames) {

            const QString fullPath = dir.absoluteFilePath(name);

            DesktopEntry entry = parseFile(fullPath);

            if (entry.isValid() && !entry.noDisplay) {
                entries.append(entry);
            }
        }
    }

    return entries;
}

DesktopEntry DesktopParser::parseFile(const QString &path) const {

    DesktopEntry entry;

    QFile desktopFile(path);
    if (!desktopFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return entry;
    }

    QTextStream in(&desktopFile);
    bool inDesktopEntry = false;

    while(!in.atEnd()) {

        const QString line = in.readLine();
        const QString trimmedLine = line.trimmed();

        if (trimmedLine.startsWith('[')) {

            const QString desktopSection = trimmedLine.sliced(1, trimmedLine.size() - 2);

            inDesktopEntry = (desktopSection == "Desktop Entry");

            continue;
        }

        if (inDesktopEntry) {
            parseLine(line, entry);
        }
    }

    return entry;
}

void DesktopParser::parseLine(const QString &line, DesktopEntry &entry) const {

    if (line.trimmed().isEmpty()) {
        return;
    }
    if (line.trimmed().startsWith("#")) {
        return;
    }
    if (line.trimmed().startsWith("[")) {
        return;
    }

    const int equalsPos = line.indexOf('=');
    if (equalsPos == -1) {
        return;
    }

    const QString key = line.left(equalsPos).trimmed();
    const QString value = line.mid(equalsPos + 1).trimmed();

    if (key.contains('[')) {
        return;
    }
    if (key == "Name") {
        entry.name = value;
    }
    else if (key == "GenericName") {
        entry.genericName = value;
    }
    else if (key == "Comment") {
        entry.comment = value;
    }
    else if (key == "Exec") {
        entry.exec = value;
    }
    else if (key == "Icon") {
        entry.icon = value;
    }
    else if (key == "Terminal") {
        entry.terminal = (value == "true");
    }
    else if (key == "NoDisplay") {
        entry.noDisplay = (value == "true");
    }
    else if (key == "Keywords") {
        entry.keywords = value.split(';', Qt::SkipEmptyParts);
    }
    else if (key == "Categories") {
        entry.categories = value.split(';', Qt::SkipEmptyParts);
    }
}