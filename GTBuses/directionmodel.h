#ifndef DIRECTIONMODEL_H
#define DIRECTIONMODEL_H

#include <QAbstractListModel>
#include "direction.h"

class DirectionModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit DirectionModel(QObject *parent = 0);

    enum DirectionRoles {
        Name = Qt::UserRole + 1,
        Tag
    };

    void setDirections(QList<Direction> directions);
    Q_INVOKABLE int rowCount(const QModelIndex &parent) const;
    Q_INVOKABLE QHash<int, QByteArray> roleNames() const;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role) const;

private:
    QList<Direction> directions;

};

Q_DECLARE_METATYPE(DirectionModel*)

#endif // DIRECTIONMODEL_H
