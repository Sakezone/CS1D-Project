#ifndef TRIP_H
#define TRIP_H

#include "controller.h"

class Trip
{
private:
    QString startCity;
    QString endCity;
    int distance;
public:
    QString getStartCity();
    QString getEndCity();
    int getDistance();
    void setStartCity(QString);
    void setEndCity(QString);
    void setDistance(int);
};

#endif // TRIP_H
