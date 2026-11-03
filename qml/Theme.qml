pragma Singleton

import QtQuick

QtObject {
    readonly property color background: "#c81e1e1e"
    readonly property color fieldBackground: "#14ffffff"
    readonly property color fieldBorder: "#ffffff"
    readonly property color text: "#ffffff"
    readonly property color textMuted: "#646464"
    readonly property color accent: "#3daee9"

    readonly property int radius: 5
    readonly property int spacing: 10
    readonly property int searchFontSize: 14
    readonly property int appsNameFontSize: 14
    readonly property int appsCommentFontSize: 10

    readonly property string fontFamily: "JetBrainsMono Nerd Font Propo"
}
