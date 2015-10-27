#ifndef B4P_VIEWPANEL_H
#define B4P_VIEWPANEL_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkCookie>
#include <QNetworkCookieJar>

class PlayerManager;

namespace Ui {
class ViewPanel;
}

class ViewPanel : public QWidget
{
    Q_OBJECT

public:
    explicit ViewPanel(PlayerManager *mPlayer, QWidget *parent = 0);
    ~ViewPanel();
    void SetLiveData( const QString live_id, const QString live_thumb, const QString live_title );
    void Initialze();
private:
    Ui::ViewPanel *ui;
    PlayerManager *mPlayer;
    QNetworkCookie cookie;
    QList< QNetworkCookie > cookies;
    QNetworkCookieJar *jar;
    QNetworkAccessManager *nam;
};

#endif // B4P_VIEWPANEL_H
