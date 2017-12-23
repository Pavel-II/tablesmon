#include "tsm_settings.h"
#include "ui_tsm_settings.h"

tsm_settings::tsm_settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tsm_settings)
{
    ui->setupUi(this);
}

tsm_settings::~tsm_settings()
{
    delete ui;
}
