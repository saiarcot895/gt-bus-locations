#include "gtwikibusfetcher.h"
#include <QNetworkRequest>
#include <QXmlStreamReader>
#include <QDebug>

GTWikiBusFetcher::GTWikiBusFetcher(QObject *parent) :
    QObject(parent),
    manager(new QNetworkAccessManager(this))
{
    routeConfigReply = manager->get(QNetworkRequest(
                                        QUrl("http://gtwiki.info/nextbus/nextbus.php?a=georgia-tech&command=routeConfig")));
    connect(routeConfigReply, SIGNAL(finished()), this, SLOT(readRouteConfig()));
    connect(routeConfigReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(readRouteConfig()));
}

void GTWikiBusFetcher::readRouteConfig() {
    if (routeConfigReply->error() != QNetworkReply::NoError) {
        qCritical() << "Error occurred: " + routeConfigReply->errorString();
        return;
    }

    QXmlStreamReader reader(routeConfigReply->readAll());
    if (reader.hasError()) {
        qCritical() << "Error parsing route config XML: " + reader.errorString();
        return;
    }

    Route route;
    Direction direction;
    bool settingDirection = false;

    while (!reader.atEnd()) {
        switch (reader.readNext()) {
        case QXmlStreamReader::StartElement:
            if (reader.name() == QStringLiteral("route")) {
                route = Route();
                route.setRouteName(reader.attributes().value("title").toString());
                route.setTag(reader.attributes().value("tag").toString());
                route.setColor(QColor(reader.attributes().value("color").toUInt(NULL, 16)));
            } else if (reader.name() == QStringLiteral("stop")) {
                if (!settingDirection) {
                    Stop stop;
                    stop.setStopName(reader.attributes().value("title").toString());
                    stop.setTag(reader.attributes().value("tag").toString());
                    stop.setLatitude(reader.attributes().value("lat").toDouble());
                    stop.setLongitude(reader.attributes().value("lon").toDouble());
                    route.getStops().insert(stop.getTag(), stop);
                } else {
                    direction.getStops().append(
                                route.getStops().value(
                                    reader.attributes().value("tag").toString()));
                }
            } else if (reader.name() == QStringLiteral("direction")) {
                direction = Direction();
                direction.setDirectionName(reader.attributes().value("title").toString());
                direction.setTag(reader.attributes().value("tag").toString());
                settingDirection = true;
            }
            break;
        case QXmlStreamReader::EndElement:
            if (reader.name() == QStringLiteral("direction")) {
                route.getDirections().insert(direction.getTag(), direction);
            } else if (reader.name() == QStringLiteral("route")) {
                routes.append(route);
            }
            break;
        default:
            break;
        }
    }

    emit loadingDone();
}

QList<Route> GTWikiBusFetcher::getRoutes() const {
    return routes;
}
