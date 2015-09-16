#ifndef NICOOKIE_H
#define NICOOKIE_H

#include <QObject>
#include <QString>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QMessageBox>

class MainWindow;
class SettingWindow;

class Nicookie : QObject
{
    Q_OBJECT
public:
    explicit Nicookie( MainWindow *mwin, SettingWindow *swin, QObject *parent = 0 );
    ~Nicookie();
    void GetCookieForAccount( const QString mail, const QString password );
    QString GetCookieForBrowser();
    QVariant EncodeByteCookie();
    QString GetCookie();

private:
    QString UserMail;
    QString UserPassword;
    QString UserCookie;
    QNetworkAccessManager *nam;
    MainWindow *mwin;
    SettingWindow *swin;
signals:
private slots:
    void CookieGot( QNetworkReply *reply );
public slots:
};

#endif // NICOOKIE_H
