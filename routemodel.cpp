#include "routemodel.h"

RouteModel::RouteModel(QObject *parent) :
    QAbstractListModel(parent)
{
}

void RouteModel::setRoutes(QList<Route> routes) {
    this->routes = routes;
}

int RouteModel::rowCount(const QModelIndex &parent) const {
    return routes.size();
}

QHash<int, QByteArray> RouteModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles.insert(RouteModel::Name, "name");
    roles.insert(RouteModel::Tag, "tag");
    return roles;
}

QVariant RouteModel::data(const QModelIndex &index, int role) const {
    if (role == RouteModel::Name) {
        return routes.at(index.row()).getRouteName();
    } else if (role == RouteModel::Tag) {
        return routes.at(index.row()).getTag();
    }
}
