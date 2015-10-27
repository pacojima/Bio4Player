#ifndef LIVESEARCHER_H
#define LIVESEARCHER_H

#include <QObject>

class PlayerManager;

class LiveSearcher : public QObject
{
    Q_OBJECT
public:
    explicit LiveSearcher(PlayerManager *mPlayer, QObject *parent = 0);
private:
    PlayerManager *mPlayer;
signals:
    void progress(int);
public slots:
    void Search();
};

#endif // LIVESEARCHER_H
