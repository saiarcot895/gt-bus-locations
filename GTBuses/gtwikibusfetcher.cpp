#include "gtwikibusfetcher.h"
#include <QGuiApplication>
#include <QNetworkRequest>
#include <QXmlStreamReader>
#include <QDebug>
#include <QThread>

#include <geos/geom/Geometry.h>
#include <geos/geom/GeometryFactory.h>
#include <geos/geom/PrecisionModel.h>
#include <geos/geom/CoordinateSequenceFactory.h>
#include <geos/geom/LineString.h>
#include <geos/operation/linemerge/LineSequencer.h>
#include <geos/operation/distance/DistanceOp.h>

#include "bus.h"

GTWikiBusFetcher::GTWikiBusFetcher(QObject *parent) :
    QObject(parent),
    manager(new QNetworkAccessManager(this)),
    routeConfigReply(NULL),
    timer(new QTimer(this)),
    factory(new geos::geom::GeometryFactory(new geos::geom::PrecisionModel(), 4326)),
    header(QStringLiteral("GT Bus Locations %1").arg(QGuiApplication::platformName()))
{
    getRouteConfig();
}

void GTWikiBusFetcher::getRouteConfig() {
    timer->stop();
    disconnect(timer, SIGNAL(timeout()), this, SLOT(getRouteConfig()));
    if (routeConfigReply != NULL) {
        disconnect(routeConfigReply, SIGNAL(finished()), this, SLOT(readRouteConfig()));
        disconnect(routeConfigReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(readRouteConfig()));
        routeConfigReply->deleteLater();
    }

    QNetworkRequest routeConfigRequest(QUrl(QStringLiteral("http://gtbuses.herokuapp.com/routeConfig")));
    routeConfigRequest.setHeader(QNetworkRequest::UserAgentHeader, header);
    routeConfigReply = manager->get(routeConfigRequest);
    connect(routeConfigReply, SIGNAL(finished()), this, SLOT(readRouteConfig()));
    connect(routeConfigReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(readRouteConfig()));
}

