#include "tsm_w_sb.h"
#include "ui_tsm_w_sb.h"

tsm_w_sb::tsm_w_sb(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tsm_w_sb)
{
    ui->setupUi(this);
}

tsm_w_sb::~tsm_w_sb()
{
    delete ui;
}

void tsm_w_sb::setConnectInfo(QString info){
    ui->lStatus->setText(info);
}
