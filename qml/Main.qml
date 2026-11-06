import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import Noveria

//Root window of the launcher
Window {
    id: root
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

    function moveSelection(delta) {

        if (appsList.count === 0) {
            return
        }

        const next = appsList.currentIndex + delta

        if (next < 0 || next >= appsList.count) {
            return
        }

        appsList.currentIndex = next
        appsList.positionViewAtIndex(next, ListView.Contain)
    }

    function launchCurrent() {
        if (Launcher.launch(appsList.currentIndex)) {
            root.close()
        }
    }

    //Crutch to make it so the mouse cursor always stays as a pointing finger
    //after grabbing scrollbar thumb even if it move over other elements of the UI
    MouseArea {
        id: dragCursorOverlay
        anchors.fill: parent
        z: 9999
        visible: scrollbar.pressed
        hoverEnabled: true
        acceptedButtons: Qt.NoButton
        cursorShape: Qt.PointingHandCursor
    }

    //Launcher background
    Rectangle {
        anchors.fill: parent
        color: Theme.background

        ColumnLayout {
            anchors.fill: parent
            anchors.margins: Theme.spacing
            spacing: Theme.spacing

            //Search field
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

                onTextChanged: {
                    Launcher.query = text
                    appsList.currentIndex = 0
                    appsList.positionViewAtBeginning()
                }

                onAccepted: root.launchCurrent()

                Keys.onDownPressed: (event) => {
                    root.moveSelection(1)
                    event.accepted = true
                }

                Keys.onUpPressed: (event) => {
                    root.moveSelection(-1)
                    event.accepted = true
                }

                Keys.onEscapePressed: (event) => {
                    root.close()
                    event.accepted = true
                }
            }

            //List that shows all desktop applications
            ListView {
                id: appsList
                Layout.fillWidth: true
                Layout.fillHeight: true
                clip: true
                spacing: 5
                model: Launcher.model
                visible: Launcher.resultCount > 0

                ScrollBar.vertical: scrollbar

                boundsBehavior: Flickable.StopAtBounds
                acceptedButtons: Qt.NoButton

                currentIndex: 0

                //Custom delegate to properly draw the item with the icon, name and comment/generic name
                delegate: Item {
                    id: delegateItem
                    required property string name
                    required property string comment
                    required property string genericName
                    required property string iconName
                    required property int index

                    readonly property bool current: ListView.isCurrentItem

                    readonly property string commentText: {
                        const t_comment = delegateItem.comment.trim();
                        return t_comment !== "" ? t_comment : delegateItem.genericName.trim()
                    }

                    width: scrollbar.visible ? ListView.view.width - Theme.scrollBarWidth - 2 : ListView.view.width
                    height: 50

                    HoverHandler {
                        id: itemHover
                    }

                    //List view item background
                    Rectangle {
                        anchors.fill: parent
                        radius: Theme.radius
                        color: (itemHover.hovered || delegateItem.current) ? Theme.accent : "transparent"

                        MouseArea {
                            anchors.fill: parent
                            cursorShape: Qt.PointingHandCursor

                            onClicked: {
                                appsList.currentIndex = delegateItem.index
                                root.launchCurrent()
                            }
                        }
                    }

                    //List view item's icon
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

                    //Column layout for the name/comment text
                    Column {
                        anchors.left: appIcon.right
                        anchors.leftMargin: Theme.spacing
                        anchors.right: parent.right
                        anchors.rightMargin: Theme.spacing
                        anchors.verticalCenter: parent.verticalCenter

                        //Name of the application
                        Text {
                            id: nameText
                            width: parent.width
                            text: delegateItem.name
                            color: (itemHover.hovered || delegateItem.current) ? Theme.textSelected : Theme.text
                            font {
                                family: Theme.fontFamily
                                pixelSize: Theme.appsNameFontSize
                            }
                            elide: Text.ElideRight
                        }

                        //Comment of the application
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

            //Empty state behavior text box
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

            //Scrollbar for the List of applications
            ScrollBar {
                id: scrollbar
                anchors.top: appsList.top
                anchors.bottom: appsList.bottom
                anchors.right: appsList.right
                policy: ScrollBar.AsNeeded
                visible: scrollbar.size < 1.0
                width: scrollbar.hovered || scrollbar.pressed? Theme.scrollBarWidth : Theme.scrollBarStaticWidth
                padding: 0
                minimumSize: 0.08

                //Animation for smooth width change
                Behavior on width {
                    NumberAnimation {
                        duration: 100
                        easing.type: Easing.InOutQuad
                    }
                }

                //Scrollbar thumb
                contentItem: Rectangle {
                    radius: Theme.scrollBarWidth / 2
                    color: Theme.scrollBar

                    HoverHandler {
                        cursorShape: Qt.PointingHandCursor
                    }
                }

                //Scrollbar track
                background: Rectangle {
                    radius: Theme.scrollBarWidth / 2
                    color: Theme.fieldBackground
                }
            }
        }
    }
}