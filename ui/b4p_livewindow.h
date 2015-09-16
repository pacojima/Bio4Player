#ifndef B4P_LIVEWINDOW_H
#define B4P_LIVEWINDOW_H

#include <QMainWindow>
#include <QNetworkAccessManager>
#include <QNetworkCookie>
#include <QNetworkCookieJar>

class MainWindow;

namespace Ui {
class LiveWindow;
}

class LiveWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit LiveWindow( const QString cookie, MainWindow *mwin, QWidget *parent = 0);
    ~LiveWindow();
    void ConnectShow( const QString live_id );
private slots:

private:
    Ui::LiveWindow *ui;
    MainWindow *mwin;
    QNetworkAccessManager *nam;
    QNetworkCookie cookie;
    QList< QNetworkCookie > cookies;
    QNetworkCookieJar *jar;
protected:
    void closeEvent( QCloseEvent *event );
};

#endif // B4P_LIVEWINDOW_H
