#include "tsm_settings.h"
#include "ui_tsm_settings.h"

tsm_settings::tsm_settings(QSqlDatabase DB, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tsm_settings)
{
    ui->setupUi(this);
    _DB = DB;
    get_settings();
}

tsm_settings::~tsm_settings()
{
    delete ui;
}

void tsm_settings::on_buttonBox_accepted()
{
    emit seveDefPorts(
                ui->sbDB2defPort->value(),
                ui->sbIBASEdefPort->value(),
                ui->sbLINTERdefPort->value(),
                ui->sbMYSQLdefPort->value(),
                ui->sbOCIdefPort->value(),
                ui->sbODBCdefPort->value(),
                ui->sbPSQLdefPort->value(),
                ui->sbTDSdefPort->value());
    emit saveUpdateInterval(ui->sbUpdateInterval->value());
    this->accept();
}

void tsm_settings::get_settings()
{
    ui->sbDB2defPort->setValue(50000);
    ui->sbIBASEdefPort->setValue(3050);
    ui->sbLINTERdefPort->setValue(1060);
    ui->sbMYSQLdefPort->setValue(3306);
    ui->sbOCIdefPort->setValue(1521);
    ui->sbODBCdefPort->setValue(1433);
    ui->sbPSQLdefPort->setValue(5432);
    ui->sbTDSdefPort->setValue(10000);
}
