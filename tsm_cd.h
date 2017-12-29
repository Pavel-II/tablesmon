#ifndef TSM_CD_H
#define TSM_CD_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMenu>
#include <QAction>

namespace Ui {
class tsm_cd;
}

class tsm_cd : public QDialog
{
    Q_OBJECT

public:
    explicit tsm_cd(QSqlDatabase DB, QWidget *parent = 0);
    ~tsm_cd();
    QSqlDatabase _DB;
signals:
    void setConnect(QString, QString, QString,int, QString, QString, bool);

private slots:
    void on_okButton_clicked();
    void on_pushButton_pressed();
    void on_pushButton_released();
    void on_comboDriver_currentTextChanged(const QString &arg1);
    void fillFromSavedConnection();

    void on_pbCleanAndDeleteSeved_clicked();

private:
    Ui::tsm_cd *ui;
    QMenu *pbSCMenu;
    void setupSavedConnectionsMenu();
};

#endif // TSM_CD_H
