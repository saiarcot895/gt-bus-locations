#include "gtwikibusfetcher.h"
#include <QNetworkRequest>
#include <QXmlStreamReader>
#include <QDebug>

GTWikiBusFetcher::GTWikiBusFetcher(QObject *parent) :
    QObject(parent),
    manager(new QNetworkAccessManager(this)),
    timer(new QTimer(this))
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
                    QString tag = reader.attributes().value("tag").toString();
                    Stop stop = route.getStops().value(tag);
                    direction.getStops().append(stop);
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
                settingDirection = false;
            } else if (reader.name() == QStringLiteral("route")) {
                routes.append(route);
            }
            break;
        default:
            break;
        }
    }

    emit loadingDone();

    disconnect(routeConfigReply, SIGNAL(finished()), this, SLOT(readRouteConfig()));
    disconnect(routeConfigReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(readRouteConfig()));

    connect(timer, SIGNAL(timeout()), this, SLOT(refreshWaitTimes()));
    connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(readWaitTimes(QNetworkReply*)));

    refreshWaitTimes();

    timer->start(15000);
}

void GTWikiBusFetcher::refreshWaitTimes() {
    for (int i = 0; i < routes.size(); i++) {
        Route route = routes.at(i);
        manager->get(QNetworkRequest(QUrl(QStringLiteral("http://gtwiki.info/nextbus/nextbus.php?"
                                                         "a=georgia-tech&command=predictionsForMultiStops&r=%1").arg(route.getTag()))));
    }
}

void GTWikiBusFetcher::readWaitTimes(QNetworkReply *reply) {
    if (reply->error() != QNetworkReply::NoError) {
        qCritical() << "Error occurred: " + reply->errorString();
        return;
    }

    QXmlStreamReader reader(reply->readAll());
    if (reader.hasError()) {
        qCritical() << "Error parsing stop prediction XML: " + reader.errorString();
        return;
    }

    QString routeTag;
    QString stopTag;
    Stop stop;

    while (!reader.atEnd()) {
        switch (reader.readNext()) {
        case QXmlStreamReader::StartElement:
            if (reader.name() == QStringLiteral("predictions")) {
                routeTag = reader.attributes().value("routeTag").toString();
                stopTag = reader.attributes().value("stopTag").toString();

                for (int i = 0; i < routes.size(); i++) {
                    Route route = routes.at(i);
                    if (route.getTag() != routeTag) {
                        continue;
                    }

                    QList<Stop> stops = route.getStops().values();
                    for (int j = 0; j < stops.size(); j++) {
                        Stop routeStop = stops.at(j);
                        if (routeStop.getTag() == stopTag) {
                            stop = routeStop;
                            break;
                        }
                    }
                }

                stop.getStopTimes().clear();
            } else if (reader.name() == QStringLiteral("prediction")) {
                stop.getStopTimes().append(reader.attributes().value("seconds").toInt());
            }
            break;
        default:
            break;
        }
    }

    emit waitTimesUpdated(routeTag);
}

QList<Route> GTWikiBusFetcher::getRoutes() const {
    return routes;
}
