#ifndef GTWIKIBUSFETCHER_H
#define GTWIKIBUSFETCHER_H

#include "route.h"

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTimer>
#include <geos/geom/GeometryFactory.h>

class GTWikiBusFetcher : public QObject
{
    Q_OBJECT
public:
    explicit GTWikiBusFetcher(QObject *parent = 0);

    QList<Route> getRoutes() const;

signals:
    void loadingDone();
    void waitTimesUpdated(QString routeTag);

public slots:
    void readRouteConfig();
    void refreshWaitTimes();
    void readWaitTimes(QNetworkReply* reply);

private:
    QNetworkAccessManager* manager;
    QNetworkReply* routeConfigReply;
    QTimer* timer;
    geos::geom::GeometryFactory* factory;

    QList<Route> routes;

};

#endif // GTWIKIBUSFETCHER_H
