#include "b4p_livesearcher.h"
#include "b4p_playermanager.h"
#include <QList>
#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QUrlQuery>
#include <QThread>

LiveSearcher::LiveSearcher(PlayerManager *mPlayer, QObject *parent) : QObject(parent)
{
    this->mPlayer = mPlayer;
}

void LiveSearcher::Search(){
    while( true ){
        mPlayer->ClearLiveData();
        _LIVEDATA live;
        QList<_LIVEDATA> livedata;
        QNetworkAccessManager *nam = new QNetworkAccessManager( this );
        QEventLoop eventloop;
        connect( nam, SIGNAL( finished( QNetworkReply* ) ), &eventloop, SLOT( quit() ) );
        QNetworkRequest rq( QUrl( "https://thick-pacojima.ssl-lolipop.jp/bio4playerapi/getbio4lives.php" ) );
        rq.setHeader( QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded" );
        QUrlQuery params;
        params.addQueryItem( "user_nicookie", QUrl::toPercentEncoding( mPlayer->GetStrNicookie() ) );
        QNetworkReply *reply = nam->post( rq, params.toString( QUrl::FullyEncoded ).toUtf8() );
        eventloop.exec();
        QString xml = reply->readAll();
        QRegExp reg_live( "<live_id no=\"\\d+\">(lv[0-9]+)</live_id>" );
        QRegExp reg_status( "<getbio4lives status=\"([0-9]+)\"/>" );
        reg_status.indexIn( xml );
        if( reg_status.cap( 1 ) == "0" ){
            int pos = 0;
            while( ( pos = reg_live.indexIn( xml, pos ) ) != -1 ){
                QString URL_GETLIVEINFOSTATUS = "http://watch.live.nicovideo.jp/api/getplayerstatus?v=";
                URL_GETLIVEINFOSTATUS.append( reg_live.cap( 1 ) );
                nam = new QNetworkAccessManager( this );
                QNetworkRequest *rq = new QNetworkRequest( QUrl( URL_GETLIVEINFOSTATUS ) );
                connect( nam, SIGNAL( finished( QNetworkReply* ) ), &eventloop, SLOT( quit() ) );
                rq->setHeader(  QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded" );
                rq->setHeader( QNetworkRequest::CookieHeader, mPlayer->GetVarNicookie() );
                reply = nam->get( *rq );
                eventloop.exec();
                QString xml = reply->readAll();
                QRegExp reg_status( "<getplayerstatus status=\"([a-z]+)\" time=\"\\d+\">" );
                //Regs
                QRegExp reg_live_id( "<id>(lv[0-9]+)</id>" );
                QRegExp reg_live_title( "<title>(.+)</title>" );
                QRegExp reg_live_description( "<description>(.+)</description>" );
                QRegExp reg_live_comunity( "<default_community>(co[0-9]+)</default_community>" );
                QRegExp reg_live_owner( "<owner_name>(.+)</owner_name>" );
                QRegExp reg_live_basetime( "<base_time>([0-9]+)</base_time>" );
                QRegExp reg_live_opentime( "<open_time>([0-9]+)</open_time>" );
                QRegExp reg_live_starttime( "<start_time>([0-9]+)</start_time>" );
                QRegExp reg_live_endtime( "<end_time>([0-9]+)</end_time>" );
                QRegExp reg_live_watchco( "<watch_count>([0-9]+)</watch_count>" );
                QRegExp reg_live_commentco( "<comment_count>([0-9]+)</comment_count>" );
                QRegExp reg_live_comthumburl( "<picture_url>(.+)</picture_url>" );
                QRegExp reg_server_addr( "<addr>(.+)</addr>" );
                QRegExp reg_server_port( "<port>([0-9]+)</port>" );
                QRegExp reg_server_thread( "<thread>([0-9]+)</thread>" );

                reg_status.indexIn( xml );
                if( reg_status.cap( 1 ) == "ok" ){

                    reg_live_id.indexIn( xml );
                    live.live_id = reg_live_id.cap( 1 );

                    reg_live_title.indexIn( xml );
                    live.live_title = reg_live_title.cap( 1 );

                    reg_live_description.indexIn( xml );
                    live.live_description = reg_live_description.cap( 1 );

                    reg_live_comunity.indexIn( xml );
                    live.live_coid = reg_live_comunity.cap( 1 );

                    reg_live_owner.indexIn( xml );
                    live.live_ownername = reg_live_owner.cap( 1 );

                    reg_live_basetime.indexIn( xml );
                    live.live_basetime = reg_live_basetime.cap( 1 );

                    reg_live_opentime.indexIn( xml );
                    live.live_opentime = reg_live_opentime.cap( 1 );

                    reg_live_starttime.indexIn( xml );
                    live.live_starttime = reg_live_starttime.cap( 1 );

                    reg_live_endtime.indexIn( xml );
                    live.live_endtime = reg_live_endtime.cap( 1 );

                    reg_live_watchco.indexIn( xml );
                    live.live_watchcount = reg_live_watchco.cap( 1 );

                    reg_live_commentco.indexIn( xml );
                    live.live_commentcount = reg_live_commentco.cap( 1 );

                    reg_live_comthumburl.indexIn( xml );
                    live.live_cothumb = reg_live_comthumburl.cap( 1 );

                    reg_server_addr.indexIn( xml );
                    live.server_addr = reg_server_addr.cap( 1 );

                    reg_server_port.indexIn( xml );
                    live.server_port = reg_server_port.cap( 1 );

                    reg_server_thread.indexIn( xml );
                    live.server_thread = reg_server_thread.cap( 1 );
                }
                pos += reg_live.matchedLength();
                livedata.append( live );
            }
            mPlayer->SetLiveData( livedata );
        } else {
        }
        emit mPlayer->uiUpdate();
        QThread::sleep( 60 );
    }
}
