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

private:
    QSqlDatabase m_database;

};

#endif // CONTROLLER_H
