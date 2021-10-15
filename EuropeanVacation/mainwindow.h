#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "controller.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(Controller *controller, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_clear_pushButton_clicked();

    void on_login_pushButton_clicked();

    void on_viewCitiesAndFoods_pushButton_clicked();

    void fillCitiesComboBoxes();

    void on_returnToUserPage_pushButton_clicked();

    void on_userLogout_pushButton_clicked();

    void on_adminEdit_pushButton_clicked();

    void on_adminViewFoods_tableView_activated(const QModelIndex &index);

    void on_contactUs_pushButton_clicked();

    void on_submit_pushButton_clicked();

    void on_return_pushButton_clicked();

    void on_userLogout_Pushbutton_clicked();

    void on_adminLogout_pushButton_clicked();

    void on_userSelectCities_comboBox_currentTextChanged(const QString &arg1);

    void on_adminChooseCities_comboBox_currentTextChanged(const QString &arg1);

    void on_editPrice_pushButton_clicked();

    void resetAdminEditPage();

    void on_returnToAdminPage_pushButton_clicked();

    void on_deleteFood_pushButton_clicked();

    void on_addNewFood_pushButton_clicked();

    void on_resetEditPage_pushButton_clicked();

    void on_adminUpload_pushButton_clicked();

    void on_returnToAdminPage_pushButton2_clicked();

    void on_adminUploadChooseCities_comboBox_currentTextChanged(const QString &arg1);

    void on_adminUploadCities_pushButton_clicked();

    void on_adminUploadFoods_pushButton_clicked();

    void on_planTrip_pushButton_clicked();

    void on_parisTrip_pushButton_clicked();

    void on_planTripPageBack_pushButton_clicked();

    void on_pickTripBack_pushButton_clicked();

    void on_autoPlanner_pushButton_clicked();

    void on_autoTripReset_pushButton_clicked();

    void on_purchaseFoods_pushButton_clicked();

    void on_customPlanner_pushButton_clicked();

    void on_customTripBack_pushButton_clicked();

    void on_customTripSelect_tableView_doubleClicked(const QModelIndex &index);

    void on_customTripReset_pushButton_clicked();

    void on_createCustomTrip_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    Controller *m_controller;
};

#endif // MAINWINDOW_H
