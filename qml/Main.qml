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

    MouseArea {
        id: dragCursorOverlay
        anchors.fill: parent
        z: 9999
        visible: scrollbar.pressed
        hoverEnabled: true
        acceptedButtons: Qt.NoButton
        cursorShape: Qt.PointingHandCursor
    }

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

                boundsBehavior: Flickable.StopAtBounds
                acceptedButtons: Qt.NoButton

                ScrollBar.vertical: ScrollBar {
                    id: scrollbar
                    policy: ScrollBar.AsNeeded
                    visible: scrollbar.size < 1.0
                    width: Theme.scrollBarWidth
                    padding: 0
                    minimumSize: 0.08

                    contentItem: Rectangle {
                        width: parent.width
                        radius: Theme.scrollBarWidth / 2
                        color: Theme.scrollBar

                        HoverHandler {
                            cursorShape: Qt.PointingHandCursor
                        }
                    }

                    background: Rectangle {
                        width: parent.width
                        height: parent.height
                        radius: Theme.scrollBarWidth / 2
                        color: Theme.fieldBackground
                    }
                }

                delegate: Item {
                    id: delegateItem
                    required property string name
                    required property string comment
                    required property string genericName
                    required property string iconName

                    readonly property string commentText: {
                        const t_comment = delegateItem.comment.trim();
                        return t_comment !== "" ? t_comment : delegateItem.genericName.trim()
                    }

                    width: scrollbar.visible ? ListView.view.width - Theme.scrollBarWidth - 5 : ListView.view.width
                    height: 50

                    Rectangle {
                        anchors.fill: parent
                        radius: Theme.radius
                        color: itemHover.hovered ? Theme.accent : "transparent"

                        MouseArea {
                            anchors.fill: parent
                            cursorShape: Qt.PointingHandCursor
                        }
                    }

                    HoverHandler {
                        id: itemHover
                    }

                    Image {
                        id: appIcon
                        anchors.left: parent.left
                        anchors.leftMargin: Theme.spacing
                        anchors.verticalCenter: parent.verticalCenter
                        width: Theme.iconSize
                        height: Theme.iconSize
                        sourceSize: Qt.size(Theme.iconSourceSize, Theme.iconSourceSize)
                        fillMode: Image.PreserveAspectFit
                        source: "image://icons/" + delegateItem.iconName
                    }

                    Column {
                        anchors.left: appIcon.right
                        anchors.leftMargin: Theme.spacing
                        anchors.right: parent.right
                        anchors.rightMargin: Theme.spacing
                        anchors.verticalCenter: parent.verticalCenter

                        Text {
                            id: nameText
                            width: parent.width
                            text: delegateItem.name
                            color: itemHover.hovered ? Theme.textSelected : Theme.text
                            font {
                                family: Theme.fontFamily
                                pixelSize: Theme.appsNameFontSize
                            }
                            elide: Text.ElideRight
                        }

                        Text {
                            id: commentText
                            width: parent.width
                            text: delegateItem.commentText
                            visible: text.length > 0
                            color: Theme.textMuted
                            font {
                                family: Theme.fontFamily
                                pixelSize: Theme.appsCommentFontSize
                            }
                            elide: Text.ElideRight
                        }
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
