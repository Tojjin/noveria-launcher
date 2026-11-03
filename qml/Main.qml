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
                id: searchField
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
                onTextChanged: Launcher.query = text
            }

            ListView {
                id: appsList
                Layout.fillWidth: true
                Layout.fillHeight: true
                clip: true
                spacing: 5
                model: Launcher.model
                visible: Launcher.resultCount > 0

                delegate: Item {
                    id: delegateItem
                    required property string name
                    required property string iconName

                    width: ListView.view.width
                    height: 50

                    Image {
                        id: appIcon
                        anchors.left: parent.left
                        anchors.leftMargin: Theme.spacing
                        anchors.verticalCenter: parent.verticalCenter
                        width: 32
                        height: 32
                        sourceSize: Qt.size(32, 32)
                        fillMode: Image.PreserveAspectFit
                        source: "image://icons/" + delegateItem.iconName
                    }

                    Text {
                        anchors.left: appIcon.right
                        anchors.leftMargin: Theme.spacing
                        anchors.right: parent.right
                        anchors.verticalCenter: parent.verticalCenter
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

            Text {
                Layout.fillWidth: true
                Layout.fillHeight: true
                visible: Launcher.resultCount === 0
                text: "Nothing found"
                color: Theme.textMuted
                verticalAlignment: Text.AlignTop
                topPadding: 5
                font {
                    family: Theme.fontFamily
                    pixelSize: Theme.searchFontSize
                }
            }
        }
    }
}
