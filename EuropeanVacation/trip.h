#ifndef TRIP_H
#define TRIP_H

#include <QObject>
#include <QString>

class Trip : public QObject
{
    Q_OBJECT
signals:
public slots:
private:
    QString startCity;
    QString endCity;
    int distance;
public:
    explicit Trip(QObject *parent = nullptr);
//    Trip();
    QString getStartCity() const;
    QString getEndCity() const;
    int getDistance() const;
    void setStartCity(const QString &item);
    void setEndCity(const QString &item);
    void setDistance(int);
};

#endif // TRIP_H
