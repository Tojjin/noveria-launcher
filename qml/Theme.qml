pragma Singleton

import QtQuick

QtObject {
    //Ui colors
    readonly property color launcherBorder: "#70ffffff"
    readonly property color background: "#802a2a2a"
    readonly property color fieldBackground: "#14ffffff"
    readonly property color fieldBorder: "#ffffff"
    readonly property color text: "#ffffff"
    readonly property color textMuted: "#656565"
    readonly property color textSelected: "#000000"
    readonly property color accent: "#3daee9"
    readonly property color scrollBar: "#40ffffff"

    //Launcher window properties
    readonly property int launcherHeight: 510
    readonly property int launcherWidth: 540
    readonly property int launcherBorderWidth: 1
    readonly property int launcherRadius: 10

    //Launcher style properties for Ui elements
    readonly property int radius: 5
    readonly property int spacing: 10
    readonly property int textFieldBorderWidth: 2

    //Text font properties
    readonly property string fontFamily: "JetBrainsMono Nerd Font Propo"
    readonly property int searchFontSize: 14
    readonly property int appsNameFontSize: 13
    readonly property int appsCommentFontSize: 12

    //Icon properties
    readonly property int iconSize : 40
    readonly property int iconSourceSize: 64

    //ScrollBar properties
    readonly property int scrollBarWidth: 10
    readonly property int scrollBarStaticWidth: 5
}