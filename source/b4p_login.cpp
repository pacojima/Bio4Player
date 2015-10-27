#include "b4p_login.h"
#include <QSettings>
#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkCookie>
#include <QUrlQuery>
#include "b4p_playermanager.h"

Login::Login(PlayerManager *mPlayer, QObject *parent) : QObject(parent)
{
    this->mPlayer = mPlayer;
}

bool Login::CheckLogin()
{

    QSettings settings( "nicoookie.ini", QSettings::IniFormat );
    settings.beginGroup( "Session" );
    QString username = settings.value( "username" ).toString();
    QString password = settings.value( "password" ).toString();
    settings.endGroup();

    QString nicookie = TryLogin( username, password );

    QNetworkAccessManager *nam = new QNetworkAccessManager( this );
    QEventLoop eventloop;
    connect( nam, SIGNAL( finished( QNetworkReply* ) ), &eventloop, SLOT( quit() ) );
    QString URL_HEARTBEAT = "http://live.nicovideo.jp/api/heartbeat";
    QNetworkRequest *rq = new QNetworkRequest( QUrl( URL_HEARTBEAT ) );
    rq->setHeader(  QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded" );
    rq->setHeader( QNetworkRequest::CookieHeader, EncodeSession( nicookie ) );
    QNetworkReply *reply = nam->get( *rq );
    eventloop.exec();
    QString xml = reply->readAll();
    QRegExp reg_heartbeat( "<code>(.+)</code>" );
    reg_heartbeat.indexIn( xml );
    if( reg_heartbeat.cap( 1 ) == "UNKNOWN" ){
        mPlayer->SetNicookie( nicookie );
        return true;
    } else {
        return false;
    }
}

void Login::SaveSession( const QString username, const QString password )
{
    QSettings settings( "nicoookie.ini", QSettings::IniFormat );
    settings.clear();
    settings.beginGroup( "Session" );
    settings.setValue( "username", username );
    settings.setValue( "password", password );
    settings.endGroup();
}

QString Login::TryLogin(const QString username, const QString password)
{
    QString nicookie = "EMPTY";
    QNetworkAccessManager *nam = new QNetworkAccessManager( this );

    QEventLoop eventloop;

    connect( nam, SIGNAL( finished( QNetworkReply* ) ), &eventloop, SLOT( quit() ) );

    QNetworkRequest rq( QUrl( "https://secure.nicovideo.jp/secure/login?site=nicolive" ) );
    rq.setHeader( QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded" );
    QUrlQuery params;
    params.addQueryItem( "next_url", "" );
    params.addQueryItem( "show_button_facebook", "0" );
    params.addQueryItem( "show_button_twitter", "0" );
    params.addQueryItem( "nolinks", "0" );
    params.addQueryItem( "_use_valid_error_code", "0" );
    params.addQueryItem( "mail", QUrl::toPercentEncoding( username ) );
    params.addQueryItem( "password", QUrl::toPercentEncoding( password ) );

    QNetworkReply *reply = nam->post( rq, params.toString( QUrl::FullyEncoded ).toUtf8() );
    eventloop.exec();
    auto headers = reply->rawHeaderPairs();
    foreach( auto header, headers ){
        if( header.first == "Set-Cookie" ) {
            auto cookies = QNetworkCookie::parseCookies( header.second );
            foreach( auto cookie, cookies ){
                if( cookie.name() == "user_session" && cookie.value() != "deleted" && cookie.value() != "" ){
                    nicookie = cookie.value();
                    break;
                }
            }
            break;
        }
    }
    if( nicookie != QString( "EMPTY" ) ){
        SaveSession( username, password );
        return nicookie;
    } else {
        return "";
    }
}

QVariant Login::EncodeSession(const QString nicookie)
{
    QVariant postData;

    QList < QNetworkCookie > cookies;
    QNetworkCookie ck;
    ck.toRawForm( QNetworkCookie::NameAndValueOnly );
    ck.setName( "user_session" );

    QByteArray user_id_ba;
    user_id_ba.append( nicookie );

    ck.setValue( user_id_ba );
    cookies.append( ck );

    postData.setValue( cookies );
    return postData;
}

