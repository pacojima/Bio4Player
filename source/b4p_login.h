#ifndef LOGIN_H
#define LOGIN_H

#include <QObject>

class PlayerManager;

class Login : public QObject
{
    Q_OBJECT
public:
    explicit Login(PlayerManager *mPlayer, QObject *parent = 0);
    QString TryLogin( const QString username, const QString password );
    bool CheckLogin();
    void SaveSession( const QString username, const QString password );
    QVariant EncodeSession( const QString nicookie );
    QString GetSession();
private:
    PlayerManager *mPlayer;
signals:

public slots:
};

#endif // LOGIN_H
