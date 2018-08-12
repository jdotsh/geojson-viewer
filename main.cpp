#include <QDebug>
#include <QFile>
#include <QGuiApplication>
#include <QJsonDocument>
#include <QQmlApplicationEngine>
#include <QVariantMap>
#include <QQmlContext>
#include <QtLocation/private/qgeojson_p.h>
#include <QGeoCircle>
#include <QGeoPath>
#include <QGeoPolygon>

const QString QGeoJsonPrettyPrint(const QVariant &variantItem)
{
    QJsonDocument doc;
    doc= QJsonDocument::fromVariant(variantItem);
    QString str = doc.toJson(QJsonDocument::Indented);
    return str;
}

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QJsonParseError err;

    // char name[] = "/home/jdotsh/Projects/qmap-viewer/testdata/ ... ";

    // Reading GeoJSON file
    if (argc < 2) {
        printf("Usage: %s file.json", argv[0]);
        return -1;
    }

    QFile loadFile(argv[1]);
    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning() << "Couldn't open" << argv[1];
        return -2;
    }

    // Load the GeoJSON file using Qt's API
    QJsonDocument loadDoc(QJsonDocument::fromJson(loadFile.readAll(), &err));
    if (err.error) {
         qWarning() << "Error parsing while importing the JSON document:\n" << err.errorString();
         return -2;
    }

    // Import geographic data to a QVariantMap
    QVariantMap modelMap = QGeoJson::importGeoJson(loadDoc);
    qWarning() << "File GeoJSON correclty imported\n";
    QVariantList modelList;
    modelList.append(modelMap);


    // Output a file with the QVariantMap structure

    /*
    QFile saveFile(argv[2]);
    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning() << "Couldn't open to write";
        return -3;
    }
    QVariant prettyfied = QVariant::fromValue(modelMap);
    QTextStream out(&saveFile);
    out << QGeoJsonPrettyPrint(prettyfied);
    saveFile.close();
    */


    // Show point coordinates

    /*
    QList<QGeoCoordinate> coordsValue;
    coordsValue = modelMap.value("data").value<QGeoPath>().path();
    qDebug() << "Coordinate del Point:\n" << coordsValue;
    */

    // Switch to QML app
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("geoJsonModel", modelList);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
