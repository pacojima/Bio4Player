#ifndef B4P_BIO4LISTITEM_H
#define B4P_BIO4LISTITEM_H

#include <QWidget>
#include "../src/Bio4PlayerLib/b4p_livedata.h"

class MainWindow;

namespace Ui {
class Bio4ListItem;
}

class Bio4ListItem : public QWidget
{
    Q_OBJECT

public:
    explicit Bio4ListItem( MainWindow *mwin, QWidget *parent = 0);
    ~Bio4ListItem();
    void SetLiveData( const LiveData live_data );

private slots:
    void on_pushButton_clicked();
private:
    Ui::Bio4ListItem *ui;
    MainWindow *mwin;
    LiveData live_data;
};

#endif // B4P_BIO4LISTITEM_H
