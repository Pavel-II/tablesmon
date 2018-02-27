#include "tsm_mw.h"
#include "ui_tsm_mw.h"

void aboutApplication(){
    QMessageBox msgBoxAboutApp(qApp->activeWindow());
    msgBoxAboutApp.setWindowTitle(QObject::tr("About this Application"));
    msgBoxAboutApp.setTextFormat(Qt::RichText);
    msgBoxAboutApp.setText(QObject::tr("It's a simple sql monitoring!<br>"
                   "<a href='https://github.com/Pavel-II/tablesmon'>Application on github</a>"));
    msgBoxAboutApp.exec();
}

tsm_mw::tsm_mw(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::tsm_mw)
{
    ui->setupUi(this);
    //
    initLocalDB();
    //
    cd = new tsm_cd(localDB, this);
    sd = new tsm_settings(localDB, this);
    t = new QTimer(this);

    connect(cd,SIGNAL(   setConnect(QString,QString,QString,int,QString,QString, bool)),
            this, SLOT(setDBConnect(QString,QString,QString,int,QString,QString, bool)));
    connect(ui->actionNew_ts_mon, SIGNAL(triggered(bool)), this, SLOT(newTsMon()));

    connect(ui->actionConnection,SIGNAL(triggered(bool)),this, SLOT(doConnect()));
    connect(ui->actionSettings,  SIGNAL(triggered(bool)),this, SLOT(doSettings()));
    connect(ui->actionClose_all, SIGNAL(triggered(bool)),this, SLOT(closeAllWindows()));
    ui->actionSettings->setDisabled(true); // Not implemented yet

    connect(t, SIGNAL(timeout()), this, SLOT(updateTime()));
    //
    ui->menuAbout->addAction(QObject::tr("Application"), []() { aboutApplication(); });
    ui->menuAbout->addSeparator();
    ui->menuAbout->addAction(QObject::tr("Qt"), []() { qApp->aboutQt(); });

    sb = new tsm_w_sb();
    connect(sb, SIGNAL(disconnectFromDB()),this, SLOT(disconnectFromDB()));
    ui->statusBar->addWidget(sb);

    cd->exec();
}

void tsm_mw::initLocalDB(){
    //
    localDB = QSqlDatabase::addDatabase("QSQLITE", "localDB");
    //
    QString path = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    //
    if (!QDir(path).exists()){
        QDir().mkdir(path);
    }
    //
    localDB.setDatabaseName(path+"/tsm.db");
    if(localDB.open()){
        //
        QSqlQuery q = localDB.exec("SELECT count(*) as tc FROM sqlite_master "
                                   "WHERE type='table' AND name='tsm_saved_connections';");
        //
        if(q.first() && (q.value("tc").toInt() == 0)){
            localDB.exec("CREATE TABLE tsm_saved_connections"
                         "("
                            "id integer primary key autoincrement not null,"
                             "driver character varying,"
                             "hostname character varying,"
                             "port integer,"
                             "dbname character varying,"
                             "dbuser character varying,"
                             "pass character varying"
                         ");");
        }
    } else {
        QMessageBox::information(this, "", "Local settings fail\n"+localDB.lastError().text());
    }
}
void tsm_mw::closeAllWindows(){
    ui->mdiArea->closeAllSubWindows();
}
void tsm_mw::disconnectFromDB(){
    t->stop();
    db.close();
    sb->setConnectInfo(QString("Disconnected"));
}

void tsm_mw::doSettings(){
    sd->exec();
}

void tsm_mw::doConnect(){
    t->stop();
    cd->exec();
}

void tsm_mw::setDBConnect(QString drv, QString dbname, QString hostname, int port, QString user, QString pass, bool saveIt){

    db.removeDatabase(drv);

    db = QSqlDatabase::addDatabase(drv);

    db.setDatabaseName(dbname);
    db.setHostName(hostname);
    db.setPort(port);
    db.setUserName(user);
    db.setPassword(pass);
    if(db.open()){
        t->start(1000);
        sb->setConnectInfo(QString("Connect to host: %1:%4 by %2@%3")
                           .arg(hostname)
                           .arg(user)
                           .arg(dbname)
                           .arg(QString::number(port)));
        this->newTsMon();
        // save if connection successful
        if (saveIt){
            if (localDB.isOpen()){
                QString select = QString("select count(*) from tsm_saved_connections where "
                                         "driver =   '%1' and "
                                         "hostname = '%2' and "
                                         "port =     %3  and "
                                         "dbname =   '%4' and "
                                         "dbuser =   '%5'")
                        .arg(drv).arg(hostname).arg(port).arg(dbname).arg(user);
                //
                QSqlQuery q = localDB.exec(select);
                //
                if(q.first() && q.value(0).toInt() == 0){
                    QString insert = QString("INSERT INTO tsm_saved_connections("
                                             "driver, hostname, port, dbname, dbuser)"
                                             "VALUES ('%1', '%2', %3, '%4', '%5');")
                                         .arg(drv)
                                         .arg(hostname)
                                         .arg(port)
                                         .arg(dbname)
                                         .arg(user);
                    localDB.exec(insert);
                }
            }
        }
        //
    } else {        
        QMessageBox::information(this, "db not open",db.lastError().text());
        sb->setConnectInfo(QString("Disconnected"));
        t->stop();
    }
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
