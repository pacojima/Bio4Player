#ifndef B4P_MAINWINDOW_H
#define B4P_MAINWINDOW_H

#include <QMainWindow>
#include <QNetworkReply>
#include <QThread>
#include "b4p_viewpanel.h"

class PlayerManager;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(PlayerManager *mPlayer, QWidget *parent = 0);
    void ShowPlayer( const QString live_id );
    ~MainWindow();
    void InitViewPanel();
private:
    Ui::MainWindow *ui;
    PlayerManager *mPlayer;
    ViewPanel *pview;
signals:
    void UiUpdate();
public slots:
    void Update();
};

#endif // B4P_MAINWINDOW_H
