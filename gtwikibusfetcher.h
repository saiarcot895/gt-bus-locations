#ifndef GTWIKIBUSFETCHER_H
#define GTWIKIBUSFETCHER_H

#include "route.h";

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class GTWikiBusFetcher : public QObject
{
    Q_OBJECT
public:
    explicit GTWikiBusFetcher(QObject *parent = 0);

    QList<Route> getRoutes() const;

signals:
    void loadingDone();

public slots:
    void readRouteConfig();

private:
    QNetworkAccessManager* manager;
    QNetworkReply* routeConfigReply;
    QList<Route> routes;

};

#endif // GTWIKIBUSFETCHER_H
