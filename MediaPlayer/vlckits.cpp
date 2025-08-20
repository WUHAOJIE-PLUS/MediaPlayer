#include "vlckits.h"
#include <QDebug>
#include <QDir>

VLCKits::VLCKits(QObject *parent)
    : QObject{parent}
    ,_durationArr()
{
    _durationArr.reserve(10);
}

VLCKits::~VLCKits()
{
    stop(); // 先停止播放

    if (_pMediaListPlayer) {
        libvlc_media_list_player_release(_pMediaListPlayer);
        _pMediaListPlayer = nullptr;
    }
    if (_pMediaList) {
        libvlc_media_list_release(_pMediaList);
        _pMediaList = nullptr;
    }

    if (_pMediaPlayer) {
        libvlc_media_player_release(_pMediaPlayer);
        _pMediaPlayer = nullptr;
    }

    if (_pInstance) {
        libvlc_release(_pInstance);
        _pInstance = nullptr;
    }
}

/*
这段代码的作用是：
计算当前播放进度百分比，并发送给进度条
将当前播放时间和总时长格式化为HH:MM:SS/HH:MM:SS的字符串（如00:01:23/00:05:00）
将格式化后的时间字符串发送给UI显示
*/
static void processPosition(VLCKits * pkits){

    // //百分比
    float pos = libvlc_media_player_get_position(pkits->mediaPlayer());
    pkits->setTimeSliderPos(pos *100);//信号


    //更新时间标签
    pkits->setTimeText();

}

//设置声音的默认值时使用，如果没这个函数，则声音正常，但滑动条不正常
static void processVolume(VLCKits * pkits)
{

    int val = libvlc_audio_get_volume(pkits->mediaPlayer());
    if(val == -1) {
        return;
    }
    pkits->setVolumePos(val);//信号
}

//当播放的媒体变化时，为这个_pMedia更新当前播放的媒体下标_currentIndex
static void processMediaChanged(VLCKits * pkits){
    pkits->addMediaIndex();//更新_pMedia对应的_currentIndex
}

static void vlc_callback(const struct libvlc_event_t *p_event, void *p_data)
{
    VLCKits * pkits = static_cast<VLCKits*>(p_data);
    if(pkits) {
        switch(p_event->type) {
        case libvlc_MediaPlayerPositionChanged://播放位置变化时
            processPosition(pkits);
            break;
        case libvlc_MediaPlayerAudioVolume://音量变化时
            processVolume(pkits);
            break;
        case libvlc_MediaPlayerMediaChanged://播放的媒体变化时
            processMediaChanged(pkits);
            break;
        }
    }
}

bool VLCKits::initVLC(){//1


    if(mediaPlayer()){//停止播放之前的视频
        stop();
    }

    _pInstance = libvlc_new(0, nullptr);
    if(_pInstance) {//libvlc_new成功
        qDebug() << "libvlc_new成功 ";
        _pMediaPlayer = libvlc_media_player_new(_pInstance);
        if(_pMediaPlayer) {//_pMediaPlayer成功
            qDebug() << "pMediaPlayer成功 ";
            _pEventManager = libvlc_media_player_event_manager(_pMediaPlayer);//---类似connect--中断
            if(_pEventManager) {// 获取事件管理器成功
                qDebug() << "获取事件管理器成功 ";
                //注册媒体播放器的事件处理器
                //1. 位置发生改变时
                libvlc_event_attach(_pEventManager, libvlc_MediaPlayerPositionChanged,vlc_callback, this);
                //2. 声音变化时
                libvlc_event_attach(_pEventManager, libvlc_MediaPlayerAudioVolume,vlc_callback, this);
                //3.媒体变化时
                libvlc_event_attach(_pEventManager, libvlc_MediaPlayerMediaChanged,vlc_callback, this);
                return true;
            } else { //获取事件管理器失败
                libvlc_media_player_release(_pMediaPlayer);
                libvlc_release(_pInstance);
                qDebug() << "获取事件管理器失败 ";
                return false;
            }
        } else {//_pMediaPlayer失败
            libvlc_release(_pInstance);
            qDebug() << "_pMediaPlayer失败 ";
            return false;
        }
    }else {//libvlc_new失败
        qDebug() << "libvlc_new失败 ";
        return false;
    }
}


//一次选一个或多个视频
//当第一次选择一个，第二次再选的，和第一次选择的没有关系
bool VLCKits::play(const QStringList &names, void *hwnd) {//2

    {//风格：多次选择的不在同一个_pMediaList
        //初始化_durationArr和_currentIndex，避免多次选择后与之前选择的冲突
        if(!_durationArr.empty()){
            _durationArr.clear();
            _currentIndex = -1;
        }
    }

    // 释放之前的媒体资源
    if (_pMediaList) {
        libvlc_media_list_release(_pMediaList);
        _pMediaList = nullptr;
    }

    if (_pMediaListPlayer) {
        libvlc_media_list_player_release(_pMediaListPlayer);
        _pMediaListPlayer = nullptr;
    }

    //设置列表播放器
    _pMediaListPlayer = libvlc_media_list_player_new(_pInstance);
    if(!_pMediaListPlayer) {
        return false;
    }

    _pMediaList = libvlc_media_list_new(_pInstance);
    if(!_pMediaList) {
        return false;
    }

    //将每一个视频都放到_pMediaList
    qDebug() << "names.size() : " << names.size();
    for(int i = 0; i < names.size(); ++i) {
        QString filename = names[i];
        filename = QDir::toNativeSeparators(filename);
        _pMedia = libvlc_media_new_path(_pInstance, filename.toStdString().c_str());//每一个结点代表一个视频
        if(!_pMedia) {
            return false;
        }
        //将媒体添加到播放列表中
        libvlc_media_list_add_media(_pMediaList, _pMedia);//_pMedia添加到_pMediaList中
        //解析媒体元数据
        libvlc_media_parse(_pMedia);
        libvlc_time_t durationSecs = libvlc_media_get_duration(_pMedia) / 1000;//一个视频的总时间
        _durationArr.push_back(durationSecs);
        //当_pMedia添加到_pMediaList后，就不需要_pMedia了
        libvlc_media_release(_pMedia);
    }
    for(auto &elem:_durationArr)
    {
        qDebug() << "durationSecs: " << elem;
    }
    //列表播放器关联媒体列表
    libvlc_media_list_player_set_media_list(_pMediaListPlayer, _pMediaList);
    //设置播放模式：列表循环播放
    libvlc_media_list_player_set_playback_mode(_pMediaListPlayer, libvlc_playback_mode_loop);//循环播放模式，播放完列表中的所有媒体后，会从头开始重新播放
    //媒体列表播放器关联媒体播放器(必须加)
    libvlc_media_list_player_set_media_player(_pMediaListPlayer, _pMediaPlayer);
    libvlc_media_player_set_nsobject(_pMediaPlayer, hwnd);//设置播放窗口

    setVolume(50);// 设置默认音量为50%

    libvlc_media_list_player_play(_pMediaListPlayer);//开始播放
    return true;
}

