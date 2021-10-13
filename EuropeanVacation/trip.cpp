#include "trip.h"

Trip::Trip(QObject *parent) : QObject(parent)
{

}

//Trip::Trip()
//{
//    this->startCity = "";
//    this->endCity = "";
//    this->distance = 0;
//}

QString Trip::getStartCity() const
{
    return startCity;
}

QString Trip::getEndCity() const
{
    return endCity;
}

int Trip::getDistance() const
{
    return distance;
}

void Trip::setStartCity(const QString &temp)
{
    startCity = temp;
}

void Trip::setEndCity(const QString &temp)
{
    endCity = temp;
}

void Trip::setDistance(int temp)
{
    distance = temp;
}
