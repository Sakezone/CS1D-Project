#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QPalette>

MainWindow::MainWindow(Controller *controller, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->login_page);
    fillCitiesComboBoxes();

//    /*QPixMap and QPalette used to set the background.*/
//    QPixmap background(":/images/background.jpg");
//    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);
//    QPalette palette;
//    palette.setBrush(QPalette::Window, background);
//    this->setPalette(palette);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fillCitiesComboBoxes()
{
    ui->userSelectCities_comboBox->setModel(m_controller->getDistancesQueryModel("select DISTINCT StartCity from Distances ORDER BY StartCity ASC;"));
    ui->adminChooseCities_comboBox->setModel(m_controller->getDistancesQueryModel("select DISTINCT StartCity from Distances ORDER BY StartCity ASC;"));
}

void MainWindow::on_clear_pushButton_clicked()
{
    this->ui->inputUsername_lineEdit->setText("");
    this->ui->inputPassword_lineEdit->setText("");
}

void MainWindow::on_login_pushButton_clicked()
{
    const QString ADMIN_USERNAME = "admin";
    const QString ADMIN_PASSWORD = "admin";
    const QString USER_USERNAME = "user";
    const QString USER_PASSWORD = "user";

    QString usernameInput = ui->inputUsername_lineEdit->text();
    QString passwordInput = ui->inputPassword_lineEdit->text();

    if (usernameInput == ADMIN_USERNAME && passwordInput == ADMIN_PASSWORD) {

        QMessageBox::information(this, "Login", "Username and Password are correct");
        on_clear_pushButton_clicked();
        ui->stackedWidget->setCurrentWidget(ui->admin_page);
    }
    else if (usernameInput == USER_USERNAME && usernameInput == USER_PASSWORD) {

        QMessageBox::information(this, "Login", "Username and Password are correct");
        on_clear_pushButton_clicked();
        ui->stackedWidget->setCurrentWidget(ui->user_page);
    }
    else {

        QMessageBox::information(this, "Login", "Username and Password are incorrect");
        on_clear_pushButton_clicked();
    }
}

void MainWindow::on_viewCitiesAndFoods_pushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->viewCitiesAndFoods_page);
}

void MainWindow::on_userSelectCities_comboBox_currentTextChanged(const QString &arg1)
{
    ui->userViewCities_tableView->setModel(m_controller->getDistancesQueryModel("select EndCity, Distance from Distances where StartCity = '"+arg1+"';"));
    ui->userViewFoods_tableView->setModel(m_controller->getFoodsQueryModel("select Food, Cost from Foods where City = '"+arg1+"';"));
}

void MainWindow::on_returnToUserPage_pushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->user_page);
    qDebug() << "BACK BUTTON PRESSED";
}

void MainWindow::on_userLogout_pushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->login_page);
}

void MainWindow::on_adminEdit_pushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->adminEdit_page);
}

void MainWindow::on_adminViewFoods_tableView_activated(const QModelIndex &index)
{
    QString currentFood;
    QString currentCity;

    if (index.column() == 1) {

        //resetSouvenirScreenLabels();
    }
    else if (index.isValid()) {

        QSqlQuery qry;
        double price;
        currentFood = index.data().toString();
        ui->editFoodFood_label->setText(currentFood);
        currentCity = ui->adminChooseCities_comboBox->currentText();
        qry.prepare("select Cost from Foods where City = '"+currentCity+"' and Food = '"+currentFood+"';");

        if (!qry.exec()) {

            qDebug() << "ERROR: on_adminViewFoods_tableView_activated(const QModelIndex &index))";
        }
        else {

            if (qry.first()) {

                qDebug() << qry.value(0);
                QString test = qry.value(0).toString();
                test.remove(0,1);
                price = test.toDouble();
                ui->editPrice_doubleSpinBox->setValue(price);
            }
        }
    }
}

void MainWindow::on_userLogout_Pushbutton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->login_page);
}

void MainWindow::on_adminLogout_pushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->login_page);
}

void MainWindow::on_adminChooseCities_comboBox_currentTextChanged(const QString &arg1)
{
    ui->adminViewFoods_tableView->setModel(m_controller->getFoodsQueryModel("select Food, Cost from Foods where City = '"+arg1+"';"));
    ui->editFoodCity_label->setText(arg1);
}

