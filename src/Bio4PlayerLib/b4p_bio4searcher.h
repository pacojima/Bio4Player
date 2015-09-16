#ifndef BIO4SEARCHER_H
#define BIO4SEARCHER_H

#include <QObject>
#include <QtNetwork>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QXmlStreamReader>
#include <QList>
#include "b4p_livedata.h"

class MainWindow;

class Bio4Searcher : public QObject
{
    Q_OBJECT
public:
    explicit Bio4Searcher( MainWindow *mwin, QObject *parent = 0 );
    void GetLiveID( const QString nicookie );
    void GetLiveData();
    QList< LiveData > live_datas;
private:
    MainWindow *mwin;
    QNetworkAccessManager *nam;
    QList< QString > live_ids;
signals:

public slots:
    void GotLiveID( QNetworkReply *reply );
    void GotLiveData( QNetworkReply *reply );
};

#endif // BIO4SEARCHER_H
