#ifndef TSM_SETTINGS_H
#define TSM_SETTINGS_H

#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class tsm_settings;
}

class tsm_settings : public QDialog
{
    Q_OBJECT

public:
    explicit tsm_settings(QSqlDatabase DB, QWidget *parent = 0);
    ~tsm_settings();
signals:
    void seveDefPorts(int,int,int,int,int,int,int,int);
    void saveUpdateInterval(int);

private slots:
    void on_buttonBox_accepted();
    void get_settings();

private:
    Ui::tsm_settings *ui;
    QSqlDatabase _DB;
};

#endif // TSM_SETTINGS_H
