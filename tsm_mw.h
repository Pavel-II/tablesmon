#ifndef TSM_MW_H
#define TSM_MW_H

#include <QMainWindow>

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QtSql/QSql>
#include <QMessageBox>
#include <QSettings>
#include <QTimer>
#include <tsm_cd.h>
#include <tsm_w.h>

#include <QDebug>

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
    QTimer *t;
    QDialog *cd;

private slots:
    void doConnect();
    void newTsMon();
    void updateTime();
    void setDBConnect(QString drv,QString dbname,QString hostname, int port, QString user,QString pass);
};

#endif // TSM_MW_H
