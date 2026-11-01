import QtQuick

Window {
    width: 540
    height: 510
    minimumWidth: 540
    minimumHeight: 510
    maximumWidth: 540
    maximumHeight: 510

    visible: true
    title: "Noveria Launcher"
    flags: Qt.FramelessWindowHint | Qt.WindowStaysOnTopHint
    color: "transparent"

    Rectangle {
        anchors.fill: parent
        color: "#1e1e1e"
    }
}
