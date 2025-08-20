#include "cvolumebutton.h"
#include <QStylePainter>
#include <QStyleOptionButton>

CVolumeButton::CVolumeButton(QWidget *parent)
    : QPushButton(parent)
    , _pvolumeSliderDlg(new CVolumeSliderDialog(this))
{
    this->setFixedSize(32,32);
    setStyleSheet("QPushButton{background-image:url(:/2音量悬浮测试资源/resources/audio_open.svg);border:none;}"
        "QPushButton:hover{background-image:url(:/2音量悬浮测试资源/resources/audio_open_hover.svg);border:none;}"
        "QPushButton:pressed{background-image:url(:/2音量悬浮测试资源/resources/audio_open.svg);border:none;}");
    this->setWindowFlags(Qt::FramelessWindowHint);

    connect(_pvolumeSliderDlg,&CVolumeSliderDialog::sig_volume,this,&CVolumeButton::sig_volume);
}

CVolumeButton::~CVolumeButton()
{

}

void CVolumeButton::paintEvent(QPaintEvent *event)
{
    QStylePainter p(this);
    QStyleOptionButton option;

    initStyleOption(&option);
    p.drawControl(QStyle::CE_PushButton, option);

}

void CVolumeButton::enterEvent(QEnterEvent *event)
{
    if (!_pvolumeSliderDlg)
    _pvolumeSliderDlg = new CVolumeSliderDialog(this);
    //用于将窗口部件内的局部坐标转换为全局屏幕坐标。这个函数在处理鼠标位置、弹出菜单、拖放操作等场景中非常有用
    QPoint p1 = this->mapToGlobal(QPoint(0, 0)); //声音按钮左上角相对于屏幕的绝对位置
    QRect rect1 = this->rect();
    QRect rect2 = _pvolumeSliderDlg->rect(); //rect包含标题栏，去掉标题栏后height不变
    int x = p1.x() + (rect1.width() - rect2.width()) / 2;
    int y = p1.y() - rect2.height() - 5;
    _pvolumeSliderDlg->move(x, y); //move是相对于桌面原点的位置
    _pvolumeSliderDlg->show();

    //一旦音量控制界面出现后，就开启定时器
    if(_isRunning == false) {
        _timerId = startTimer(250);//开启定时器,250毫秒的时间间隔
        _isRunning = true;//定时器启动标志位
    }
}

//1s内触发4次判断是否隐身
void CVolumeButton::timerEvent(QTimerEvent *event)
{
    hide();
}

void CVolumeButton::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton) {
        _isMute = !_isMute;//按钮是为了静音
        if(_isMute) {//设置为静音
            if(_pvolumeSliderDlg) {
                //保存原来的音量值
                _volumeValue = _pvolumeSliderDlg->value();
                _pvolumeSliderDlg->setSliderValue(0);
                setStyleSheet("QPushButton{background-image:url(:/2音量悬浮测试资源/resources/audio_mute.png)}");
                emit sig_volume(0);
            }
        } else {//从静音状态返回之前状态
            if(_pvolumeSliderDlg) {
                _pvolumeSliderDlg->setSliderValue(_volumeValue);
                setStyleSheet(
                    "QPushButton{background-image:url(:/2音量悬浮测试资源/resources/audio_open.svg);border:none;}"
                    "QPushButton:hover{background-image:url(:/2音量悬浮测试资源/resources/audio_open_hover.svg);border:none;}"
                    "QPushButton:pressed{background-image:url(:/2音量悬浮测试资源/resources/audio_open.svg);border:none;}");
                emit sig_volume(_volumeValue);
            }
        }
    }
}


void CVolumeButton::hide()
{
    if(_pvolumeSliderDlg) {
        QPoint mousePos = QCursor::pos();//获取鼠标的位置
        //geometry()函数返回的是窗口部件在其父窗口坐标系中的矩形区域（包括窗口边框和标题栏，但对于无边框窗口则等同于内容区域)
        QRect rect1 = _pvolumeSliderDlg->geometry();
        QRect rect2 = this->geometry();
        QRect rect3(rect1.x(), rect1.y(), rect1.width(), rect1.height() + rect2.height());
        //根据鼠标的位置判断音量大小窗口是否消失
        if(!rect3.contains(mousePos)) {//鼠标退出区域
            //隐藏窗口小部件。此函数等效于 setVisible(false)
            _pvolumeSliderDlg->hide();
        }
    } else {//鼠标还在区域
        killTimer(_timerId);//当不包含鼠标位置，并且音量控制界面没显示时，就停止定时器
        _isRunning = false;
    }
}

void CVolumeButton::setVolume_Value(int value)
{
     if(_pvolumeSliderDlg){
        _pvolumeSliderDlg->setSliderValue(value);
     }
}



