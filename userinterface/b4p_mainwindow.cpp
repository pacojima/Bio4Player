#include "b4p_mainwindow.h"
#include "ui_b4p_mainwindow.h"
#include "../source/b4p_playermanager.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QList>
#include "../userinterface/b4p_liveitem.h"

MainWindow::MainWindow(PlayerManager *mPlayer, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->mPlayer = mPlayer;
    pview = new ViewPanel( this->mPlayer );
    connect( this, SIGNAL( UiUpdate() ), this, SLOT( Update() ) );
}

void MainWindow::Update()
{
    QList<_LIVEDATA> *livedata = mPlayer->GetLiveData();
    QList<_LIVEDATA>::iterator itr;
    QLayoutItem *child;
    while ( ( child = ui->ListLayout->takeAt( 0 ) ) != 0 ){
        delete child->widget();
    }
    for( itr = livedata->begin(); itr != livedata->end(); ++itr ){
        LiveItem *item = new LiveItem( mPlayer );
        item->SetLiveData( itr->live_cothumb, itr->live_ownername, itr->live_id );
        ui->ListLayout->addWidget( item );
    }
}

void MainWindow::InitViewPanel(){
    pview->Initialze();
}

void MainWindow::ShowPlayer(const QString live_id)
{
    QList<_LIVEDATA> *livedata = mPlayer->GetLiveData();
    QList<_LIVEDATA>::iterator itr;
    for( itr = livedata->begin(); itr != livedata->end(); ++itr ){
        if( live_id == itr->live_id ){
            pview->SetLiveData(itr->live_id, itr->live_cothumb, itr->live_title );
            ui->ViewPanel->addWidget( pview );
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
