#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QDialog>

#include "csvparser.h"


namespace Ui {
class EditDialog;
}

class EditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditDialog(CSVParser& parser, QWidget *parent = nullptr);
    ~EditDialog();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::EditDialog *ui;
    CSVParser& _parser;
};

#endif // EDITDIALOG_H
