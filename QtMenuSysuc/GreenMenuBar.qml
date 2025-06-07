import QtQuick 2.5
import QtQuick.Controls 2.5
//改键是qml的一个组件，用于创建菜单栏中的项
MenuBarItem{
    id:myMenuBarItem
    width: 120
    height: 40
    //系统字体设置
    font:Qt.font({
                     family:"微软雅黑",
                     pointSize:10,
                     weight:Font.Bold
                 } )
    //系统颜色设置
    //contentItem是一个内置属性，表示菜单的内容项
    contentItem: Text {
        id: myContentItem
        text: myMenuBarItem.text
        font: myMenuBarItem.font
//透明度
        opacity: enabled?1.0:3.0
        color: "white"
    horizontalAlignment: Text.AlignHCenter
    verticalAlignment: Text.AlignVCenter
    //指定文本溢出时如何截断文本
    elide: Text.ElideRight//文本超出控件右侧部分被截断
    }


    //背景颜色设置-
    //rectangle矩形元素，用于创建一个可视化的矩形区域
    background: Rectangle{
        implicitHeight: 40//设置组件的隐式高度
        implicitWidth: 30
        opacity: enabled?1.0:3.0
        //将myMenuBarItem对象在高亮状态下的背景颜色设置为黄绿色，非高亮状态下为透明
        color: myMenuBarItem.highlighted?"yellowgreen":"transparent"
    }

}
