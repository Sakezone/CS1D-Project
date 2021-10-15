#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QPalette>

MainWindow::MainWindow(Controller *controller, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      m_controller(controller)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->login_page);
    fillCitiesComboBoxes();

    /*QPixMap and QPalette used to set the background.*/
    QPixmap background(":/images/backgroundwhite.png");
    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, background);
    this->setPalette(palette);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::fillCitiesComboBoxes()
{
    ui->userSelectCities_comboBox->setModel(m_controller->getDistancesQueryModel("select DISTINCT StartCity from Distances ORDER BY StartCity ASC;"));
    ui->adminChooseCities_comboBox->setModel(m_controller->getDistancesQueryModel("select DISTINCT StartCity from Distances ORDER BY StartCity ASC;"));
    ui->adminUploadChooseCities_comboBox->setModel(m_controller->getDistancesQueryModel("select DISTINCT StartCity from Distances ORDER BY StartCity ASC;"));
    ui->autoTripCity_comboBox->setModel(m_controller->getDistancesQueryModel("select DISTINCT StartCity from Distances ORDER BY StartCity ASC;"));
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

        QMessageBox::information(this, "Success", "Username and Password are correct\nLogging into Admin");
        on_clear_pushButton_clicked();
        ui->stackedWidget->setCurrentWidget(ui->admin_page);
    }
    else if (usernameInput == USER_USERNAME && usernameInput == USER_PASSWORD) {

        QMessageBox::information(this, "Success", "Username and Password are correct\nLogging into User");
        on_clear_pushButton_clicked();
        ui->stackedWidget->setCurrentWidget(ui->user_page);
    }
    else {

        QMessageBox::information(this, "Invalid", "Username and Password are incorrect");
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

void MainWindow::on_contactUs_pushButton_clicked()
{
    QPixmap icon (":images/runtimeerror.png");
    ui->iconLabel->setPixmap(icon);
    ui->stackedWidget->setCurrentWidget(ui->contactUs_Page);
}

void MainWindow::on_submit_pushButton_clicked()
{
    QMessageBox::information(this, "Submitted", "Thank you for contacting Runtime Terror. Your information will be forwarded to the proper team.");
    ui->userInputBox->clear();
    ui->stackedWidget->setCurrentWidget(ui->user_page);
}

void MainWindow::on_return_pushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->user_page);
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

void MainWindow::resetAdminEditPage()
{
    ui->editFoodCity_label->setText(ui->adminChooseCities_comboBox->currentText());
    ui->editFoodFood_label->setText("No Food Selected!");
    ui->editPrice_doubleSpinBox->clear();
    ui->newFood_lineEdit->clear();
    ui->newFoodPrice_doubleSpinBox->clear();

}
void MainWindow::on_editPrice_pushButton_clicked()
{
    if (ui->editFoodFood_label->text() == "No Food Selected!")
        QMessageBox::warning(this, "Invalid", "No food selected!");
    else if (ui->editPrice_doubleSpinBox->value() < 0.01)
        QMessageBox::warning(this, "Invalid", "Invalid price!");
    else {

        QString food = ui->editFoodFood_label->text();
        QString city = ui->editFoodCity_label->text();
        double cost = ui->editPrice_doubleSpinBox->value();

        QMessageBox::StandardButton reply =
                QMessageBox::question(this, "Edit", "Are you sure you want to edit " + food + "?",
                                      QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {

            m_controller->editFoodCostQuery(city, food, cost);
            resetAdminEditPage();
            on_adminChooseCities_comboBox_currentTextChanged(city);
        }
    }
}


void MainWindow::on_returnToAdminPage_pushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->admin_page);
}


