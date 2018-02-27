#ifndef TSM_W_H
#define TSM_W_H

#include <QWidget>
#include <QSqlQueryModel>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QLabel>
#include <QTimer>
#include <QMenu>
//#include <QMdiArea>
#include <QFileDialog>
#include <QTextStream>
#include "sqlsyntaxhighlighter.h"

namespace Ui {
class tsm_w;
}

class tsm_w : public QWidget
{
    Q_OBJECT

public:
    explicit tsm_w(QSqlDatabase *_db, QWidget *parent = 0);
    ~tsm_w();

private:
    Ui::tsm_w *ui;
    QTimer *t;
    QSqlDatabase *db;
    QPoint dragPosition;
    QSqlQueryModel *model;
    SQLSyntaxHighlighter *ssh;
    void setDB(QSqlDatabase *_db);

    QMenu *menu;
    bool isActive;
    void setActive(bool set);

private slots:
    void updateTime();
    void menuSetup();
    void update(bool up);
    void openFile(bool);

    void on_pBState_clicked();

    void on_pB_openFile_clicked();

protected:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void contextMenuEvent(QContextMenuEvent *event);

};

#endif // TSM_W_H
