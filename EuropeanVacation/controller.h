#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlError>
#include <QtDebug>
#include <QMessageBox>
#include <QKeyEvent>
#include <QFileDialog>
#include<QItemDelegate>
#include<QSpinBox>
#include<QSize>
#include<QTableWidgetItem>
#include <QSpinBox>
#include "trip.h"
using namespace std;

class Controller : public QObject {

    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);
    ~Controller();

    QSqlQueryModel *getDistancesQueryModel(QString query);
    QSqlQueryModel *getFoodsQueryModel(QString query);
    void editFoodCostQuery(QString city, QString food, double cost);
    void deleteFoodQuery(QString city, QString food, double cost);
    void addFoodQuery(QString city, QString food, double cost);
    void uploadCitiesFile();
    void uploadFoodsFile();

    // For planning trips
    void createTripList();
    void createCustomTripList();
    void resetTripList();
    void displayTripList();
    void createTrip(QString startCity, int numberOfCities);
    void resetTrip();
    void displayTrip();
    void createFoodList();

    QVector<Trip*> tripList;
    QVector<Trip*> completedTripList;
    QVector<food*> foodList;
    QVector<QString> customTripListCities;

private:
    QSqlDatabase m_database;

};

#endif // CONTROLLER_H
