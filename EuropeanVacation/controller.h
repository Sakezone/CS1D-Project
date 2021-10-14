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
#include "trip.h"
using namespace std;

class Controller : public QObject {

    Q_OBJECT
public:
    explicit Controller(QObject *parent = nullptr);

//    Controller(Controller& controller);
    ~Controller();
//    void createTable();
//    void loadCities();
    QSqlQueryModel *getDistancesQueryModel(QString query);
    QSqlQueryModel *getFoodsQueryModel(QString query);
    void editFoodCostQuery(QString city, QString food, double cost);
    void deleteFoodQuery(QString city, QString food, double cost);
    void addFoodQuery(QString city, QString food, double cost);
    void uploadCitiesFile();
    void uploadFoodsFile();

    // For planning trips
    void createTripList();
    void resetTripList();
    void displayTripList();
    QVector<Trip*> planTrip(QVector<Trip*> tripVector, QVector<Trip*> plannedTrip, QString search, int distance, int amountOfCities);
    void parisTrip();
    void createAutomaticTrip(QString startCity, int numberOfCities);
    void resetAutomaticTrip();
    void displayAutomaticTrip();

    QVector<Trip*> tripList;
    QVector<Trip*> completedTripList;

private:
    QSqlDatabase m_database;

};

#endif // CONTROLLER_H
