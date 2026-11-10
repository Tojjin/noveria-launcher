#ifndef THEME_H
#define THEME_H

#include <QColor>
#include <QObject>
#include <QString>
#include <QtQml/qqmlregistration.h>

class Theme : public QObject {

    Q_OBJECT

    QML_ELEMENT
    QML_SINGLETON

    Q_PROPERTY(int launcherWidth MEMBER m_launcherWidth CONSTANT)
    Q_PROPERTY(int launcherHeight MEMBER m_launcherHeight CONSTANT)
    Q_PROPERTY(int launcherRadius MEMBER m_launcherRadius CONSTANT)
    Q_PROPERTY(int launcherBorderWidth MEMBER m_launcherBorderWidth CONSTANT)

    Q_PROPERTY(QColor background MEMBER m_background CONSTANT)
    Q_PROPERTY(QColor launcherBorder MEMBER m_launcherBorder CONSTANT)
    Q_PROPERTY(QColor fieldBackground MEMBER m_fieldBackground CONSTANT)
    Q_PROPERTY(QColor fieldBorder MEMBER m_fieldBorder CONSTANT)
    Q_PROPERTY(QColor text MEMBER m_text CONSTANT)
    Q_PROPERTY(QColor textMuted MEMBER m_textMuted CONSTANT)
    Q_PROPERTY(QColor textSelected MEMBER m_textSelected CONSTANT)
    Q_PROPERTY(QColor accent MEMBER m_accent CONSTANT)
    Q_PROPERTY(QColor scrollBar MEMBER m_scrollBar CONSTANT)

    Q_PROPERTY(QString fontFamily MEMBER m_fontFamily CONSTANT)
    Q_PROPERTY(int searchFontSize MEMBER m_searchFontSize CONSTANT)
    Q_PROPERTY(int appsNameFontSize MEMBER m_appsNameFontSize CONSTANT)
    Q_PROPERTY(int appsCommentFontSize MEMBER m_appsCommentFontSize CONSTANT)

    Q_PROPERTY(int radius MEMBER m_radius CONSTANT)
    Q_PROPERTY(int spacing MEMBER m_spacing CONSTANT)
    Q_PROPERTY(int textFieldBorderWidth MEMBER m_textFieldBorderWidth CONSTANT)
    Q_PROPERTY(int searchFieldHeight MEMBER m_searchFieldHeight CONSTANT)
    Q_PROPERTY(int searchFieldPadding MEMBER m_searchFieldPadding CONSTANT)
    Q_PROPERTY(int listSpacing MEMBER m_listSpacing CONSTANT)
    Q_PROPERTY(int itemHeight MEMBER m_itemHeight CONSTANT)
    Q_PROPERTY(int scrollBarWidth MEMBER m_scrollBarWidth CONSTANT)
    Q_PROPERTY(int scrollBarStaticWidth MEMBER m_scrollBarStaticWidth CONSTANT)
    Q_PROPERTY(int iconSize MEMBER m_iconSize CONSTANT)
    Q_PROPERTY(int iconSourceSize MEMBER m_iconSourceSize CONSTANT)

public:

    explicit Theme(QObject* parent = nullptr);

private:

    void loadConfig();

    int m_launcherWidth = 540;
    int m_launcherHeight = 510;
    int m_launcherRadius = 10;
    int m_launcherBorderWidth = 1;

    QColor m_background{QStringLiteral("#802a2a2a")};
    QColor m_launcherBorder{QStringLiteral("#70ffffff")};
    QColor m_fieldBackground{QStringLiteral("#14ffffff")};
    QColor m_fieldBorder{QStringLiteral("#ffffff")};
    QColor m_text{QStringLiteral("#ffffff")};
    QColor m_textMuted{QStringLiteral("#656565")};
    QColor m_textSelected{QStringLiteral("#000000")};
    QColor m_accent{QStringLiteral("#3daee9")};
    QColor m_scrollBar{QStringLiteral("#40ffffff")};

    QString m_fontFamily{QStringLiteral("JetBrainsMono Nerd Font Propo")};
    int m_searchFontSize = 14;
    int m_appsNameFontSize = 13;
    int m_appsCommentFontSize = 12;

    int m_radius = 5;
    int m_spacing = 10;
    int m_textFieldBorderWidth = 2;
    int m_searchFieldHeight = 40;
    int m_searchFieldPadding = 10;
    int m_listSpacing = 5;
    int m_itemHeight = 50;
    int m_scrollBarWidth = 10;
    int m_scrollBarStaticWidth = 5;
    int m_iconSize = 40;
    int m_iconSourceSize = 64;
};

#endif // THEME_H
