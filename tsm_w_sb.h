#ifndef TSM_W_SB_H
#define TSM_W_SB_H

#include <QWidget>

namespace Ui {
class tsm_w_sb;
}

class tsm_w_sb : public QWidget
{
    Q_OBJECT

signals:
    void disconnectFromDB();
public:
    explicit tsm_w_sb(QWidget *parent = 0);
    ~tsm_w_sb();
    void setConnectInfo(QString info);

private slots:

    void on_pbDisconnect_clicked();

private:
    Ui::tsm_w_sb *ui;
};

#endif // TSM_W_SB_H
