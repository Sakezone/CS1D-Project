#include "trip.h"

QString Trip::getStartCity()
{
    return startCity;
}
QString Trip::getEndCity()
{
    return endCity;
}

int Trip::getDistance()
{
    return distance;
}

void Trip::setStartCity(QString temp)
{
    startCity = temp;
}

void Trip::setEndCity(QString temp)
{
    endCity = temp;
}

void Trip::setDistance(int temp)
{
    distance = temp;
}
