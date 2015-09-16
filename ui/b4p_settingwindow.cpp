#include "b4p_settingwindow.h"
#include "ui_b4p_settingwindow.h"
#include "b4p_mainwindow.h"

SettingWindow::SettingWindow( MainWindow *mwin, QWidget *parent ) :
    QMainWindow(parent),
    ui(new Ui::SettingWindow)
{
    ui->setupUi(this);
    this->mwin = mwin;
}

SettingWindow::~SettingWindow()
{
    delete ui;
}

void SettingWindow::on_pushButton_login_clicked()
{
    mwin->player_manager->nicookie->GetCookieForAccount( ui->lineEdit_Mail->text(), ui->lineEdit_Password->text() );
}

void SettingWindow::on_buttonBox_accepted()
{
    if( mwin->player_manager->nicookie->GetCookie() != QString( "EMPTY" ) ){
        mwin->CreateLiveWindow( mwin->player_manager->nicookie->GetCookie() );
        mwin->player_manager->bio4searcher->GetLiveID( mwin->player_manager->nicookie->GetCookie() );
    }
    mwin->player_manager->HideSettingWindow();
}

void SettingWindow::on_buttonBox_rejected()
{
    mwin->player_manager->HideSettingWindow();
}
