#ifndef ROUTEMODEL_H
#define ROUTEMODEL_H

#include <QAbstractListModel>
#include "route.h"

class RouteModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit RouteModel(QObject *parent = 0);

    enum RouteRoles {
        Name = Qt::UserRole + 1,
        Tag
    };

    void setRoutes(QList<Route> routes);
    Q_INVOKABLE int rowCount(const QModelIndex &parent) const;
    Q_INVOKABLE QHash<int, QByteArray> roleNames() const;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role) const;

private:
    QList<Route> routes;

};

Q_DECLARE_METATYPE(RouteModel*)

#endif // ROUTEMODEL_H
