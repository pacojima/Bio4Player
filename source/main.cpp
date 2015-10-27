#include "b4p_playermanager.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    PlayerManager *mPlayer = new PlayerManager();

    mPlayer->Initialize();

    return a.exec();
}
