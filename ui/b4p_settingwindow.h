#ifndef B4P_SETTING_WINDOW_H
#define B4P_SETTING_WINDOW_H

#include <QMainWindow>

class MainWindow;

namespace Ui {
class SettingWindow;
}

class SettingWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit SettingWindow( MainWindow *mwin, QWidget *parent = 0 );
    ~SettingWindow();

private:
    Ui::SettingWindow *ui;
    MainWindow *mwin;

private slots:
    void on_pushButton_login_clicked();
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
};

#endif // B4P_SETTING_WINDOW_H
