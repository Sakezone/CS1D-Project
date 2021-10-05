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
}

Controller::~Controller() {

    m_database.close();
}

QSqlQueryModel *Controller::getDistancesQueryModel(QString query) {

    QSqlQueryModel* model = new QSqlQueryModel();
//    QSqlQuery qry;
//    qry.prepare(query);

//    if (!qry.exec()) {

//        qDebug() << "ERROR IN getQueryModel(" << query << ")";
//    }

    model->setQuery(query);
    if (model->lastError().isValid())
        qDebug() << model->lastError();
    else
        qDebug() << model;
    return model;
}

QSqlQueryModel *Controller::getFoodsQueryModel(QString query) {

    QSqlQueryModel* model = new QSqlQueryModel();
//    QSqlQuery qry;
//    qry.prepare(query);

//    if (!qry.exec()) {

//        qDebug() << "ERROR IN getQueryModel(" << query << ")";
//    }

    model->setQuery(query);
    if (model->lastError().isValid())
        qDebug() << model->lastError();
    else
        qDebug() << model;
    return model;
}
