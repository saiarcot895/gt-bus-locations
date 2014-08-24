#include "directionmodel.h"

DirectionModel::DirectionModel(QObject *parent) :
    QAbstractListModel(parent)
{
}

void DirectionModel::setDirections(QList<Direction> directions) {
    this->directions = directions;
}

int DirectionModel::rowCount(const QModelIndex &parent) const {
    return directions.size();
}

QHash<int, QByteArray> DirectionModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles.insert(DirectionModel::Name, "name");
    roles.insert(DirectionModel::Tag, "tag");
    return roles;
}

QVariant DirectionModel::data(const QModelIndex &index, int role) const {
    if (role == DirectionModel::Name) {
        return directions.at(index.row()).getDirectionName();
    } else if (role == DirectionModel::Tag) {
        return directions.at(index.row()).getTag();
    }
}
