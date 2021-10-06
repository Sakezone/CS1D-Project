#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QMainWindow>
#include <QtSql>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
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
    void *editFoodCostQuery(QString city, QString food, double cost);
    void *deleteFoodQuery(QString city, QString food, double cost);
    void *addFoodQuery(QString city, QString food, double cost);
    void *uploadCitiesFile();
    void *uploadFoodsFile();
private:
    QSqlDatabase m_database;

};

#endif // CONTROLLER_H