void GTWikiBusFetcher::readRouteConfig() {
    if (routeConfigReply->error() != QNetworkReply::NoError) {
        qCritical() << "Error occurred: " + routeConfigReply->errorString();
        routeConfigReply->deleteLater();
        routeConfigReply = NULL;
        connect(timer, SIGNAL(timeout()), this, SLOT(getRouteConfig()));
        timer->setSingleShot(true);
        timer->start(5000);
        return;
    }

    QXmlStreamReader reader(routeConfigReply->readAll());
    if (Q_UNLIKELY(reader.hasError())) {
        qCritical() << "Error parsing route config XML: " + reader.errorString();
        routeConfigReply->deleteLater();
        return;
    }

    Route route;
    Direction direction;
    bool settingDirection = false;
    const geos::geom::CoordinateSequenceFactory* sequenceFactory = factory->getCoordinateSequenceFactory();
    QList<geos::geom::Coordinate> coordinates;
    QList<geos::geom::CoordinateSequence*> paths;

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
                route.getStops().clear();

                bool changesMade = true;

                if (route.getTag() == "green") {
                    for (int i = 0; i < paths.size(); i++) {
                        geos::geom::CoordinateSequence* pathSequence = paths.at(i);
                        delete pathSequence;
                    }
                    paths.clear();

                    routes.append(route);
                    continue;
                }

                double accuracy = 1e-6;

                if (route.getTag() == "emory") {
                    // The stops for Emory are wide enough that this shouldn't have much of a negative impact
                    accuracy *= 10;
                }

                while (paths.size() > 1 && changesMade) {
                    changesMade = false;
                    for (int i = 0; i < paths.size(); i++) {
                        geos::geom::CoordinateSequence* path1 = paths.at(i);
                        for (int j = i + 1; j < paths.size(); j++) {
                            geos::geom::CoordinateSequence* path2 = paths.at(j);
                            if (qAbs((path1->front().x - path2->back().x) / path1->front().x) <= accuracy
                                    && qAbs((path1->front().y - path2->back().y) / path1->front().y) <= accuracy) {

                                for (int k = path2->size() - 1; k >= 0; k--) {
                                    path1->add(0, path2->getAt(k), false);
                                }

                                delete path2;
                                paths.removeAt(j);
                                j--;
                                changesMade = true;
                            } else if (qAbs((path1->back().x - path2->front().x) / path1->back().x) <= accuracy
                                       && qAbs((path1->back().y - path2->front().y) / path1->back().y) <= accuracy) {

                                for (int k = 0; k < path2->size(); k++) {
                                    path1->add(path2->getAt(k), false);
                                }

                                delete path2;
                                paths.removeAt(j);
                                j--;
                                changesMade = true;
                            }
                        }
                    }
                }

                for (int i = 0; i < paths.size(); i++) {
                    geos::geom::CoordinateSequence* path = paths.at(i);
                    if (path->size() <= 3 || path->size() == 19 /* GLC/Clough */) {
                        paths.removeAt(i);
                        i--;
                        delete path;
                    }
                }

                Q_ASSERT(paths.size() == 1);

                QSharedPointer<geos::geom::LineString> busPath(factory->createLineString(paths.first()));

                QList<Stop> stops;
                for (int i = 0; i < route.getDirections().values().size(); i++) {
                    Direction direction = route.getDirections().values().at(i);
                    stops += direction.getStops();
                }

                geos::geom::CoordinateSequence* startingCoordinates = geos::operation::distance
                        ::DistanceOp::nearestPoints(busPath.data(), stops.at(0).getCoordinate().data());
                int startingIndex = -1;
                for (int i = 0; i < startingCoordinates->size(); i++) {
                    geos::geom::Coordinate startingCoordinate = startingCoordinates->getAt(i);
                    for (int j = 0; j < busPath->getCoordinatesRO()->size(); j++) {
                        geos::geom::Coordinate stop = busPath->getCoordinateN(j);
                        if (qAbs((stop.x - startingCoordinate.x) / stop.x) <= accuracy * 10
                                && qAbs((stop.y - startingCoordinate.y) / stop.y) <= accuracy * 10) {
                            startingIndex = j;
                            break;
                        }
                    }

                    if (startingIndex != -1) {
                        break;
                    }
                }
                delete startingCoordinates;
                startingCoordinates = NULL;

                Q_ASSERT(startingIndex != -1);

                int previousIndex = startingIndex;
                for (int i = 1; i < stops.size(); i++) {
                    Stop prevStop = stops.at(i - 1);
                    Stop stop = stops.at(i);

                    geos::geom::CoordinateSequence* nearestCoordinates = geos::operation::distance
                            ::DistanceOp::nearestPoints(busPath.data(), stop.getCoordinate().data());

                    geos::geom::CoordinateSequence* sequence =
                            sequenceFactory->create((std::vector<geos::geom::Coordinate>*) NULL, 2);

                    for (int j = 0; j < nearestCoordinates->size(); j++) {
                        const geos::geom::Coordinate nearestCoordinate = nearestCoordinates->getAt(j);
                        sequence->add(busPath->getCoordinateN(previousIndex));
                        for (int k = previousIndex + 1; k < busPath->getCoordinatesRO()->size() + previousIndex; k++) {
                            const geos::geom::Coordinate busCoordinate = busPath->getCoordinateN(
                                        k % busPath->getCoordinatesRO()->size());
                            sequence->add(busCoordinate);
                            if (qAbs((busCoordinate.x - nearestCoordinate.x) / busCoordinate.x) <= accuracy * 10
                                    && qAbs((busCoordinate.y - nearestCoordinate.y) / busCoordinate.y) <= accuracy * 10) {
                                previousIndex = k % busPath->getCoordinatesRO()->size();
                                break;
                            }
                        }

                        if (sequence->size() > 1 &&
                                sequence->size() < busPath->getCoordinatesRO()->size() - 1) {
                            break;
                        } else {
                            delete sequence;
                            sequence = sequenceFactory->create(
                                        (std::vector<geos::geom::Coordinate>*) NULL, 2);
                        }
                    }
                    delete nearestCoordinates;
                    nearestCoordinates = NULL;

                    Q_ASSERT(sequence->size() > 1 && sequence->size() < busPath->getCoordinatesRO()->size());

                    QSharedPointer<geos::geom::LineString> stopPath(factory->createLineString(sequence));
                    prevStop.setDepartingSegment(stopPath);
                    stop.setArrivingSegment(stopPath);
                }

                geos::geom::CoordinateSequence* sequence =
                        sequenceFactory->create((std::vector<geos::geom::Coordinate>*) NULL, 2);

                for (int i = previousIndex; i != startingIndex; i++, i %= busPath->getCoordinatesRO()->size()) {
                    const geos::geom::Coordinate busCoordinate = busPath->getCoordinateN(i);
                    sequence->add(busCoordinate);
                }
                QSharedPointer<geos::geom::LineString> stopPath(factory->createLineString(sequence));
                stops.first().setArrivingSegment(stopPath);
                stops.last().setDepartingSegment(stopPath);

                paths.clear();

                routes.append(route);
            } else if (reader.name() == QStringLiteral("path")) {
                geos::geom::CoordinateSequence* sequence = sequenceFactory->create(
                            (std::vector<geos::geom::Coordinate>*) NULL, 2);
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

    routeConfigReply->deleteLater();

    connect(timer, SIGNAL(timeout()), this, SLOT(updateInfo()));

    updateInfo();

    timer->setSingleShot(false);
    timer->start(5000);
}

