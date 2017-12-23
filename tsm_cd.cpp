#include "tsm_cd.h"
#include "ui_tsm_cd.h"

tsm_cd::tsm_cd(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tsm_cd)
{
    ui->setupUi(this);
    ui->comboDriver->addItems(QSqlDatabase::drivers());
    ui->comboDriver->setCurrentIndex(ui->comboDriver->findText("QPSQL"));
}

tsm_cd::~tsm_cd(){
    delete ui;
}

void tsm_cd::on_okButton_clicked()
{
    emit setConnect(
                ui->comboDriver->itemText(ui->comboDriver->currentIndex()),
                ui->editDatabase->text(),
                ui->editHostname->text(),
                ui->spinBoxPort->value(),
                ui->editUsername->text(),
                ui->editPassword->text());
    this->accept();
}


void tsm_cd::on_pushButton_pressed()
{
    ui->editPassword->setEchoMode(QLineEdit::Normal);
}

void tsm_cd::on_pushButton_released()
{
    ui->editPassword->setEchoMode(QLineEdit::Password);
}

void tsm_cd::on_comboDriver_currentTextChanged(const QString &arg1)
{
    //
    if ((arg1 == "QSQLITE") || (arg1 == "QSQLITE2")) {
         ui->spinBoxPort->setReadOnly(true);
         ui->spinBoxPort->setEnabled(false);
    } else {
        ui->spinBoxPort->setReadOnly(false);
        ui->spinBoxPort->setEnabled(true);
        // read post from settings
        ui->spinBoxPort->setValue(5432);
    }
}

void tsm_cd::on_cbSaveConnection_clicked(bool checked)
{
    if (checked) {
        // save connection
    } else {
        // !save
    }
}
