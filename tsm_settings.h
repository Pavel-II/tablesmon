#ifndef TSM_SETTINGS_H
#define TSM_SETTINGS_H

#include <QDialog>

namespace Ui {
class tsm_settings;
}

class tsm_settings : public QDialog
{
    Q_OBJECT

public:
    explicit tsm_settings(QWidget *parent = 0);
    ~tsm_settings();

private:
    Ui::tsm_settings *ui;
};

#endif // TSM_SETTINGS_H
