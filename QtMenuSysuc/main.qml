import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.5


ApplicationWindow {
    visible: true
    width: 900
    height: 560
    title: qsTr("QML是实现下拉菜单")

    //创建一个菜单
    menuBar:MenuBar{
        Menu{
            title: qsTr("A")
            Action{text: qsTr("Bfasddddddddddd")}
            Action{text: qsTr("Cfaddddddddd")}
            Action{text: qsTr("Dfadssss")}
            Action{text: qsTr("fadssssE")}
            Action{text: qsTr("Ffads")}
            Action{text: qsTr("Gfadss")}
            Action{text: qsTr("Hfads")}
            Action{text: qsTr("Ifasd")}
//            delegate: GreenMenuItem{}
//            background: GreenMenuBarBg{}

        }
//        delegate: GreenMenuItem{}
//        background: GreenMenuBarBg{}
    }


}
