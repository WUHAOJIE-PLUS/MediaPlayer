#ifndef CCOMBINATIONPLAY_H
#define CCOMBINATIONPLAY_H

#include <QWidget>
#include "cbottomctrlbar.h"
#include "cpositionsliderdialog.h"

class CcombinationPlay : public QWidget
{
    Q_OBJECT
public:
    explicit CcombinationPlay(QWidget *parent = nullptr);

    void showTimeLabel(bool isShow);
    void setCurPlayTime(const qint64& curMs);
    void setTotalTime(const qint64& totalMs);

    void setVolume_Value(int value);

    void setStart_bnt(){
        _pcbottom->setStart_bnt();
    }
    void setPause_bnt(){
        _pcbottom->setPause_bnt();
    }


    bool IsSliderDown();
    int value();
    void setSliderValue(int value);

    void setSlideHide();
    void setSlideShow();

private:
    void initUI();

signals:
    void sig_play();//与播放connect
    void sig_stop();//与停止connect
    void sig_pre();
    void sig_next();

    void sig_fullScreen();

    void sig_volume(int);

    void sig_pslider(int);
    void open_file();
private:
    CPositionSliderDialog *_pposslide;
    CBottomCtrlBar *_pcbottom;
};

#endif // CCOMBINATIONPLAY_H
