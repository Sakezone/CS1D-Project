#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QMessageBox alert;
    ui->setupUi(this);
    alert.setText("Welcome to the European Trip Planner.");
    alert.exec();
}

MainWindow::~MainWindow()
{
    delete ui;
}