void GTWikiBusFetcher::updateInfo() {
    for (int i = 0; i < routes.size(); i++) {
        Route route = routes.at(i);

        QNetworkRequest waitTimeRequest(QUrl(QStringLiteral("https://gtbuses.herokuapp.com/predictions/%1").arg(route.getTag())));
        waitTimeRequest.setHeader(QNetworkRequest::UserAgentHeader, header);
        QNetworkReply* waitTimeReply = manager->get(waitTimeRequest);
        connect(waitTimeReply, SIGNAL(finished()), this, SLOT(readWaitTimes()));

        QNetworkRequest busPositionRequest(QUrl(QStringLiteral("https://gtbuses.herokuapp.com/locations/%1").arg(route.getTag())));
        busPositionRequest.setHeader(QNetworkRequest::UserAgentHeader, header);
        QNetworkReply* busPositionReply = manager->get(busPositionRequest);
        connect(busPositionReply, SIGNAL(finished()), this, SLOT(readBusPositions()));
    }

}

void GTWikiBusFetcher::readWaitTimes() {
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

    disconnect(reply, SIGNAL(finished()), this, SLOT(readWaitTimes()));

    if (reply->error() != QNetworkReply::NoError) {
        qCritical() << "Error occurred: " + reply->errorString();
        reply->deleteLater();
        return;
    }

    QXmlStreamReader reader(reply->readAll());
    if (reader.hasError()) {
        qCritical() << "Error parsing stop prediction XML: " + reader.errorString();
        reply->deleteLater();
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

                    const QList<Direction> directions = route.getDirections().values();
                    QList<Stop> stops;
                    for (int j = 0; j < directions.size(); j++) {
                        stops.append(directions.at(j).getStops());
                    }

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
                StopWait stopWait;
                stopWait.setTime(reader.attributes().value("seconds").toInt());
                stopWait.setBusId(reader.attributes().value("vehicle").toInt());
                stop.getStopTimes().append(stopWait);
            }
            break;
        default:
            break;
        }
    }

    reply->deleteLater();

    emit waitTimesUpdated(routeTag);
}

void GTWikiBusFetcher::readBusPositions() {
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

    disconnect(reply, SIGNAL(finished()), this, SLOT(readBusPositions()));

    if (reply->error() != QNetworkReply::NoError) {
        qCritical() << "Error occurred: " + reply->errorString();
        reply->deleteLater();
        return;
    }

    QXmlStreamReader reader(reply->readAll());
    if (Q_UNLIKELY(reader.hasError())) {
        qCritical() << "Error parsing stop prediction XML: " + reader.errorString();
        reply->deleteLater();
        return;
    }

    QString routeTag;

    while (!reader.atEnd()) {
        switch (reader.readNext()) {
        case QXmlStreamReader::StartElement:
            if (reader.name() == QStringLiteral("vehicle")) {
                routeTag = reader.attributes().value("routeTag").toString();
                QString dirTag = reader.attributes().value("dirTag").toString();
                int busId = reader.attributes().value("id").toInt();
                double lat = reader.attributes().value("lat").toDouble();
                double lon = reader.attributes().value("lon").toDouble();

                Route route;
                Direction direction;

                for (int i = 0; i < routes.size(); i++) {
                    Route possibleRoute = routes.at(i);
                    if (possibleRoute.getTag() == routeTag) {
                        route = possibleRoute;
                        direction = route.getDirections().value(dirTag);
                        continue;
                    }
                }

                Bus bus = route.getBuses().value(busId);
                bus.setId(busId);
                bus.setRoute(route);
                bus.setDirection(direction);

                geos::geom::Coordinate coordinate;
                coordinate.x = lon;
                coordinate.y = lat;

                QSharedPointer<geos::geom::Point> point(factory->createPoint(coordinate));
                bus.setLocation(point);

                route.getBuses().insert(busId, bus);
            }
            break;
        default:
            break;
        }
    }

    reply->deleteLater();

    emit waitTimesUpdated(routeTag);
}

QList<Route> GTWikiBusFetcher::getRoutes() const {
    return routes;
}

GTWikiBusFetcher::~GTWikiBusFetcher() {
    delete timer;
    delete manager;
    delete factory;
}
