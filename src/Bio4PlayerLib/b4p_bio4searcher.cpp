#include "b4p_bio4searcher.h"
#include "../../ui/b4p_mainwindow.h"
#include <QMessageBox>

Bio4Searcher::Bio4Searcher( MainWindow *mwin, QObject *parent) : QObject(parent),
    nam( nullptr )
{
    this->mwin = mwin;
    live_ids.clear();
    live_datas.clear();
}

void Bio4Searcher::GetLiveID( const QString nicookie ){
    if( nam != nullptr ) delete nam;
    nam = new QNetworkAccessManager( this );
    connect( nam, SIGNAL( finished( QNetworkReply* ) ), this, SLOT( GotLiveID( QNetworkReply* ) ) );
    QUrlQuery params;
    //QNetworkRequest rq( QUrl( "http://localhost/Bio4PlayerAPI/getbio4lives.php" ) );
    QNetworkRequest rq( QUrl( "http://pacojima.thick.jp/bio4playerapi/getbio4lives.php" ) );
    rq.setHeader( QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded" );
    params.addQueryItem( "user_nicookie", QUrl::toPercentEncoding( nicookie ) );

    nam->post( rq, params.toString( QUrl::FullyEncoded ).toUtf8() );
}

void Bio4Searcher::GetLiveData(){

    if( nam != nullptr ) delete nam;
    nam = new QNetworkAccessManager( this );
    for( auto itr = live_ids.begin(); itr != live_ids.end(); ++itr ){
        connect( nam, SIGNAL( finished( QNetworkReply* ) ), this, SLOT( GotLiveData( QNetworkReply* ) ) );
        QString URL_GETLIVEINFOSTATUS = "http://watch.live.nicovideo.jp/api/getplayerstatus?v=";
        URL_GETLIVEINFOSTATUS.append( *itr );
        QNetworkRequest *rq = new QNetworkRequest( QUrl( URL_GETLIVEINFOSTATUS ) );
        rq->setHeader(  QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded" );
        rq->setHeader( QNetworkRequest::CookieHeader, mwin->player_manager->nicookie->EncodeByteCookie() );
        nam->get( *rq );
    }
}

void Bio4Searcher::GotLiveData( QNetworkReply *reply ){
    reply->deleteLater();
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
    QRegExp reg_live_comthumburl( "<thumb_url>(.+)</thumb_url>" );
    QRegExp reg_server_addr( "<addr>(.+)</addr>" );
    QRegExp reg_server_port( "<port>([0-9]+)</port>" );
    QRegExp reg_server_thread( "<thread>([0-9]+)</thread>" );
    reg_status.indexIn( xml );

    if( reg_status.cap( 1 ) == "ok" ){
        LiveData live_data;

        reg_live_id.indexIn( xml );
        live_data.SetLiveID( reg_live_id.cap( 1 ) );

        reg_live_title.indexIn( xml );
        live_data.SetLiveTitle( reg_live_title.cap( 1 ) );

        reg_live_description.indexIn( xml );
        live_data.SetLiveDescription( reg_live_description.cap( 1 ) );

        reg_live_comunity.indexIn( xml );
        live_data.SetLiveComunity( reg_live_comunity.cap( 1 ) );

        reg_live_owner.indexIn( xml );
        live_data.SetLiveOwner( reg_live_owner.cap( 1 ) );

        reg_live_basetime.indexIn( xml );
        live_data.SetLiveBaseTime( reg_live_basetime.cap( 1 ) );

        reg_live_opentime.indexIn( xml );
        live_data.SetLiveOpenTime( reg_live_opentime.cap( 1 ) );

        reg_live_starttime.indexIn( xml );
        live_data.SetLiveStartTime( reg_live_starttime.cap( 1 ) );

        reg_live_endtime.indexIn( xml );
        live_data.SetLiveEndTime( reg_live_endtime.cap( 1 ) );

        reg_live_watchco.indexIn( xml );
        live_data.SetLiveWatchCount( reg_live_watchco.cap( 1 ) );

        reg_live_commentco.indexIn( xml );
        live_data.SetLiveCommentCount( reg_live_commentco.cap( 1 ) );

        reg_live_comthumburl.indexIn( xml );
        live_data.SetLiveComunityThumburl( reg_live_comthumburl.cap( 1 ) );

        reg_server_addr.indexIn( xml );
        live_data.SetServerAddress( reg_server_addr.cap( 1 ) );

        reg_server_port.indexIn( xml );
        live_data.SetServerPort( reg_server_port.cap( 1 ) );

        reg_server_thread.indexIn( xml );
        live_data.SetServerThread( reg_server_thread.cap( 1 ) );

        mwin->player_manager->AddListItem( live_data );

    }

}

void Bio4Searcher::GotLiveID( QNetworkReply *reply ){
    reply->deleteLater();
    live_ids.clear();
    mwin->ClearListItem();
    QString xml = QString( reply->readAll() );
    QRegExp reg( "<live_id no=\"\\d+\">(lv[0-9]+)</live_id>" );
    QRegExp status( "<getbio4lives status=\"([0-9]+)\"/>" );

    status.indexIn( xml );

    if( status.cap( 1 ) == "0" ){
        int pos = 0;
        while ( ( pos = reg.indexIn( xml, pos ) ) != -1 ){
            live_ids.append( reg.cap( 1 ) );
            pos += reg.matchedLength();
        }
        mwin->ChangeStatusBar( "ライブIDを取得しました" );
        GetLiveData();
    } else {
        mwin->ChangeStatusBar( "ライブが見つかりませんでした" );
    }
}
