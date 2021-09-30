#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "controller.h"
#include <QMainWindow>

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

    void on_userSelectCities_comboBox_activated(const QString &arg1);

    void on_returnToUserPage_pushButton_clicked();

    void on_userLogout_pushButton_clicked();

    void on_adminEdit_pushButton_clicked();

    void on_adminChooseCities_comboBox_activated(const QString &arg1);

    void on_adminViewFoods_tableView_activated(const QModelIndex &index);

    void on_userLogout_Pushbutton_clicked();

    void on_adminLogout_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    Controller *m_controller;
};
#endif // MAINWINDOW_H
