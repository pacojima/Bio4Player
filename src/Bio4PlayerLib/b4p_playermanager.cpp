#include "b4p_playermanager.h"
#include "../../ui/b4p_mainwindow.h"

PlayerManager::PlayerManager( MainWindow *mwin, SettingWindow *swin, LiveWindow *lwin, QObject *parent) : QObject(parent){
    this->mwin = mwin;
    this->swin = swin;
    this->lwin = lwin;
    this->setting = new Setting();
    this->nicookie = new Nicookie( this->mwin, this->swin );
    this->bio4searcher = new Bio4Searcher( this->mwin );
    listwedgets.clear();
}

void PlayerManager::ShowSettingWindow() const{
    swin->show();
}

void PlayerManager::AddListItem( const LiveData livedata ){
    Bio4ListItem *list = new Bio4ListItem( mwin );
    list->SetLiveData( livedata );
    mwin->AppendListItem( list );
}

void PlayerManager::HideSettingWindow() const{
    swin->hide();
}

PlayerManager::~PlayerManager(){
    delete setting;
    delete nicookie;
}

