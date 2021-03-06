#include "tsm_w.h"
#include "ui_tsm_w.h"

tsm_w::tsm_w(QSqlDatabase *_db, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tsm_w)
{
    ui->setupUi(this);
    this->setDB(_db);
    this->menuSetup();
    //
    ssh = new SQLSyntaxHighlighter(ui->textEdit->document());
    model = new QSqlQueryModel(ui->tableView);
    ui->tableView->setModel(model);
    t = new QTimer(this);
    isActive = false;
    //
    this->setActive(false);
    connect(t,                    SIGNAL(timeout()),       this, SLOT(updateTime()));
    connect(ui->actionUpdateByF5, SIGNAL(triggered(bool)), this, SLOT(update(bool)));
    connect(ui->actionOpenFile,   SIGNAL(triggered(bool)), this, SLOT(openFile(bool)));
    ui->textEdit->addAction(ui->actionUpdateByF5);
    ui->textEdit->setFocus();
}

tsm_w::~tsm_w()
{
    t->stop();
    if (t) delete (t);
    if (model) delete (model);
    if (menu) delete (menu);
    delete ui;
}


void tsm_w::setDB(QSqlDatabase *_db){
    db = _db;
}

void tsm_w::menuSetup(){
    menu = new QMenu(this);
    menu->addSeparator();
    menu->addAction(ui->actionUpdateByF5);
    menu->addSeparator();
    menu->addAction(ui->actionOpenFile);
    menu->addSeparator();
}
void tsm_w::setActive(bool set){
    QPalette palette = ui->pBState->palette();
    QString state = "";
    if(set && db->isOpen()){
        palette.setColor(ui->pBState->backgroundRole(), Qt::green);
        palette.setColor(ui->pBState->foregroundRole(), Qt::green);
        state = QObject::tr("ACTIVE!");
    } else {
        palette.setColor(ui->pBState->backgroundRole(), Qt::red);
        palette.setColor(ui->pBState->foregroundRole(), Qt::red);
        ui->pBState->setPalette(palette);
        state = QObject::tr("idle");
    }
    ui->pBState->setPalette(palette);
    ui->pBState->setText(state);
}
void tsm_w::update(bool up){
    isActive = up;
    this->setActive(isActive);
    if(up && db->isOpen()){
        t->start(1000);
    } else {
        t->stop();
        this->setWindowTitle(QObject::tr("Sql watcher"));
    }
}

void tsm_w::openFile(bool){
    //

    QFileDialog dialog(this);
    dialog.setFileMode(QFileDialog::ExistingFile);
    dialog.setViewMode(QFileDialog::Detail);
    QString fileName;
    if (dialog.exec())
        fileName = dialog.selectedFiles().at(0);
    //
    QFile f(fileName);
    if (!f.open(QFile::ReadOnly | QFile::Text)) return;
    QTextStream in(&f);
    ui->textEdit->clear();
    ui->textEdit->setText(in.readAll());

}

void tsm_w::updateTime(){
    //
    this->setWindowTitle(QObject::tr("Sql watcher") +" [" +ui->textEdit->toPlainText()+ "]");
    //
    model->setQuery(QSqlQuery(ui->textEdit->toPlainText(), *db));
}

void tsm_w::mouseMoveEvent(QMouseEvent *event){
    if (event->buttons() == Qt::LeftButton) {
        move(event->globalPos() - dragPosition);
        event->accept();
    }
}

void tsm_w::mousePressEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton) {
        dragPosition = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void tsm_w::contextMenuEvent(QContextMenuEvent *event){
    menu->exec(event->globalPos());
}

void tsm_w::on_pBState_clicked()
{
    this->update(!isActive);
}

void tsm_w::on_pB_openFile_clicked()
{
    ui->actionOpenFile->activate(QAction::Trigger);
}
