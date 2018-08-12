import QtQuick 2.11
import QtQuick.Window 2.11
import QtPositioning 5.12
import QtLocation 5.12
import Qt.labs.qmlmodels 1.0

Window {
    visible: true
    width: 1024
    height: 1024
    title: qsTr("GeoJSon Viewer")

    Map {
        id: map
        anchors.fill: parent
        plugin: Plugin { name: "osm" }
        center: QtPositioning.coordinate(44.0, 12.5) // me :)
        zoomLevel: 3

        MapItemView {
            id: miv
            model: geoJsonModel
            delegate: MapDelegate {

            }
        }
    }
}
