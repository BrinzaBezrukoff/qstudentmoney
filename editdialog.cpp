#include "editdialog.h"
#include "ui_editdialog.h"

#include <iostream>

EditDialog::EditDialog(CSVParser& parser, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditDialog),
    _parser(parser)
{
    ui->setupUi(this);
    ui->table->setColumnCount(_parser.getColumnsCount());
    ui->table->setRowCount(_parser.getRowsCount());
    setWindowTitle(QString::fromStdString(_parser.getPath()));
    QStringList headers;
    for (auto&& column: _parser.getHeader()) {
        headers.append(QString::fromStdString(column));
    }
    ui->table->setHorizontalHeaderLabels(headers);
    for (size_t i = 0; i < _parser.getRowsCount(); i++) {
        for (size_t j = 0; j < _parser.getColumnsCount(); j++) {
            ui->table->setItem(i, j, new QTableWidgetItem(QString::fromStdString(_parser[i][j])));
        }
    }
}

EditDialog::~EditDialog()
{
    delete ui;
}

void EditDialog::on_buttonBox_accepted()
{
    for (size_t i = 0; i < _parser.getRowsCount(); i++) {
        for (size_t j = 0; j < _parser.getColumnsCount(); j++) {
            _parser[i][j] = ui->table->item(i, j)->text().toStdString();
        }
    }
    _parser.write();
}

void EditDialog::on_buttonBox_rejected()
{
    close();
}
