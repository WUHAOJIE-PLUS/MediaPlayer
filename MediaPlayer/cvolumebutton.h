#ifndef CVOLUMEBUTTON_H
#define CVOLUMEBUTTON_H

#include "CVolumeSliderDialog.h"

#include <QPushButton>
#include <QEvent>
#include <QEnterEvent>
#include <QMouseEvent>


class CVolumeButton : public QPushButton
{
    Q_OBJECT
public:
    explicit CVolumeButton(QWidget *parent = nullptr);
     ~CVolumeButton();

    void hide();

    void setVolume_Value(int value);

signals:
    void sig_volume(int);

protected:
    void paintEvent(QPaintEvent* event) override;
    void enterEvent(QEnterEvent *event) override;
    // void leaveEvent(QEvent *event)override;
    //重写定时器函数
    void timerEvent(QTimerEvent* event) override;
    //音量按钮被按下时，调用mousePressEvent函数
    void mousePressEvent(QMouseEvent* event) override;

private:
    CVolumeSliderDialog * _pvolumeSliderDlg;

    int _timerId = 0;//定时器id
    bool _isRunning = false;//定时器开启的标志位
    bool _isMute = false;//是否静音
    int _volumeValue = 0;//音量值
};

#endif // CVOLUMEBUTTON_H
