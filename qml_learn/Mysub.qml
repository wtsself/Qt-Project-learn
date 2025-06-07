import QtQuick 2.12
import QtQuick.Window 2.12
import QtQuick.Controls 2.0
Item {
     property Component com
  property alias size: asss
    property int infa: 12
    Rectangle{
        id:asss
        width: 10
        height: 10
        color: "green"

    }

    Loader{
        id:da
        sourceComponent: com
    }



}
