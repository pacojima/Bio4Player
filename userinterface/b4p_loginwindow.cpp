#include "b4p_loginwindow.h"
#include "ui_b4p_loginwindow.h"
#include "../source/b4p_playermanager.h"

LoginWindow::LoginWindow(PlayerManager *mPlayer, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LoginWindow)
{
    ui->setupUi(this);
    this->mPlayer = mPlayer;
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_button_login_clicked()
{
    if( !ui->username->text().isEmpty() || !ui->password->text().isEmpty() ){
        mPlayer->TryLogin( ui->username->text(), ui->password->text() );
    }
}