void MainWindow::on_deleteFood_pushButton_clicked()
{
    if (ui->editFoodFood_label->text() == "No Food Selected!")
        QMessageBox::warning(this, "Invalid", "No food selected!");
    else {

        QString food = ui->editFoodFood_label->text();
        QString city = ui->editFoodCity_label->text();
        double cost = ui->editPrice_doubleSpinBox->value();

        QMessageBox::StandardButton reply =
                QMessageBox::question(this, "Delete", "Are you sure you want to delete " + food + "?",
                                      QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {

            m_controller->deleteFoodQuery(city, food, cost);
            resetAdminEditPage();
            on_adminChooseCities_comboBox_currentTextChanged(city);
        }
    }
}


void MainWindow::on_addNewFood_pushButton_clicked()
{
    if (ui->newFood_lineEdit->text() == "" && ui->newFoodPrice_doubleSpinBox->value() <= 0.00)
        QMessageBox::warning(this, "Invalid", "New food has no name and price!");
    else if (ui->newFoodPrice_doubleSpinBox->value() <= 0.00)
        QMessageBox::warning(this, "Invalid", "New food has no price!");
    else if (ui->newFood_lineEdit->text() == "")
        QMessageBox::warning(this, "Invalid", "New food has no name!");
    else if (ui->editFoodCity_label->text() == "No City Selected!")
        QMessageBox::warning(this, "Invalid", "No city selected for new food!");
    else {

        QString city = ui->editFoodCity_label->text();
        QString food = ui->newFood_lineEdit->text();
        double cost  = ui->newFoodPrice_doubleSpinBox->value();

        QMessageBox::StandardButton reply =
                QMessageBox::question(this, "Add", "Are you sure you want to add " + food + " to " + city + "?",
                                      QMessageBox::Yes | QMessageBox::No);

        if (reply == QMessageBox::Yes) {

            m_controller->addFoodQuery(city, food, cost);

            resetAdminEditPage();
            on_adminChooseCities_comboBox_currentTextChanged(city);
        }
    }
}


void MainWindow::on_resetEditPage_pushButton_clicked()
{
    QString defaultCity = "Amsterdam";
    resetAdminEditPage();
    on_adminChooseCities_comboBox_currentTextChanged(defaultCity);
    ui->adminChooseCities_comboBox->setCurrentIndex(0);
}


void MainWindow::on_adminUpload_pushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->adminUpload_page);
}


void MainWindow::on_returnToAdminPage_pushButton2_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->admin_page);
}


void MainWindow::on_adminUploadChooseCities_comboBox_currentTextChanged(const QString &arg1)
{
    ui->adminUploadViewCities_tableView->setModel(m_controller->getDistancesQueryModel("select EndCity, Distance from Distances where StartCity = '"+arg1+"';"));
    ui->adminUploadViewFoods_tableView->setModel(m_controller->getFoodsQueryModel("select Food, Cost from Foods where City = '"+arg1+"';"));
}


void MainWindow::on_adminUploadCities_pushButton_clicked()
{
    m_controller->uploadCitiesFile();
    fillCitiesComboBoxes();
    ui->selectNumberOfCities_spinBox->setMaximum(12);
}


void MainWindow::on_adminUploadFoods_pushButton_clicked()
{
    m_controller->uploadFoodsFile();
    fillCitiesComboBoxes();
    ui->selectNumberOfCities_spinBox->setMaximum(12);
}

void MainWindow::on_planTrip_pushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pickTrip_Page);
}

void MainWindow::on_parisTrip_pushButton_clicked()
{
    int totalDistance = 0;
    m_controller->createTripList();
    m_controller->displayTripList();
    m_controller->createTrip(ui->autoTripCity_comboBox->currentText(), ui->selectNumberOfCities_spinBox->value());
    m_controller->displayTrip();

    ui->autoTrip_tableWidget->setRowCount(m_controller->completedTripList.size());
    ui->autoTrip_tableWidget->setColumnCount(3);

    for (int i = 0; i < m_controller->completedTripList.size(); i++) {

        QTableWidgetItem *startCity = new QTableWidgetItem();
        QTableWidgetItem *endCity = new QTableWidgetItem();
        QTableWidgetItem *distance = new QTableWidgetItem();

        startCity->setText(m_controller->completedTripList[i]->getStartCity());
        endCity->setText(m_controller->completedTripList[i]->getEndCity());
        distance->setText(QString::number(m_controller->completedTripList[i]->getDistance()));

        ui->autoTrip_tableWidget->setItem(i, 0, startCity);
        ui->autoTrip_tableWidget->setItem(i, 1, endCity);
        ui->autoTrip_tableWidget->setItem(i, 2, distance);

        totalDistance = totalDistance + m_controller->completedTripList[i]->getDistance();
    }

    ui->autoTrip_tableWidget->resizeColumnsToContents();

    // -FOOD SECTION-

    m_controller->createFoodList();

    ui->purchaseFoods_tableWidget->setRowCount(m_controller->foodList.size());
    ui->purchaseFoods_tableWidget->setColumnCount(4);

    for (int i = 0; i < m_controller->foodList.size(); i++) {

        QTableWidgetItem *city = new QTableWidgetItem();
        QTableWidgetItem *food = new QTableWidgetItem();
        QTableWidgetItem *cost = new QTableWidgetItem();

        city->setText(m_controller->foodList[i]->getCity());
        food->setText(m_controller->foodList[i]->getName());
        cost->setText(QString::number(m_controller->foodList[i]->getCost()));

        ui->purchaseFoods_tableWidget->setItem(i, 0, city);
        ui->purchaseFoods_tableWidget->setItem(i, 1, food);
        ui->purchaseFoods_tableWidget->setItem(i, 2, cost);
        ui->purchaseFoods_tableWidget->setCellWidget(i, 3, new QSpinBox);
    }

    ui->purchaseFoods_tableWidget->resizeColumnsToContents();


}

