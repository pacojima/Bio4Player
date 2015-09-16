#include "b4p_nicookie.h"
#include "../../ui/b4p_settingwindow.h"
#include "../../ui/b4p_mainwindow.h"

Nicookie::Nicookie( MainWindow *mwin, SettingWindow *swin, QObject *parent ) : QObject( parent ),
    nam( nullptr ),
    UserCookie( "EMPTY" )
{
    this->mwin = mwin;
    this->swin = swin;
}

void Nicookie::GetCookieForAccount( const QString mail, const QString password ){

    UserMail = mail;
    UserPassword = password;

    if( nam != nullptr ) delete nam;
    nam = new QNetworkAccessManager( this );

    connect( nam, SIGNAL( finished( QNetworkReply* ) ), this, SLOT( CookieGot( QNetworkReply* ) ) );

    QNetworkRequest rq( QUrl( "https://secure.nicovideo.jp/secure/login?site=nicolive" ) );
    rq.setHeader( QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded" );

    QUrlQuery params;
    params.addQueryItem( "next_url", "" );
    params.addQueryItem( "show_button_facebook", "0" );
    params.addQueryItem( "show_button_twitter", "0" );
    params.addQueryItem( "nolinks", "0" );
    params.addQueryItem( "_use_valid_error_code", "0" );
    params.addQueryItem( "mail", QUrl::toPercentEncoding( UserMail ) );
    params.addQueryItem( "password", QUrl::toPercentEncoding( UserPassword ) );

    nam->post( rq, params.toString( QUrl::FullyEncoded ).toUtf8() );

}

QString Nicookie::GetCookie(){
    return UserCookie;
}

QVariant Nicookie::EncodeByteCookie(){
    QVariant postData;

    QList < QNetworkCookie > cookies;
    QNetworkCookie ck;
    ck.toRawForm( QNetworkCookie::NameAndValueOnly );
    ck.setName( "user_session" );

    QByteArray user_id_ba;
    user_id_ba.append( UserCookie );

    ck.setValue( user_id_ba );
    cookies.append( ck );

    postData.setValue( cookies );
    return postData;
}

QString Nicookie::GetCookieForBrowser(){

}

void Nicookie::CookieGot( QNetworkReply *reply ){
    auto headers = reply->rawHeaderPairs();
    foreach( auto header, headers ){
        if( header.first == "Set-Cookie" ) {
            auto cookies = QNetworkCookie::parseCookies( header.second );
            foreach( auto cookie, cookies ){
                if( cookie.name() == "user_session" && cookie.value() != "deleted" && cookie.value() != "" ){
                    UserCookie = cookie.value();
                    break;
                }
            }
            break;
        }
    }

    if( UserCookie != QString( "EMPTY" ) ){
        QMessageBox::information( swin, "Bio4Player", QStringLiteral( "ログインしました" ) );
        mwin->ChangeStatusBar( "ログインしました。" );
    } else {
        QMessageBox::information( swin, "Bio4Player", QStringLiteral( "ログインに失敗しました\nメールアドレスとパスワードを確認してください" ) );
        mwin->ChangeStatusBar( "ログインされていません。" );
        UserCookie = "EMPTY";
    }

    reply->deleteLater();
}

Nicookie::~Nicookie(){
}
