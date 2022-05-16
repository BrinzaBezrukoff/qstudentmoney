#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "dataloader.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_ch_AgeEffect_stateChanged(int arg1);

    void on_pb_ChooseFiles_clicked();

    void on_pb_Calculate_clicked();

    void on_cb_Month_currentIndexChanged(int index);

    void on_pb_editCosts_clicked();

    void on_pb_editTransport_clicked();

    void on_pb_editInstitute_clicked();

    void on_pb_editCaffeCinema_clicked();

private:
    Ui::MainWindow *ui;
    DataLoader _dataLoader;
    string _predictedDataPath;

};
#endif // MAINWINDOW_H
