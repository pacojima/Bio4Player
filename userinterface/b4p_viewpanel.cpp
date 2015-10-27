#include "b4p_viewpanel.h"
#include "ui_b4p_viewpanel.h"

#include "../source/b4p_playermanager.h"


ViewPanel::ViewPanel(PlayerManager *mPlayer,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ViewPanel)
{
    ui->setupUi(this);
    this->mPlayer = mPlayer;


    ui->webView->setZoomFactor( 1 );
    ui->webView->load( QUrl( "" ) );
}

void ViewPanel::Initialze(){
    QByteArray cookievalue;
    cookievalue.append( mPlayer->GetStrNicookie() );
    ui->webView->settings()->setAttribute( QWebSettings::PluginsEnabled, true );
    ui->webView->settings()->setAttribute( QWebSettings::JavascriptEnabled, true );
    this->cookie.setName( "user_session" );
    this->cookie.setDomain( ".nicovideo.jp" );
    this->cookie.setValue( cookievalue );
    this->cookie.setPath( "/" );
    cookies.append( this->cookie );
    nam = new QNetworkAccessManager( this );
    jar = new QNetworkCookieJar( this );
    jar->setCookiesFromUrl( cookies, QUrl( "http://live.nicovideo.jp/nicoliveplayer.swf" ) );
    nam->setCookieJar( jar );
    ui->webView->page()->setNetworkAccessManager( nam );
}

void ViewPanel::SetLiveData(const QString live_id, const QString live_thumb, const QString live_title)
{
    ui->Thumb->load( QUrl( live_thumb ) );
    ui->label_title->setText( live_title );
    QString URL = "http://live.nicovideo.jp/nicoliveplayer.swf?v=";
    URL.append( live_id );
    ui->webView->load( QUrl( URL ) );
}

ViewPanel::~ViewPanel()
{
    delete ui;
}
