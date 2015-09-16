#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include <QObject>
#include "../../ui/b4p_settingwindow.h"
#include "../../ui/b4p_bio4listitem.h"
#include "../../ui/b4p_livewindow.h"
#include "b4p_setting.h"
#include "b4p_nicookie.h"
#include "b4p_bio4searcher.h"
#include "b4p_livedata.h"

namespace Ui {
class MainWindow;
}

class PlayerManager : public QObject
{
    Q_OBJECT
public:
    explicit PlayerManager( MainWindow *mwin, SettingWindow *swin, LiveWindow *lwin, QObject *parent = 0);
    ~PlayerManager();
    void ShowSettingWindow() const;
    void HideSettingWindow() const;
    void ShowHelpWindow() const;
    void AddListItem( const LiveData live_data );
    Setting *setting;
    Nicookie *nicookie;
    Bio4Searcher *bio4searcher;
    QList< Bio4ListItem* > listwedgets;
private:
    MainWindow *mwin;
    SettingWindow *swin;
    LiveWindow *lwin;
signals:

public slots:
};

#endif // PLAYERMANAGER_H
