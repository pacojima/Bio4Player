#include "b4p_liveitem.h"
#include "ui_b4p_liveitem.h"
#include "../source/b4p_playermanager.h"

LiveItem::LiveItem(PlayerManager *mPlayer, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LiveItem)
{
    ui->setupUi(this);
    ui->Thumbnail->setCursor( Qt::BlankCursor );
    this->mPlayer = mPlayer;
}

LiveItem::~LiveItem()
{
    delete ui;
}

void LiveItem::SetLiveData(const QString thumb, const QString ownername, const QString live_id )
{
    ui->OwnerName->setText( ownername );
    ui->Thumbnail->load( QUrl( thumb ) );
    this->live_id = live_id;
}

void LiveItem::mousePressEvent(QMouseEvent *e)
{
    mPlayer->ShowPlayer( live_id );
}
