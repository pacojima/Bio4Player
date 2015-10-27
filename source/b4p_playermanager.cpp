#include "b4p_playermanager.h"

PlayerManager::PlayerManager(QObject *parent) : QObject(parent)
{
    mwin = new MainWindow( this );
    lwin = new LoginWindow( this );
    lmng = new Login( this );
    hmng = new Heartbeat( this );
    livemng = new LiveSearcher( this );
    connect( this, SIGNAL( uiUpdate() ), this, SLOT( Update() ) );
}

void PlayerManager::Initialize()
{

    if( lmng->CheckLogin() ){
        mwin->show();
        varnicookie = lmng->EncodeSession( nicookie );
        StartUpdate();
        mwin->InitViewPanel();
    }else{
        lwin->show();
    }
}

void PlayerManager::TryLogin(const QString username, const QString password)
{
    QString nicookie = lmng->TryLogin(username, password);
    if( nicookie != "" ){
        if( lmng->CheckLogin() ){
            lwin->hide();
            mwin->show();
            this->nicookie = nicookie;
            varnicookie = lmng->EncodeSession( nicookie );
            StartUpdate();
            mwin->InitViewPanel();
        }
    }
}

QList<_LIVEDATA> *PlayerManager::GetLiveData()
{
    return &livedata;
}

void PlayerManager::SetLiveData(const QList<_LIVEDATA> livedata)
{
    this->livedata = livedata;
}

void PlayerManager::ClearLiveData()
{
    livedata.clear();
}

QString PlayerManager::GetStrNicookie()
{
    return nicookie;
}

QVariant PlayerManager::GetVarNicookie()
{
    return varnicookie;
}

void PlayerManager::SetNicookie(const QString nicookie)
{
    this->nicookie = nicookie;
}

LiveSearcher *PlayerManager::GetLiveSearcher()
{
    return livemng;
}

void PlayerManager::StartUpdate()
{
    search_thread = new QThread();
    livemng->moveToThread( search_thread );
    connect( search_thread, SIGNAL( started() ), livemng, SLOT( Search() ) );
    search_thread->start();
    heartbeat_thread = new QThread();
    hmng->moveToThread( heartbeat_thread );
    connect( heartbeat_thread, SIGNAL( started() ), hmng, SLOT( RunHeartBeat() ) );
    heartbeat_thread->start();
}

void PlayerManager::ShowPlayer( const QString live_id )
{
    current_live_id = live_id;
    mwin->ShowPlayer( live_id );
}

QString PlayerManager::GetCurrentLiveID()
{
    return current_live_id;
}

void PlayerManager::Update()
{
    emit mwin->UiUpdate();
}
