#ifndef CMAINWINDOW_H
#define CMAINWINDOW_H

#include "framelesswidget.h"
#include "ctitlebar.h"
#include "buttonmenu.h"
#include "vlckits.h"
#include "playlistdialog.h"
#include "videowidget.h"
#include "ccombinationplay.h"
#include <QLabel>

class CMainWindow : public FramelessWidget
{
    Q_OBJECT
public:
    explicit CMainWindow(QWidget * parent= nullptr);

private slots:
    void closeSlot();//与子对象CTitleBar::sigClose信号绑定
    void isFullScreenSlot();//是否全屏
    void Start_Pause();
    void Stop();
    void Openfile();
    void PlayPre();
    void PlayNext();
    void setVolume(int value);
    void seekPosition(int value);
    //更新进度条的位置
    void updatePosition(int value);
    //更新时间的位置
    void updateTimeText();
    //更新时间的位置
    void updateVolume(int value);

    void onShowPlaylist();
    void onItemSelected(int index);
    void showcombination();
    void hidecombination();

protected:
    void mouseDoubleClickEvent(QMouseEvent *event)override;
    void keyPressEvent(QKeyEvent *event)override;
    void resizeEvent(QResizeEvent* event)override;
private:
    void initUI();
    void Connect();

private:
    VLCKits *vlckits;
    CTitleBar * _ptitleBar;//主窗口中包含标题栏
    VideoWidget * wbody;//视频窗口
    QPushButton *Show_Playlist_btn;//显示播放列表按钮
    ButtonMenu *_buttonmenu;//按钮菜单
    QLabel *_imageLabel;//中心图片
    CcombinationPlay *_pbottom_play;

    PlaylistDialog *medialist_dialog = nullptr;//媒体列表
};

#endif // CMAINWINDOW_H
