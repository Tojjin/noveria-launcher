#include "desktopentry.h"

bool DesktopEntry::isValid() const {
    return !name.trimmed().isEmpty() && !exec.trimmed().isEmpty();
}

bool DesktopEntry::hasComment() const {
    return !comment.trimmed().isEmpty();
}
