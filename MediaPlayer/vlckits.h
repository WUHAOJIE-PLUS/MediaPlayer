#ifndef VLCKITS_H
#define VLCKITS_H

#include <QObject>
#include <vlc/vlc.h>
#include <vector>

using std::vector;

class VLCKits : public QObject
{
    Q_OBJECT
public:
    explicit VLCKits(QObject *parent = nullptr);
    ~VLCKits();

    bool initVLC();
    // bool play(const QString & path, void * hwnd);
    bool play(const QStringList &names, void *hwnd);
    void addMediaIndex();
    int currentIndex() const { return _currentIndex; }
    const vector<libvlc_time_t> & durationArr() const { return _durationArr; }//

    void play();
    void pause();
    void stop();
    void setVolume(int value);
    void setPosition(int value);

    void playNext();
    void playPrevious();

    libvlc_media_player_t * mediaPlayer() const { return _pMediaPlayer;}
    libvlc_media_list_t *mediaList()const{  return _pMediaList; }

    //当需要修改UI界面的显示时，通过信号来触发，以下三个函数调用时就触发信号
    void setTimeSliderPos(int value);
    void setTimeText();
    void setVolumePos(int value);

    libvlc_state_t get_vlcState();
    libvlc_time_t getcurSecs();
    libvlc_time_t get_totalSecs();

    void onItemSelected(int index);

signals://自定义信号
    void sigTimeSliderPos(int value);
    void sigTimeText();
    void sigVolumeSliderPos(int value);

private:
    libvlc_instance_t   *_pInstance = nullptr; //该指针代表了⼀个 VLC 实例
    libvlc_media_t  *_pMedia = nullptr;//该指针代表了指定路径的媒体⽂件,可以看成一个结点，每一个结点代表一个视频
    libvlc_media_player_t   *_pMediaPlayer = nullptr;//该指针代表了⼀个媒体播放器对象
    libvlc_event_manager_t *_pEventManager = nullptr;//该指针代表了媒体播放器的事件管理器。通过这个事件管理器，你可以注册和监听媒体播放器的各种事件，如播放状态变化、时间更新等

    //添加的数据成员
    libvlc_media_list_player_t     * _pMediaListPlayer = nullptr;//该指针代表了⼀个媒体列表播放器对象。通过这个媒体列表播放器对象，你可以管理和播放⼀系列媒体⽂件。
    libvlc_media_list_t    *_pMediaList = nullptr;//该指针代表了⼀个媒体列表对象。通过这个媒体列表对象，你可以添加、删除和管理多个媒体资源。
    vector<libvlc_time_t>  _durationArr; // 存储每个媒体的时长
    int _currentIndex = -1;//表示当前播放的媒体下标

};

#endif // VLCKITS_H
