#include "food.h"

food::food(QObject * parent) : QObject(parent) {}

QString food::getCity() const
{
    return city;
}

QString food::getName() const
{
    return name;
}

double food::getCost() const
{
    return cost;
}

void food::setCity(const QString &item)
{
    city = item;
}

void food::setName(const QString &item)
{
    name = item;
}

void food::setCost(double &item)
{
    cost = item;
}

