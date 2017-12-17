#ifndef TSM_CD_H
#define TSM_CD_H

#include <QDialog>
#include <QSqlDatabase>
#include <QDebug>

namespace Ui {
class tsm_cd;
}

class tsm_cd : public QDialog
{
    Q_OBJECT

public:
    explicit tsm_cd(QWidget *parent = 0);
    ~tsm_cd();
signals:
    void setConnect(QString, QString, QString,int, QString, QString);

private slots:
    void on_okButton_clicked();

    void on_pushButton_pressed();

    void on_pushButton_released();

private:
    Ui::tsm_cd *ui;

};

#endif // TSM_CD_H