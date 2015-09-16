#ifndef LIVEDATA_H
#define LIVEDATA_H

#include <QString>

class LiveData
{
public:
    LiveData();
    ~LiveData();
    QString GetLiveID() const;
    QString GetLiveTitle() const;
    QString GetLiveDescription() const;
    QString GetLiveComunity() const;
    QString GetLiveOwner() const;
    QString GetLiveBaseTime() const;
    QString GetLiveOpenTime() const;
    QString GetLiveStartTime() const;
    QString GetLiveEndTime() const;
    QString GetLiveWatchCount() const;
    QString GetLiveCommentCount() const;
    QString GetLiveComunityThumburl() const;
    QString GetServerAddress() const;
    QString GetServerPort() const;
    QString GetServerThread() const;
    void SetLiveID( const QString str );
    void SetLiveTitle( const QString str );
    void SetLiveDescription( const QString str );
    void SetLiveComunity( const QString str );
    void SetLiveOwner( const QString str );
    void SetLiveBaseTime( const QString str );
    void SetLiveOpenTime( const QString str );
    void SetLiveStartTime( const QString str );
    void SetLiveEndTime( const QString str );
    void SetLiveWatchCount( const QString str );
    void SetLiveCommentCount( const QString str );
    void SetLiveComunityThumburl( const QString str );
    void SetServerAddress( const QString str );
    void SetServerPort( const QString str );
    void SetServerThread( const QString str );
private:
    QString live_id;
    QString live_title;
    QString live_description;
    QString live_comunity;
    QString live_owner;
    QString live_basetime;
    QString live_opentime;
    QString live_starttime;
    QString live_endtime;
    QString live_watchco;
    QString live_commentco;
    QString live_comthumburl;
    QString server_addr;
    QString server_port;
    QString server_thread;
};

#endif // LIVEDATA_H
