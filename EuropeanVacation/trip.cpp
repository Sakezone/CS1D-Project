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
