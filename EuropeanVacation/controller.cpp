#include "controller.h"

Controller::Controller(QObject *parent) : QObject(parent) {

    m_database = QSqlDatabase::addDatabase("QSQLITE");
    QString path = "..//CS1D-European-Vacation-Project.db";
    m_database.setDatabaseName(path);
    if (!m_database.open()) {

        qDebug() << "PROBLEM OPENING DATABASE.";
    }
    else {

        qDebug() << "DATABASE OPENED.";
    }

//    createTripList();
//    displayTripList();
//    displayTripList();
//    displayTripList();
}

Controller::~Controller() {

    m_database.close();
}

QSqlQueryModel *Controller::getDistancesQueryModel(QString query) {

    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery(query);

    if (model->lastError().isValid())
        qDebug() << model->lastError();
    else
        qDebug() << model;

    return model;
}

QSqlQueryModel *Controller::getFoodsQueryModel(QString query) {

    QSqlQueryModel* model = new QSqlQueryModel();


    model->setQuery(query);

    if (model->lastError().isValid())
        qDebug() << model->lastError();
    else
        qDebug() << model;

    return model;
}

void *Controller::editFoodCostQuery(QString city, QString food, double cost) {

    QString costAsString = "$" + QString::number(cost);
    QSqlQuery qry;

//    qry.prepare ("UPDATE [Foods] SET City = '"+city+"', Food = '"+food+"', Cost = '"+costAsString+"' where Food = '"+food+"' and City = '"+city+"';");

    qry.prepare("UPDATE [Foods] set   "
                "City       = ?,      "
                "Food       = ?,      "
                "Cost       = ?       "
                "where Food = ? and   "
                "City       = ?;      ");

    qry.addBindValue(city);
    qry.addBindValue(food);
    qry.addBindValue(costAsString);
    qry.addBindValue(food);
    qry.addBindValue(city);

    if (!qry.exec()) {

        qDebug() << "ERROR IN editFoodPriceQueryModel(QString city, QString food, double price)!!!!!!!!!!!";
        qDebug() << food << " from " << city << "not updated to " << costAsString << "!";

    }
    else {
        qDebug() << food << " from " << city << "updated to " << costAsString << "!";
    }

    qry.clear();

    return 0;
}

void *Controller::deleteFoodQuery(QString city, QString food, double cost)
{
    QString costAsString = "$" + QString::number(cost);
    QSqlQuery qry;

    qry.prepare("DELETE FROM Foods WHERE City = '"+city+"' AND Food = '"+food+"' AND Cost = '"+costAsString+"';");

    if (!qry.exec())
        qDebug() << "ERROR IN deleteFoodQuery(QString city, QString food, double cost)!!!!!!!!!!!";
    else
        qDebug() << food << " FROM " << city << " REMOVED!";

    qry.clear();

    return 0;
}

void *Controller::addFoodQuery(QString city, QString food, double cost) {

    QString costAsString = "$" + QString::number(cost);
    QSqlQuery qry;

    qry.prepare("INSERT INTO Foods (City, Food, Cost) "
                "VALUES (?, ?, ?);");
    qry.addBindValue(city);
    qry.addBindValue(food);
    qry.addBindValue(costAsString);

    if (!qry.exec())
        qDebug() << "ERROR IN addFoodQuery(QString city, QString food, double cost)!!!!!!!!!!!!!!";
    else
        qDebug() << "ADDED " << city << ", " << food << ", " << costAsString;

    qry.clear();

    return 0;
}

void *Controller::uploadCitiesFile() {

    QString fileName = QFileDialog::getOpenFileName(nullptr, tr("Open File"),
                                                    "/home/CS1D-Project", tr("Text Files (*.txt)"));
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        qDebug() << "Error reading file.";
    else {

        QTextStream in(&file);

        while (!in.atEnd()) {

            QSqlQuery qry;
            QString startCity = in.readLine();
            QString endCity = in.readLine();
            QString distance = in.readLine();

            qry.prepare("INSERT INTO Distances (StartCity, EndCity, Distance)"
                        "VALUES (?, ?, ?);");

            qry.addBindValue(startCity);
            qry.addBindValue(endCity);
            qry.addBindValue(distance);

            if (!qry.exec())
                qDebug() << "ERROR READING .TXT ON " << startCity << ", " << endCity << ", " << distance;
            else {

                qDebug() << "CITY DATA APPENDED TO .DB: " << startCity << ", " << endCity << ", " << distance;
                qry.clear();
            }
        }
    }

    return 0;
}

void *Controller::uploadFoodsFile() {

    QString fileName = QFileDialog::getOpenFileName(nullptr, tr("Open File"),
                                                    "/home/CS1D-Project", tr("Text Files (*.txt)"));
    QFile file(fileName);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        qDebug() << "Error reading file.";
    else {

        QTextStream in(&file);

        while (!in.atEnd()) {

            QSqlQuery qry;
            QString city = in.readLine();
            QString food = in.readLine();
            QString cost = in.readLine();

            qry.prepare("INSERT INTO Foods (City, Food, Cost)"
                        "VALUES (?, ?, ?);");

            qry.addBindValue(city);
            qry.addBindValue(food);
            qry.addBindValue(cost);

            if (!qry.exec())
                qDebug() << "ERROR READING .TXT ON " << city << ", " << food << ", " << cost;
            else {

                qDebug() << "FOOD DATA APPENDED TO .DB: " << city << ", " << food << ", " << cost;
                qry.clear();
            }
        }
    }

    return 0;
}

void *Controller::createTripList()
{
    QSqlTableModel model;
    model.setTable("Distances");
    model.select();

    for (int i = 0; i < model.rowCount(); i++) {

        Trip* entry = new Trip();
        entry->setStartCity(model.record(i).value("StartCity").toString());
        entry->setEndCity(model.record(i).value("EndCity").toString());
        entry->setDistance(model.record(i).value("Distance").toInt());

        this->tripList.append(entry);

//        qDebug() << "DATABASE ROW :" << i;
//        qDebug() << "    " << tripList[i]->getStartCity() << ", " << tripList[i]->getEndCity()
//                 << ", " << tripList[i]->getDistance();
    }

    displayTripList();
}

void *Controller::displayTripList()
{
    for (int i = 0; i < tripList.size(); i++) {

        qDebug() << "DATABASE ROW :" << i;
        qDebug() << tripList[i]->getStartCity();
        qDebug() << tripList[i]->getEndCity();
        qDebug() << tripList[i]->getDistance();

    }
}

void Controller::parisTrip()
{
    return;
}






