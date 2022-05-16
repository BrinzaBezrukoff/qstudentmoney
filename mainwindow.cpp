#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QFileDialog>
#include <QString>
#include <QMessageBox>
#include <stdexcept>
#include <cmath>

#include <iostream>

#include "student.h"
#include "editdialog.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Try to locate data directory automaticly
    _predictedDataPath = DataLoader::locateDirectory("/home", 30);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ch_AgeEffect_stateChanged(int arg1)
{
    if (arg1 == Qt::CheckState::Checked) {
        ui->sb_Age->setEnabled(true);
    }
    else if (arg1 == Qt::CheckState::Unchecked) {
        ui->sb_Age->setEnabled(false);
    }
}

void MainWindow::on_pb_ChooseFiles_clicked()
{
    QString dirPath = QFileDialog::getExistingDirectory(this, "Выбор директории с данными", QString::fromStdString(_predictedDataPath));
    if (dirPath.size() == 0) {
        return;
    }
    try {
        _dataLoader.openDirectory(dirPath.toStdString());
        ui->le_DataPath->setText(dirPath);
        ui->pb_Calculate->setEnabled(true);
        ui->pb_editCosts->setEnabled(true);
        ui->pb_editTransport->setEnabled(true);
        ui->pb_editInstitute->setEnabled(true);
        ui->pb_editCaffeCinema->setEnabled(true);
    }
    catch (std::runtime_error& ex) {
        ui->le_DataPath->setText("");
        ui->pb_Calculate->setEnabled(false);
        ui->pb_editCosts->setEnabled(false);
        ui->pb_editTransport->setEnabled(false);
        ui->pb_editInstitute->setEnabled(false);
        ui->pb_editCaffeCinema->setEnabled(false);
        QMessageBox::warning(this, "Не удалось загрузить данные", ex.what());
    }
    ui->le_Answer->setText(QString::number(0));
}

void MainWindow::on_pb_Calculate_clicked()
{
    string city = ui->le_City->text().toStdString();
    string address = ui->le_Address->text().toStdString();
    string caffe = ui->le_Caffe->text().toStdString();
    string cinema = ui->le_Cinema->text().toStdString();
    string institute = ui->le_Institute->text().toStdString();
    uint age = ui->sb_Age->value();
    uint month = ui->cb_Month->currentIndex();
    uint workDays = ui->sb_WorkDays->value();
    bool withAge = ui->ch_AgeEffect->checkState() == Qt::CheckState::Checked;

    Student stud (&_dataLoader, city, address, cinema, caffe, institute, age);

    try {
        uint costs = stud.getCosts(month, workDays, withAge);
        ui->le_Answer->setText(QString::number(costs));
    }
    catch (std::runtime_error& ex) {
        QMessageBox::critical(this, "Не удалось посчитать стоимость", ex.what());
    }
}

void MainWindow::on_cb_Month_currentIndexChanged(int index)
{
    ui->sb_WorkDays->setMaximum(DateUtils::getMonthDays(index));
    ui->sb_WorkDays->setValue(std::min(ui->sb_WorkDays->value(), ui->sb_WorkDays->maximum()));
}

void MainWindow::on_pb_editCosts_clicked()
{
    EditDialog dialog(_dataLoader.costs(), this);
    dialog.exec();
}

void MainWindow::on_pb_editTransport_clicked()
{
    EditDialog dialog(_dataLoader.transport(), this);
    dialog.exec();
}

void MainWindow::on_pb_editInstitute_clicked()
{
    EditDialog dialog(_dataLoader.institute(), this);
    dialog.exec();
}

void MainWindow::on_pb_editCaffeCinema_clicked()
{
    EditDialog dialog(_dataLoader.caffeCinema(), this);
    dialog.exec();
}
