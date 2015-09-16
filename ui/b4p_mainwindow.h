#ifndef B4P_MAINWINDOW_H
#define B4P_MAINWINDOW_H

#include <QMainWindow>
#include "b4p_settingwindow.h"
#include "b4p_bio4listitem.h"
#include "b4p_livewindow.h"
#include "../src/Bio4PlayerLib/b4p_playermanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow( QWidget *parent = 0 );
    ~MainWindow();
    PlayerManager *player_manager;
    void ChangeStatusBar( const QString status );
    void AppendListItem( Bio4ListItem *item );
    void ClearListItem();
    void CreateLiveWindow( const QString cookie );
    LiveWindow *lwin;
private slots:
    void on_actionSettings_triggered();

    void on_actionWhatIsBio4Player_triggered();

    void on_buttonReflesh_clicked();

private:
    Ui::MainWindow *ui;
    SettingWindow *swin;

};

#endif // B4P_MAINWINDOW_H
