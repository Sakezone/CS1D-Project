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

    createTripList();
    displayTripList();
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

void Controller::editFoodCostQuery(QString city, QString food, double cost) {

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


}

void Controller::deleteFoodQuery(QString city, QString food, double cost)
{
    QString costAsString = "$" + QString::number(cost);
    QSqlQuery qry;

    qry.prepare("DELETE FROM Foods WHERE City = '"+city+"' AND Food = '"+food+"' AND Cost = '"+costAsString+"';");

    if (!qry.exec())
        qDebug() << "ERROR IN deleteFoodQuery(QString city, QString food, double cost)!!!!!!!!!!!";
    else
        qDebug() << food << " FROM " << city << " REMOVED!";

    qry.clear();


}

void Controller::addFoodQuery(QString city, QString food, double cost) {

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
}

void Controller::uploadCitiesFile() {

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

                Trip* entry = new Trip();
                entry->setStartCity(startCity);
                entry->setEndCity(endCity);
                entry->setDistance(distance.toInt());
                this->tripList.append(entry);
            }
        }
    }
}

void Controller::uploadFoodsFile() {

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
}

void Controller::createTripList()
{
    for(int i = 0; i < tripList.size(); i++) {

        delete tripList[i];
    }

    tripList.clear();

    QSqlTableModel model;
    model.setTable("Distances");
    model.select();

    for (int i = 0; i < model.rowCount(); i++) {

        Trip* entry = new Trip();
        entry->setStartCity(model.record(i).value("StartCity").toString());
        entry->setEndCity(model.record(i).value("EndCity").toString());
        entry->setDistance(model.record(i).value("Distance").toInt());

        this->tripList.append(entry);
    }  
}

void Controller::resetTripList()
{
    createTripList();
}

void Controller::displayTripList()
{
    for (int i = 0; i < tripList.size(); i++) {

//        qDebug() << "----------";
//        qDebug() << tripList[i]->getStartCity();
//        qDebug() << tripList[i]->getEndCity();
//        qDebug() << tripList[i]->getDistance();
        qDebug() << tripList[i]->getStartCity() << ", " << tripList[i]->getEndCity() << ", " << tripList[i]->getDistance();
    }
}

QVector<Trip*> Controller::planTrip(QVector<Trip*> tripVector, QVector<Trip*> plannedTrip, QString search, int distance, int amountOfCities)
{
    if(plannedTrip.size() == amountOfCities)
        return plannedTrip;

    for(int i = 0; i < tripVector.size(); i++)
    {
        if(tripVector[i]->getStartCity() == search)
            if(distance > tripVector[i]->getDistance())
                distance = tripVector[i]->getDistance();
    }

    for(int i = 0; i < tripVector.size(); i++)
    {
        if(tripVector[i]->getStartCity() == search)
            if(tripVector[i]->getDistance() == distance)
            {
                // THIS PART IS BROKEN

                Trip* trip = new Trip();
                trip->setStartCity(tripVector[i]->getStartCity());
                trip->setEndCity(tripVector[i]->getEndCity());
                trip->setDistance(tripVector[i]->getDistance());
                plannedTrip.append(trip);

                search = tripVector[i]->getEndCity();
                distance = 999999;

                planTrip(tripVector, plannedTrip, search, distance, amountOfCities);
            }
    }
}

void Controller::parisTrip()
{
//    QVector<Trip*> tripVector;
//    QVector<Trip*> plannedTrip;
//    QString search = "Paris";
//    int distance = 999999;
//    int amountOfCities = 11;
//    tripVector = createTripList();
//    plannedTrip = planTrip(tripVector, plannedTrip, search, distance, amountOfCities);

//    for(int i = 0; i < plannedTrip.size(); i++)
//        qDebug() << plannedTrip[i]->getStartCity();
}

void Controller::createAutomaticTrip(QString startCity, int numberOfCities)
{
    QString tempEndCity = "DEFAULT";
    int tempDistance = 99999;
    int distance = 99999;   // RE-INITIALIZES DISTANCE FOR DISTANCE SEARCH

    if (completedTripList.size() == numberOfCities)    // ENDS WHEN THE NUMBER OF CITIES IS REACHED.
        return;

    else {

        for (int i = 0; i < tripList.size(); i++) { // TRAVERSES tripList AND SEARCHES FOR THE CITY WITH THE LOWEST DISTANCE RELATIVE TO startCity

            if (tripList[i]->getStartCity() == startCity) { // FINDS THE CITY WITH THE LOWEST DISTANCE AND SAVES endCity AND distance

                if (tripList[i]->getDistance() < distance) {

                        tempEndCity = tripList[i]->getEndCity();
                        tempDistance = tripList[i]->getDistance();
                        distance = tripList[i]->getDistance();
                }

                qDebug() << "REMOVING: " << tripList[i]->getStartCity() << ", " << tripList[i]->getEndCity() << ", " << tripList[i]->getDistance();

                tripList[i]->setStartCity("NULL");
                tripList[i]->setEndCity("NULL");
                tripList[i]->setDistance(100000);
//                tripList.removeAt(i);
                continue;
            }
        }

        for (int i = 0; i < tripList.size(); i++) { // TRAVERSES tripList AND SEARCHES FOR THE CITY WITH THE LOWEST DISTANCE RELATIVE TO startCity

            if (tripList[i]->getEndCity() == startCity) {

                qDebug() << "REMOVING: " << tripList[i]->getStartCity() << ", " << tripList[i]->getEndCity() << ", " << tripList[i]->getDistance();

                tripList[i]->setStartCity("NULL");
                tripList[i]->setEndCity("NULL");
                tripList[i]->setDistance(100000);
//                tripList.removeAt(i);
                continue;
            }
        }

//        displayTripList();
        qDebug() << "***********FINISHED THE FOR LOOP THROUGH tripList*******************";
//        displayTripList();

        Trip *entry = new Trip();
        entry->setStartCity(startCity);
        entry->setEndCity(tempEndCity);
        entry->setDistance(tempDistance);

        this->completedTripList.append(entry);

//        qDebug() << startCity << "---->" << tempDistance << "---->" << tempEndCity;

        createAutomaticTrip(tempEndCity, numberOfCities);
    }
}

void Controller::resetAutomaticTrip()
{
    for(int i = 0; i < completedTripList.size(); i++) {

        delete completedTripList[i];
    }

    completedTripList.clear();
}

void Controller::displayAutomaticTrip()
{
    qDebug() << "++++++++++FINAL TRIP+++++++++++++++++";
    for (int i = 0; i < completedTripList.size(); i++) {

        qDebug() << completedTripList[i]->getStartCity() << "--->" << completedTripList[i]->getDistance() << "--->" << completedTripList[i]->getEndCity();
    }
}
