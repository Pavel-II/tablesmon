#include "tsm_d.h"
#include "ui_tsm_d.h"

tsm_d::tsm_d(QSqlDatabase _db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tsm_d)
{
    ui->setupUi(this);
    this->setDB(_db);
    this->menuSetup();
    //
    ssh = new SQLSyntaxHighlighter(ui->textEdit->document());
    //
    model = new QSqlQueryModel(ui->tableView);
    model->setQuery(QSqlQuery(ui->textEdit->toPlainText(), db));
    ui->tableView->setModel(model);
    //
    t = new QTimer(this);

    QPalette palette = ui->lStateText->palette();
    palette.setColor(ui->lStateText->backgroundRole(), Qt::red);
    palette.setColor(ui->lStateText->foregroundRole(), Qt::red);
    ui->lStateText->setPalette(palette);
    ui->lStateText->setText("idle");

    connect(t, SIGNAL(timeout()), this, SLOT(updateTime()));
    connect(ui->actionUpdate, SIGNAL(triggered(bool)), this, SLOT(update(bool)));
    updateTime();
    ui->textEdit->addAction(ui->actionUpdate);
}

tsm_d::~tsm_d(){
    t->stop();

    delete ui;
}

void tsm_d::setDB(QSqlDatabase _db){
    db = _db;
}

void tsm_d::menuSetup(){
    menu = new QMenu(this);
    menu->addSeparator();
    menu->addAction(ui->actionUpdate);
    menu->addSeparator();
}
void tsm_d::update(bool up){
    if(up){
        t->start(1000);
        QPalette palette = ui->lStateText->palette();
        palette.setColor(ui->lStateText->backgroundRole(), Qt::green);
        palette.setColor(ui->lStateText->foregroundRole(), Qt::green);
        ui->lStateText->setPalette(palette);
         ui->lStateText->setText("ACTIVE");
    } else {
        t->stop();
        QPalette palette = ui->lStateText->palette();
        palette.setColor(ui->lStateText->backgroundRole(), Qt::red);
        palette.setColor(ui->lStateText->foregroundRole(), Qt::red);
        ui->lStateText->setPalette(palette);
        ui->lStateText->setText("idle");
    }
}
void tsm_d::updateTime(){
    model->setQuery(QSqlQuery(ui->textEdit->toPlainText(), db));
}

void tsm_d::mouseMoveEvent(QMouseEvent *event){
    if (event->buttons() == Qt::LeftButton) {
        move(event->globalPos() - dragPosition);
        event->accept();
    }

}

void tsm_d::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton) {
        dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void tsm_d::contextMenuEvent(QContextMenuEvent *event){
    menu->exec(event->globalPos());
}
