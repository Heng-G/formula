#include "e.h"
#include "ui_e.h"
#include <QString>
#include <QDebug>


QString e_name;

e::e(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::e)
{
    ui->setupUi(this);


}

e::~e()
{
    delete ui;
}

void e::on_buttonBox_accepted()
{

    e_name = ui->textEdit->toPlainText();


}
