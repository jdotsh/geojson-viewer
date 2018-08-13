import QtQuick 2.11
import QtPositioning 5.12
import QtLocation 5.12
import Qt.labs.qmlmodels 1.0

DelegateComponent {    
    id: dc
    role: "type"
    DelegateChoice {
        roleValue: "Point"
        delegate: MapCircle {
            geoShape: modelData.data
            radius: 100000
            color: "red"
        }
    }
    DelegateChoice {
        roleValue: "LineString"
        delegate: MapPolyline {
            geoShape: modelData.data
            line.color: "black"
            line.width: 1
        }
    }
    DelegateChoice {
        roleValue: "Polygon"
        delegate: MapPolygon {
            geoShape: modelData.data
            color: "red"
            opacity: 0.50
        }
    }
    DelegateChoice {
        roleValue: "MultiPoint"
        delegate: MapItemView {
            model: modelData.data
            delegate: dc
        }
    }
    DelegateChoice {
        roleValue: "MultiLinestring"
        delegate: MapItemView {
            model: modelData.data
            delegate: dc
        }
    }
    DelegateChoice {
        roleValue: "MultiPolygon"
        delegate: MapItemView {
            model: modelData.data
            delegate: dc
        }
    }
}