//更新_pMedia对应的_currentIndex
void VLCKits::addMediaIndex()
{
    ++_currentIndex;
    _currentIndex %= _durationArr.size();
    qDebug() << "_currentIndex: " << _currentIndex
             <<"_durationArr: " << _durationArr.size();

/* 刚开始选择视频时，_currentIndex从0开始，每当播放的媒体变化时，
 * 都会触发一个这个函数，目的是为了更新每个_pMedia所对应的_currentIndex，
 * 而原理是：_durationArr（里面的每个_pMedia对应的时间是在选择文件后就确定的），
 * 每个数组元素下标都跟每个_pMedia的_currentIndex一一对应
>>>>> processMediaChanged()
_currentIndex:  0 _durationArr:  2
*/

}

libvlc_state_t VLCKits::get_vlcState(){

    return libvlc_media_player_get_state(_pMediaPlayer);
}

libvlc_time_t VLCKits::getcurSecs()
{
   return libvlc_media_player_get_time(mediaPlayer());//现在运行到多少ms
}

libvlc_time_t VLCKits::get_totalSecs()
{
   return durationArr()[currentIndex()] * 1000;//视频一共多少ms
}


/*
volume：要设置的音量级别，范围通常是从0（静音）到100（最大音量）
*/
void VLCKits::setVolume(int value){

    //防止打开视频前，点击按钮，导致异常退出
    if(!_pMediaPlayer){
        return;
    }
    qDebug() << "VLCKits::setVolume:";

    libvlc_audio_set_volume(_pMediaPlayer, value);
}

/*
position: 要设置的播放位置，范围在 0.0 到 1.0 之间（浮点数），其中：
0.0 表示媒体的开始位置。
1.0 表示媒体的结束位置。
*/
void VLCKits::setPosition(int value){


    //防止打开视频前，点击按钮，导致异常退出
    if(!_pMediaPlayer){
        return;
    }

    libvlc_media_player_set_position(_pMediaPlayer, value / 100.0);
}



//当需要修改UI界面的显示时，通过信号来触发，以下三个函数调用时就触发信号
void VLCKits::setTimeSliderPos(int value){
    //发送信号
    emit sigTimeSliderPos(value);
}

void VLCKits::setTimeText(){
    //发送信号
    emit sigTimeText();
}

void VLCKits::setVolumePos(int value){
    emit sigVolumeSliderPos(value);
}

void VLCKits::play() {
    if (_pMediaListPlayer) {
        qDebug() << "VLCKits::play()";
        libvlc_media_list_player_play(_pMediaListPlayer);
    }
}

void VLCKits::pause() {
    if (_pMediaListPlayer) {
        libvlc_media_list_player_pause(_pMediaListPlayer);
    }
}

void VLCKits::stop() {
    if (_pMediaListPlayer) {
        // 1. 先停止播放
        libvlc_media_list_player_stop(_pMediaListPlayer);

        // 2. 释放播放器（如果存在）
        if (_pMediaPlayer) {
            libvlc_media_player_release(_pMediaPlayer);
            _pMediaPlayer = nullptr;
        }

        // 3. 释放播放列表播放器
        libvlc_media_list_player_release(_pMediaListPlayer);
        _pMediaListPlayer = nullptr;

        // 4. 发送位置更新信号
        emit sigTimeSliderPos(0);
    }
}


void VLCKits::onItemSelected(int index) {

     if(_pMediaListPlayer){
    libvlc_media_list_player_play_item_at_index(_pMediaListPlayer, index);
     _currentIndex = index;
     }
}

void VLCKits::playNext()
{
    qDebug() << "void VLCKits::playNext()";
    if(_pMediaListPlayer){
        // 计算新索引（支持循环）
        int newIndex = (_currentIndex + 1) % durationArr().size();
        libvlc_media_list_player_play_item_at_index(_pMediaListPlayer,newIndex);

        // 更新当前索引
        _currentIndex = newIndex;
    }
}

void VLCKits::playPrevious()
{
    qDebug() << "void VLCKits::playPrevious()";
    if(_pMediaListPlayer){
        // 计算新索引（支持循环）
        int newIndex = (_currentIndex - 1 + durationArr().size()) % durationArr().size();
        libvlc_media_list_player_play_item_at_index(_pMediaListPlayer, newIndex);

        // 更新当前索引
        _currentIndex = newIndex;
    }
}
