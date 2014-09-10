#include "gtwikibusfetcher.h"
#include <QNetworkRequest>
#include <QXmlStreamReader>
#include <QDebug>

#include <geos/geom/Geometry.h>
#include <geos/geom/GeometryFactory.h>
#include <geos/geom/PrecisionModel.h>
#include <geos/geom/CoordinateSequenceFactory.h>
#include <geos/geom/LineString.h>
#include <geos/operation/linemerge/LineSequencer.h>

GTWikiBusFetcher::GTWikiBusFetcher(QObject *parent) :
    QObject(parent),
    manager(new QNetworkAccessManager(this)),
    timer(new QTimer(this)),
    factory(new geos::geom::GeometryFactory(new geos::geom::PrecisionModel(), 4326))
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
    const geos::geom::CoordinateSequenceFactory* sequenceFactory = factory->getCoordinateSequenceFactory();
    QList<geos::geom::Coordinate> coordinates;
    QList< QSharedPointer<geos::geom::CoordinateSequence> > paths;

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

                    geos::geom::Coordinate coordinate;
                    coordinate.x = reader.attributes().value("lon").toDouble();
                    coordinate.y = reader.attributes().value("lat").toDouble();
                    coordinates.append(coordinate);
                    QSharedPointer<geos::geom::Point> point(factory->createPoint(coordinate));
                    stop.setCoordinate(point);

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
            } else if (reader.name() == QStringLiteral("point")) {
                geos::geom::Coordinate coordinate;
                coordinate.x = reader.attributes().value("lon").toDouble();
                coordinate.y = reader.attributes().value("lat").toDouble();
                coordinates.append(coordinate);
            }
            break;
        case QXmlStreamReader::EndElement:
            if (reader.name() == QStringLiteral("direction")) {
                route.getDirections().insert(direction.getTag(), direction);
                settingDirection = false;
            } else if (reader.name() == QStringLiteral("route")) {
                bool changesMade = true;
                while (paths.size() > 1 && changesMade) {
                    changesMade = false;
                    for (int i = 0; i < paths.size(); i++) {
                        QSharedPointer<geos::geom::CoordinateSequence> path1 = paths.at(i);
                        for (int j = i + 1; j < paths.size(); j++) {
                            QSharedPointer<geos::geom::CoordinateSequence> path2 = paths.at(j);
                            if (path1->front().equals2D(path2->back())) {
                                for (int k = path2->size() - 1; k >= 0; k--) {
                                    path1->add(0, path2->getAt(k), false);
                                }
                                paths.removeAt(j);
                                j--;
                                changesMade = true;
                            } else if (path1->back().equals2D(path2->front())) {
                                for (int k = 0; k < path2->size(); k++) {
                                    path1->add(path2->getAt(k), false);
                                }
                                paths.removeAt(j);
                                j--;
                                changesMade = true;
                            }
                        }
                    }
                }
                Q_ASSERT(paths.size() == 1);

                routes.append(route);
            } else if (reader.name() == QStringLiteral("path")) {
                QSharedPointer<geos::geom::CoordinateSequence> sequence(sequenceFactory->create(
                            (std::vector<geos::geom::Coordinate>*) NULL, 2));
                for (int i = 0; i < coordinates.size(); i++) {
                    sequence->add(coordinates.at(i));
                }
                paths.append(sequence);
                coordinates.clear();
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
