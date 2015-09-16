#include "b4p_mainwindow.h"
#include "ui_b4p_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    swin( new SettingWindow( this, this ) )
{
    ui->setupUi(this);
    ui->statusBar->showMessage( QString("ログインされてません") );
    player_manager = new PlayerManager( this, this->swin, this->lwin );
}

void MainWindow::ChangeStatusBar( const QString status ){
    ui->statusBar->showMessage( status );
}

void MainWindow::AppendListItem( Bio4ListItem *item ){
    ui->ListLayout->addWidget( item );
}

void MainWindow::CreateLiveWindow( const QString cookie ){
    lwin = new LiveWindow( cookie, this, this );
}

void MainWindow::ClearListItem(){
    QLayoutItem *child;
    while ( ( child = ui->ListLayout->takeAt( 0 ) ) != 0 ){
        delete child->widget();
    }
}

MainWindow::~MainWindow()
{
    delete swin;
    delete player_manager;
    delete ui;
}

void MainWindow::on_actionSettings_triggered()
{
    player_manager->ShowSettingWindow();
}

void MainWindow::on_actionWhatIsBio4Player_triggered()
{
}

void MainWindow::on_buttonReflesh_clicked()
{
    if( player_manager->nicookie->GetCookie() != QString( "EMPTY" ) ){
        player_manager->bio4searcher->GetLiveID( player_manager->nicookie->GetCookie() );
    }
}
