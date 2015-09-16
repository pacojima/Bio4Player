#include "b4p_livewindow.h"
#include "ui_b4p_livewindow.h"
#include "b4p_mainwindow.h"

LiveWindow::LiveWindow( const QString cookie, MainWindow *mwin, QWidget *parent ) :
    QMainWindow(parent),
    ui(new Ui::LiveWindow)
{
    ui->setupUi(this);
    this->mwin = mwin;
    QByteArray cookievalue;
    cookievalue.append( cookie );
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

void LiveWindow::ConnectShow(const QString live_id ){
    QString URL_NICOLIVEPLAYER = "http://live.nicovideo.jp/nicoliveplayer.swf?v=";
    URL_NICOLIVEPLAYER.append( live_id );
    ui->webView->load( QUrl( URL_NICOLIVEPLAYER ) );
    this->show();
}

LiveWindow::~LiveWindow()
{
    delete ui;
}

void LiveWindow::closeEvent(QCloseEvent *event){
    ui->webView->load( QUrl( "" ) );
}

