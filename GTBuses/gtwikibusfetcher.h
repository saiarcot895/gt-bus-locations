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

    ~GTWikiBusFetcher();
signals:
    void loadingDone();
    void waitTimesUpdated(QString routeTag);

public slots:
    void readRouteConfig();
    void updateInfo();
    void distributeInfo(QNetworkReply* reply);
    void getRouteConfig();

private:
    void readWaitTimes(QNetworkReply* reply);
    void readBusPositions(QNetworkReply* reply);

    QNetworkAccessManager* manager;
    QNetworkReply* routeConfigReply;
    QTimer* timer;
    geos::geom::GeometryFactory* factory;

    QList<Route> routes;
    QList<QNetworkReply*> waitTimesReplies;
    QList<QNetworkReply*> busPositionReplies;

};

#endif // GTWIKIBUSFETCHER_H
