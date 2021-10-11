#ifndef TRIP_H
#define TRIP_H

#include <QString>
#include <QObject>

class Trip : public QObject
{
    Q_OBJECT
private:
    QString startCity;
    QString endCity;
    int distance;
public:
    explicit Trip(QObject *parent = nullptr);
//    Trip();
    QString getStartCity();
    QString getEndCity();
    int getDistance();
    void setStartCity(QString);
    void setEndCity(QString);
    void setDistance(int);
};

#endif // TRIP_H
