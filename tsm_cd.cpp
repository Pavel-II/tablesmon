#include "tsm_cd.h"
#include "ui_tsm_cd.h"

tsm_cd::tsm_cd(QSqlDatabase DB, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::tsm_cd)
{
    _DB = DB;
    ui->setupUi(this);
    ui->comboDriver->addItems(QSqlDatabase::drivers());// Add availables drivers
    ui->comboDriver->setCurrentIndex(ui->comboDriver->findText("QPSQL"));
    //
    pbSCMenu = new QMenu;
    setupSavedConnectionsMenu();
}

tsm_cd::~tsm_cd(){
    delete ui;
}

void tsm_cd::on_okButton_clicked()
{
    setupSavedConnectionsMenu();
    emit setConnect(ui->comboDriver->itemText(ui->comboDriver->currentIndex()),
                    ui->editDatabase->text(),
                    ui->editHostname->text(),
                    ui->spinBoxPort->value(),
                    ui->editUsername->text(),
                    ui->editPassword->text(),
                    ui->cbSaveConnection->isChecked());
    this->accept();
}


void tsm_cd::on_pushButton_pressed()
{
    ui->editPassword->setEchoMode(QLineEdit::Normal);
}

void tsm_cd::on_pushButton_released()
{
    ui->editPassword->setEchoMode(QLineEdit::Password);
}

void tsm_cd::on_comboDriver_currentTextChanged(const QString &arg1)
{
    //
    if ((arg1 == "QSQLITE") || (arg1 == "QSQLITE2")) {
         ui->spinBoxPort->setReadOnly(true);
         ui->spinBoxPort->setEnabled(false);
    } else {
        ui->spinBoxPort->setReadOnly(false);
        ui->spinBoxPort->setEnabled(true);
        // read port from settings
        ui->spinBoxPort->setValue(5432);
    }
}

void tsm_cd::fillFromSavedConnection(){
    //
    QAction *senderAction = (QAction *) sender();
    QStringList acData = senderAction->data().toStringList();
    ui->comboDriver->setCurrentIndex(ui->comboDriver->findText(acData.at(0).toLocal8Bit().constData()));
    ui->editHostname->setText(acData.at(1).toLocal8Bit().constData());
    ui->editDatabase->setText(acData.at(2).toLocal8Bit().constData());
    ui->editUsername->setText(acData.at(3).toLocal8Bit().constData());
    ui->spinBoxPort->setValue(acData.at(4).toInt());
}

void tsm_cd::setupSavedConnectionsMenu(){
    //
    pbSCMenu->clear();
    QAction *action;
    // get from saved connections
    QSqlQuery q = _DB.exec("select tsc.*, dbuser||'@'|| dbname || "
                           "' on '|| hostname || ':'|| port ||"
                           "' via driver ' || driver as 'connection string' "
                           "from tsm_saved_connections as tsc");
    while (q.next()){
        action = new QAction(q.value("connection string").toString());
        action->setText(q.value("connection string").toString());
        action->setData(QStringList() <<
                        q.value("driver").toString() <<
                        q.value("hostname").toString() <<
                        q.value("dbname").toString() <<
                        q.value("dbuser").toString() <<
                        q.value("port").toString());
        pbSCMenu->addAction(action);
        //
        connect(action, SIGNAL(triggered()), this, SLOT(fillFromSavedConnection()));
    }
    //
    pbSCMenu->addSeparator();
    ui->pbSavedConnections->setMenu(pbSCMenu);
    ui->pbSavedConnections->setText("");// text on button for visible it on conctructor
}

void tsm_cd::on_pbCleanAndDeleteSeved_clicked()
{
    _DB.exec(QString("delete from tsm_saved_connections where "
                     "driver = '%1' and "
                     "hostname = '%2' and "
                     "port = %3 and "
                     "dbname = '%4' and "
                     "dbuser = '%5'")
             .arg(ui->comboDriver->currentText())
             .arg(ui->editHostname->text())
             .arg(ui->spinBoxPort->value())
             .arg(ui->editDatabase->text())
             .arg(ui->editUsername->text()));
    ui->editDatabase->clear();
    ui->editHostname->clear();
    ui->editPassword->clear();
    ui->editUsername->clear();
    setupSavedConnectionsMenu();
}
