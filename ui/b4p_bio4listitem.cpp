#include "b4p_bio4listitem.h"
#include "ui_b4p_bio4listitem.h"
#include "b4p_mainwindow.h"

Bio4ListItem::Bio4ListItem( MainWindow *mwin, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Bio4ListItem)
{
    ui->setupUi(this);
    this->mwin = mwin;
}

void Bio4ListItem::SetLiveData( const LiveData live_data ){
    this->live_data = live_data;
    ui->pushButton->setText( live_data.GetLiveTitle() );
    QString label_text = live_data.GetLiveOwner();
    label_text.append( "@" );
    label_text.append( live_data.GetLiveComunity() );
    ui->label_ownercomunity->setText( label_text );
    ui->label_livedescription->setText( live_data.GetLiveDescription() );
}

Bio4ListItem::~Bio4ListItem()
{
    delete ui;
}

void Bio4ListItem::on_pushButton_clicked()
{
    mwin->lwin->ConnectShow( live_data.GetLiveID() );
}
