import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Noveria

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
        color: Theme.background

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: Theme.spacing
            spacing: Theme.spacing

            TextField {
                Layout.fillWidth: true
                Layout.preferredHeight: 40
                placeholderText: "Search applications..."
                focus: true
                padding: 10
                color: Theme.text
                placeholderTextColor: Theme.textMuted
                font {
                    family: Theme.fontFamily
                    pixelSize: Theme.searchFontSize
                }
                background: Rectangle {
                    color: Theme.fieldBackground
                    border.color: Theme.fieldBorder
                    border.width: 2
                    radius: Theme.radius
                }
            }

            ListView {
                id: appsList
                Layout.fillWidth: true
                Layout.fillHeight: true
                clip: true
                spacing: 5
                model: Launcher.model

                delegate: Item {
                    id: delegateItem
                    required property string name

                    width: ListView.view.width
                    height: 60

                    Text {
                        anchors.fill: parent
                        anchors.leftMargin: 5
                        verticalAlignment: Text.AlignVCenter
                        text: delegateItem.name
                        color: Theme.text
                        font {
                            family: Theme.fontFamily
                            pixelSize: Theme.appsNameFontSize
                        }
                        elide: Text.ElideRight
                    }
                }
            }
        }
    }
}
