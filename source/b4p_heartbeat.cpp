#include "b4p_heartbeat.h"
#include "b4p_playermanager.h"
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QEventLoop>

Heartbeat::Heartbeat(PlayerManager *mPlayer, QObject *parent) : QObject(parent)
{
    this->mPlayer = mPlayer;
}

void Heartbeat::RunHeartBeat()
{
    while( true ){
        QString URL = "http://live.nicovideo.jp/api/heartbeat?v=";
        URL.append( mPlayer->GetCurrentLiveID() );
        QNetworkAccessManager *nam = new QNetworkAccessManager( this );
        QEventLoop eventloop;
        connect( nam, SIGNAL( finished( QNetworkReply* ) ), &eventloop, SLOT( quit() ) );
        QNetworkRequest *rq = new QNetworkRequest( QUrl( URL ) );
        rq->setHeader(  QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded" );
        rq->setHeader( QNetworkRequest::CookieHeader, mPlayer->GetVarNicookie() );
        QNetworkReply *reply = nam->get( *rq );
        eventloop.exec();
        qDebug() << URL;
        qDebug() << reply->readAll();
        QThread::sleep( 60 );
    }
}

