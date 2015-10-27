#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include <QObject>
#include <QList>
#include <QThread>
#include "../userinterface/b4p_mainwindow.h"
#include "../userinterface/b4p_loginwindow.h"
#include "b4p_login.h"
#include "b4p_heartbeat.h"
#include "b4p_livesearcher.h"

struct _LIVEDATA{
    QString live_id;
    QString live_title;
    QString live_description;
    QString live_coid;
    QString live_cothumb;
    QString live_ownername;
    QString live_basetime;
    QString live_opentime;
    QString live_starttime;
    QString live_endtime;
    QString live_watchcount;
    QString live_commentcount;
    QString server_addr;
    QString server_port;
    QString server_thread;
};

class PlayerManager : public QObject
{
    Q_OBJECT
public:
    explicit PlayerManager(QObject *parent = 0);
    void Initialize();
    void TryLogin( const QString username, const QString password );
    QList<_LIVEDATA> *GetLiveData();
    void SetLiveData(const QList<_LIVEDATA> livedata);
    void ClearLiveData();
    QString GetStrNicookie();
    QVariant GetVarNicookie();
    void SetNicookie( const QString nicookie );
    LiveSearcher *GetLiveSearcher();
    void StartUpdate();
    void ShowPlayer( const QString live_id );
    QString GetCurrentLiveID();
private:
    MainWindow *mwin;
    LoginWindow *lwin;
    Login *lmng;
    Heartbeat *hmng;
    LiveSearcher *livemng;
    QString nicookie;
    QVariant varnicookie;
    QList<_LIVEDATA> livedata;
    QThread *search_thread;
    QThread *heartbeat_thread;
    QString current_live_id;
signals:
    void uiUpdate();
public slots:
    void Update();
};

#endif // PLAYERMANAGER_H
