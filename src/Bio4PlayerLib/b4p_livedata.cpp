#include "b4p_livedata.h"

LiveData::LiveData(){}

QString LiveData::GetLiveID() const{
    return live_id;
}

QString LiveData::GetLiveTitle() const{
    return live_title;
}

QString LiveData::GetLiveDescription() const{
    return live_description;
}

QString LiveData::GetLiveComunity() const{
    return live_commentco;
}

QString LiveData::GetLiveOwner() const{
    return live_owner;
}

QString LiveData::GetLiveBaseTime() const{
    return live_basetime;
}

QString LiveData::GetLiveOpenTime() const{
    return live_opentime;
}

QString LiveData::GetLiveStartTime() const{
    return live_starttime;
}

QString LiveData::GetLiveEndTime() const{
    return live_endtime;
}

QString LiveData::GetLiveWatchCount() const{
    return live_watchco;
}

QString LiveData::GetLiveCommentCount() const{
    return live_commentco;
}

QString LiveData::GetLiveComunityThumburl() const{
    return live_comthumburl;
}

QString LiveData::GetServerAddress() const{
    return server_addr;
}

QString LiveData::GetServerPort() const{
    return server_port;
}

QString LiveData::GetServerThread() const{
    return server_thread;
}

void LiveData::SetLiveID( const QString str ){
    live_id = str;
}

void LiveData::SetLiveTitle( const QString str ){
    live_title = str;
}

void LiveData::SetLiveDescription( const QString str ){
    live_description = str;
}

void LiveData::SetLiveComunity( const QString str ){
    live_comunity = str;
}

void LiveData::SetLiveOwner( const QString str ){
    live_owner = str;
}

void LiveData::SetLiveBaseTime( const QString str ){
    live_basetime = str;
}

void LiveData::SetLiveOpenTime( const QString str ){
    live_opentime = str;
}

void LiveData::SetLiveStartTime( const QString str ){
    live_starttime = str;
}

void LiveData::SetLiveEndTime( const QString str ){
    live_endtime = str;
}

void LiveData::SetLiveWatchCount( const QString str ){
    live_watchco = str;
}

void LiveData::SetLiveCommentCount( const QString str ){
    live_commentco = str;
}

void LiveData::SetLiveComunityThumburl( const QString str ){
    live_comthumburl = str;
}

void LiveData::SetServerAddress( const QString str ){
    server_addr = str;
}

void LiveData::SetServerPort( const QString str ){
    server_port = str;
}

void LiveData::SetServerThread( const QString str ){
    server_thread = str;
}

LiveData::~LiveData(){}


