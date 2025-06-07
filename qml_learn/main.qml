import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")



Component{
    id:w
    Button{

        width: 25
        height: 25

        ColorAnimation {
            from: "white"
            to: "black"
            duration: 2000
        }
    }
}


Mysub{
    com: w
size.width: 100
}




















}
