#ifndef FOOD_H
#define FOOD_H

#include <QObject>
#include <QString>

class food : public QObject
{
    Q_OBJECT
private:
    QString city;
    QString name;
    double cost;
public:
    explicit food(QObject *parent = nullptr);
    QString getCity() const;
    QString getName() const;
    double getCost() const;
    void setCity(const QString &item);
    void setName(const QString &item);
    void setCost(double &item);
};

#endif // FOOD_H
