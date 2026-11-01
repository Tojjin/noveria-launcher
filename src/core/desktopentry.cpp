#include "desktopentry.h"

bool DesktopEntry::isValid() const {
    return !name.trimmed().isEmpty() && !exec.trimmed().isEmpty();
}