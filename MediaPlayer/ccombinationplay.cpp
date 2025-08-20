#include "ccombinationplay.h"
#include <QDebug>
#include <QVBoxLayout>

CcombinationPlay::CcombinationPlay(QWidget *parent)
    : QWidget{parent}
    ,_pposslide(new CPositionSliderDialog(this))
    ,_pcbottom(new CBottomCtrlBar(this))
{

    initUI();
}


void CcombinationPlay::initUI()
{


    setFixedHeight(100);
    setStyleSheet("background-color:rgb(54,54,54)");


    // // 添加透明背景支持
    setAttribute(Qt::WA_TranslucentBackground);

    setAttribute(Qt::WA_StyledBackground);

    // this->setWindowFlags(Qt::FramelessWindowHint | Qt::ToolTip);
    this->setWindowFlags(Qt::FramelessWindowHint);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(0); // 设置控件间间距为0
    layout->setContentsMargins(0,0,0,0); // 设置边距为0

    // 设置进度条的最小高度
    _pposslide->setMinimumHeight(20);
    layout->addWidget(_pposslide);

    layout->addStretch();

    // 设置控制栏的最小高度
    _pcbottom->setMinimumHeight(60);
    layout->addWidget(_pcbottom);

    // 设置背景色，以便观察
    setStyleSheet("CcombinationPlay { background-color: rgba(50,50,50,150); }");

    connect(_pcbottom, &CBottomCtrlBar::sig_play, this, &CcombinationPlay::sig_play);
    connect(_pcbottom, &CBottomCtrlBar::sig_stop, this, &CcombinationPlay::sig_stop);
    connect(_pcbottom, &CBottomCtrlBar::sig_next, this, &CcombinationPlay::sig_next);
    connect(_pcbottom, &CBottomCtrlBar::sig_pre, this, &CcombinationPlay::sig_pre);
    connect(_pcbottom, &CBottomCtrlBar::sig_fullScreen, this, &CcombinationPlay::sig_fullScreen);
    connect(_pcbottom, &CBottomCtrlBar::open_file, this, &CcombinationPlay::open_file);
    // &QPushButton::clicked ->&CPlayButtonGroupWidget::sig_play-> &CBottomCtrlBar::sig_play
    connect(_pcbottom,&CBottomCtrlBar::sig_volume,this,&CcombinationPlay::sig_volume);

    connect(_pposslide, &CPositionSliderDialog::sig_pslider, this, &CcombinationPlay::sig_pslider);

}
// _pcbottom


void CcombinationPlay::showTimeLabel(bool isShow)
{
    _pcbottom->showTimeLabel(isShow);
}

void CcombinationPlay::setCurPlayTime(const qint64 &curMs)
{
    _pcbottom->setCurPlayTime(curMs);
}

void CcombinationPlay::setTotalTime(const qint64 &totalMs)
{
    _pcbottom->setTotalTime(totalMs);
}

void CcombinationPlay::setVolume_Value(int value)
{
    _pcbottom->setVolume_Value(value);
}

bool CcombinationPlay::IsSliderDown()
{
    return _pposslide->IsSliderDown();
}

int CcombinationPlay::value()
{
   return  _pposslide->value();
}

void CcombinationPlay::setSliderValue(int value)
{
    _pposslide->setSliderValue(value);
}

void CcombinationPlay::setSlideHide()
{
    _pposslide->hide();
}

void CcombinationPlay::setSlideShow()
{
    _pposslide->show();
}

