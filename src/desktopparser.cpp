#include "desktopparser.h"
#include <QStandardPaths>

DesktopParser::DesktopParser() : m_directories(QStandardPaths::standardLocations(QStandardPaths::ApplicationsLocation)) {}