void MainWindow::on_planTripPageBack_pushButton_clicked()
{
    on_autoTripReset_pushButton_clicked();
    ui->stackedWidget->setCurrentWidget(ui->user_page);
}


void MainWindow::on_pickTripBack_pushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->user_page);
}

void MainWindow::on_autoPlanner_pushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->planAutoTrip_Page);
}

void MainWindow::on_autoTripReset_pushButton_clicked()
{
    m_controller->resetTripList();
    m_controller->resetTrip();
    ui->autoTrip_tableWidget->clearContents();
    ui->autoTrip_tableWidget->clear();
    ui->autoTrip_tableWidget->setRowCount(0);
    ui->autoTrip_tableWidget->setColumnCount(0);

    ui->purchaseFoods_tableWidget->clearContents();
    ui->purchaseFoods_tableWidget->clear();
    ui->purchaseFoods_tableWidget->setRowCount(0);
    ui->purchaseFoods_tableWidget->setColumnCount(0);

    ui->foodReceipt_tableView->clear();
    ui->totalCost_label->clear();
}


void MainWindow::on_purchaseFoods_pushButton_clicked()
{
    ui->foodReceipt_tableView->clear();

    double totalCost = 0;

    for (int i = 0; i < ui->purchaseFoods_tableWidget->rowCount(); i++) {

        int val = static_cast<QSpinBox*>(ui->purchaseFoods_tableWidget->cellWidget(i, 3))->value();
        QTableWidgetItem *cost = ui->purchaseFoods_tableWidget->item(i,2);
        totalCost = totalCost + (cost->text().toDouble() * val);

        int quantity = static_cast<QSpinBox*>(ui->purchaseFoods_tableWidget->cellWidget(i, 3))->value();

        if (quantity > 0) {

            QString name = ui->purchaseFoods_tableWidget->item(i,1)->text();
            double costs = cost->text().toDouble() * quantity;

            ui->foodReceipt_tableView->append(name);
            ui->foodReceipt_tableView->append(cost->text() + " x" + QString::number(quantity));
            ui->foodReceipt_tableView->append(QString::number(costs));
            ui->foodReceipt_tableView->append("----------------");
        }
    }

    ui->totalCost_label->setText("$" + QString::number(totalCost));
}


void MainWindow::on_customPlanner_pushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->customTrip_page);
    ui->customTripSelect_tableView->setModel(m_controller->getDistancesQueryModel("select DISTINCT StartCity from Distances ORDER BY StartCity ASC;"));
}


void MainWindow::on_customTripBack_pushButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->user_page);
}


void MainWindow::on_customTripSelect_tableView_doubleClicked(const QModelIndex &index)
{
    m_controller->customTripListCities.append(index.data().toString());
    ui->customTrip_textBrowser->append(index.data().toString());
    ui->customTripSelect_tableView->hideRow(index.row());
}

void MainWindow::on_customTripReset_pushButton_clicked()
{
    m_controller->resetTripList();
    m_controller->resetTrip();

    ui->customTripSelect_tableView->reset();

//    ui->customTripSelect_tableView->resizeRowsToContents();
    ui->customTripSelect_tableView->setModel(m_controller->getDistancesQueryModel("select DISTINCT StartCity from Distances ORDER BY StartCity ASC;"));
    ui->customTrip_textBrowser->clear();
}

void MainWindow::on_createCustomTrip_pushButton_clicked()
{
//    qDebug() << m_controller->customTripListCities.size();
//    for (int i = 0; i < m_controller->customTripListCities.size(); i++) {

//        qDebug() << m_controller->customTripListCities[i];
//    }

    QString startCity = m_controller->customTripListCities[0];
    int numberOfCities = m_controller->customTripListCities.size() - 1;

//    m_controller->createAutomaticTrip(firstCity, numberOfCities);
//    m_controller->displayAutomaticTrip();

    m_controller->createCustomTripList();
    m_controller->displayTripList();
    m_controller->createTrip(startCity, numberOfCities);
    m_controller->displayTrip();
}

