#ifndef B4P_LIVEITEM_H
#define B4P_LIVEITEM_H

#include <QWidget>

class PlayerManager;

namespace Ui {
class LiveItem;
}

class LiveItem : public QWidget
{
    Q_OBJECT

public:
    explicit LiveItem(PlayerManager *mPlayer, QWidget *parent = 0);
    ~LiveItem();
    void SetLiveData( const QString thumb, const QString ownername, const QString live_id );
    void mousePressEvent( QMouseEvent *e );
private:
    Ui::LiveItem *ui;
    PlayerManager *mPlayer;
    QString live_id;
};

#endif // B4P_LIVEITEM_H
