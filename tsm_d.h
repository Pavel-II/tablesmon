#ifndef TSM_D_H
#define TSM_D_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>
#include <QLabel>
#include <QTimer>
#include <QMenu>
#include "sqlsyntaxhighlighter.h"
namespace Ui {
class tsm_d;
}

class tsm_d : public QDialog
{
    Q_OBJECT

public:
    explicit tsm_d(QSqlDatabase _db, QWidget *parent = 0);
    ~tsm_d();
private:
    QTimer *t;
    QSqlDatabase db;
    QPoint dragPosition;
    QSqlQueryModel *model;
    SQLSyntaxHighlighter *ssh;
    void setDB(QSqlDatabase _db);

private slots:
    void updateTime();
    void menuSetup();
    void update(bool up);

private:
    Ui::tsm_d *ui;
    QMenu *menu;
protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);
};

#endif // TSM_D_H
