#include "tsm_mw.h"
#include "ui_tsm_mw.h"

void aboutApplication(){
    QMessageBox::information(qApp->activeWindow(),
                             "About this Application",
                             "It's a simple sql monitoring!");
}

tsm_mw::tsm_mw(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::tsm_mw)
{
    ui->setupUi(this);

    cd = new tsm_cd(this);
    t = new QTimer(this);

    connect(cd,SIGNAL(setConnect(QString,QString,QString,int,QString,QString)),
            this, SLOT(setDBConnect(QString,QString,QString,int,QString,QString)));
    connect(ui->actionNew_ts_mon, SIGNAL(triggered(bool)), this, SLOT(newTsMon()));
    connect(ui->actionSettings,SIGNAL(triggered(bool)),this, SLOT(doConnect()));
    connect(t, SIGNAL(timeout()), this, SLOT(updateTime()));
    //
    ui->menuAbout->addAction(QObject::tr("Application"), []() { aboutApplication(); });
    ui->menuAbout->addSeparator();
    ui->menuAbout->addAction(QObject::tr("Qt"), []() { qApp->aboutQt(); });

    cd->exec();
}

void tsm_mw::doConnect(){
    t->stop();
    cd->exec();
}

void tsm_mw::setDBConnect(QString drv, QString dbname, QString hostname, int port, QString user, QString pass){

    db = QSqlDatabase::addDatabase(drv);

    db.setDatabaseName(dbname);
    db.setHostName(hostname);
    db.setPort(port);
    db.setUserName(user);
    db.setPassword(pass);
    if(db.open()){
        t->start(1000);
    } else {
        QMessageBox::information(this, "db not open",db.lastError().text());
        t->stop();
        ui->mdiArea->addSubWindow(cd);
        cd->showMaximized();
    }
    cd->accept();
    this->newTsMon();
}

tsm_mw::~tsm_mw()
{
    if (t) delete (t);
    delete ui;
}

void tsm_mw::newTsMon(){
    QWidget *w = new tsm_w(&db);

    ui->mdiArea->addSubWindow(w);
    w->showNormal();
}

void tsm_mw::updateTime(){
    if(!db.isOpen()){
        QMessageBox::information(this, "db not open",db.lastError().text());
        t->stop();
        ui->mdiArea->addSubWindow(cd);
        cd->showMaximized();
    }
}
