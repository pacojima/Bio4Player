#ifndef B4P_LOGINWINDOW_H
#define B4P_LOGINWINDOW_H

#include <QMainWindow>

class PlayerManager;

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LoginWindow(PlayerManager *mPlayer, QWidget *parent = 0);
    ~LoginWindow();

private slots:
    void on_button_login_clicked();

private:
    Ui::LoginWindow *ui;
    PlayerManager *mPlayer;
};

#endif // B4P_LOGINWINDOW_H
