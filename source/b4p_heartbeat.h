#ifndef HEARTBEAT_H
#define HEARTBEAT_H

#include <QObject>
#include <QNetworkReply>

class PlayerManager;

class Heartbeat : public QObject
{
    Q_OBJECT
public:
    explicit Heartbeat(PlayerManager *mPlayer, QObject *parent = 0);
private:
    PlayerManager *mPlayer;
signals:
    void progress( int );
public slots:
    void RunHeartBeat();
};

#endif // HEARTBEAT_H
