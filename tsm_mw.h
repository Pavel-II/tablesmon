#ifndef TSM_MW_H
#define TSM_MW_H

#include <QMainWindow>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSql>
#include <QMessageBox>
#include <QTimer>
#include <QStandardPaths>
#include <QDir>
#include <tsm_cd.h>
#include <tsm_w.h>
#include <tsm_settings.h>
#include "tsm_w_sb.h"

void aboutApplication();

namespace Ui {
class tsm_mw;
}

class tsm_mw : public QMainWindow
{
    Q_OBJECT

public:
    explicit tsm_mw(QWidget *parent = 0);
    ~tsm_mw();

private:
    Ui::tsm_mw *ui;
    QSqlDatabase db;
    QSqlDatabase localDB;
    QTimer *t;
    QDialog *cd;
    QDialog *sd;
    tsm_w_sb *sb;
    void initLocalDB();

private slots:
    void doConnect();
    void doSettings();
    void closeAllWindows();
    void newTsMon();
    void updateTime();
    void setDBConnect(QString drv,QString dbname,QString hostname, int port, QString user,QString pass, bool saveIt);
};

#endif // TSM_MW_H
