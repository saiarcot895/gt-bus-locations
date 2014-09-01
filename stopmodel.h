#ifndef STOPMODEL_H
#define STOPMODEL_H

#include <QAbstractListModel>
#include "stop.h"

class StopModel : public QAbstractListModel
{
    Q_OBJECT
public:
    explicit StopModel(QObject *parent = 0);

    enum StopRoles {
        Name = Qt::UserRole + 1,
        Tag
    };

    void setStops(QList<Stop> directions);
    Q_INVOKABLE int rowCount(const QModelIndex &parent) const;
    Q_INVOKABLE QHash<int, QByteArray> roleNames() const;
    Q_INVOKABLE QVariant data(const QModelIndex &index, int role) const;

private:
    QList<Stop> stops;

};

#endif // STOPMODEL_H
