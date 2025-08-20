#include "cbottomctrlbar.h"
#include <QHBoxLayout>

CBottomCtrlBar::CBottomCtrlBar(QWidget *parent)
    : QWidget{parent}
    ,m_pPlayButtonGroupWidget(new CPlayButtonGroupWidget(this))
{

    // resize(700,80);
    //禁止父窗口影响子窗口样式
    setAttribute(Qt::WA_StyledBackground);
    setMouseTracking(true);

    // this->setFixedHeight(60);

    setStyleSheet("background-color:rgb(54,54,54)");


    QString label_qss = "QLabel{font-family:Microsoft YaHei; font-size:18px; color:rgb(255,255,255);}";
    m_pCurPlayTimeLabel = new QLabel(this);
    m_pCurPlayTimeLabel->setText("00:00:00");
    m_pCurPlayTimeLabel->setAlignment(Qt::AlignRight);
    m_pCurPlayTimeLabel->setFixedSize(80, 32);
    m_pCurPlayTimeLabel->setStyleSheet(label_qss);

    m_pTotalTimeLabel = new QLabel(this);
    m_pTotalTimeLabel->setText("01:20:30");
    m_pTotalTimeLabel->setAlignment(Qt::AlignLeft);
    m_pTotalTimeLabel->setFixedSize(160, 32);
    m_pTotalTimeLabel->setStyleSheet(label_qss);

    // m_pPlayButtonGroupWidget = new CPlayButtonGroupWidget(this);

    m_pFileBoxButton = new QPushButton(this);
    m_pFileBoxButton->setText("");
    m_pFileBoxButton->setFixedSize(32, 32);
    m_pFileBoxButton->setStyleSheet("QPushButton{background-image:url(:/toolbox_hover.svg);border:none;}"
                                    "QPushButton:hover{background-image:url(:/toolbox.svg);border:none; }"
                                    "QPushButton:pressed{background-image:url(:/toolbox_hover.svg);border:none;}");

    m_pEffectButton = new QPushButton(this);
    m_pEffectButton->setText("");
    m_pEffectButton->setFixedSize(32, 32);
    m_pEffectButton->setStyleSheet("QPushButton{background-image:url(:/playctrlBar/effect.svg);border:none;}"
                                   "QPushButton:hover{background-image:url(:/playctrlBar/effect_hover.svg);border:none;} "
                                   "QPushButton:pressed{background-image:url(:/playctrlBar/effect.svg);border:none;}");

    m_pFullscreenButton = new QPushButton(this);
    m_pFullscreenButton->setText("");
    m_pFullscreenButton->setFixedSize(32, 32);
    m_pFullscreenButton->setStyleSheet("QPushButton{background-image:url(:/playctrlBar/fullscreen.svg);border:none;}"
                                       "QPushButton:hover{background-image:url(:/playctrlBar/fullscreen_hover.svg);border:no ne;}"
                                       "QPushButton:pressed{background-image:url(:/playctrlBar/fullscreen.svg);border:none;}") ;

    QHBoxLayout* pHLay = new QHBoxLayout(this);
    pHLay->addSpacing(3);//在此盒子布局的末尾添加一个大小为 size 的不可拉伸空间
    pHLay->addWidget(m_pCurPlayTimeLabel);
    pHLay->addSpacing(1);
    pHLay->addWidget(m_pTotalTimeLabel);

    pHLay->addStretch();//在该框布局的末尾添加一个最小尺寸为0,拉伸因子为拉伸的可拉伸空间
    pHLay->addWidget(m_pPlayButtonGroupWidget);
    pHLay->addStretch();

    pHLay->addWidget(m_pFileBoxButton);
    pHLay->addSpacing(18);
    pHLay->addWidget(m_pEffectButton);
    pHLay->addSpacing(18);
    pHLay->addWidget(m_pFullscreenButton);

    showTimeLabel(false);//是否显示时间

    connect(m_pPlayButtonGroupWidget, &CPlayButtonGroupWidget::sig_play, this, &CBottomCtrlBar::sig_play);
    connect(m_pPlayButtonGroupWidget, &CPlayButtonGroupWidget::sig_stop, this, &CBottomCtrlBar::sig_stop);
    connect(m_pPlayButtonGroupWidget, &CPlayButtonGroupWidget::sig_next, this, &CBottomCtrlBar::sig_next);
    connect(m_pPlayButtonGroupWidget, &CPlayButtonGroupWidget::sig_pre, this, &CBottomCtrlBar::sig_pre);
    connect(m_pFullscreenButton, &QPushButton::clicked, this, &CBottomCtrlBar::sig_fullScreen);
     // &QPushButton::clicked ->&CPlayButtonGroupWidget::sig_play-> &CBottomCtrlBar::sig_play
    connect(m_pPlayButtonGroupWidget,&CPlayButtonGroupWidget::sig_volume,this,&CBottomCtrlBar::sig_volume);
    connect(m_pFileBoxButton, &QPushButton::clicked, this, &CBottomCtrlBar::open_file);

}

CBottomCtrlBar::~CBottomCtrlBar() {
}

void CBottomCtrlBar::showTimeLabel(bool isShow) {
    if (isShow) {
        m_pCurPlayTimeLabel->show();
        m_pTotalTimeLabel->show();
    } else {
        m_pCurPlayTimeLabel->hide();
        m_pTotalTimeLabel->hide();
    }
}

//下面三个函数完成了2个时间QLabel的设置，与vlc联系起来
QString CBottomCtrlBar::formatTimeMs(const qint64& timeMs) {

    qint64 seconds = timeMs / 1000;

    int secs = seconds % 60;
    int mins = seconds / 60 % 60;
    int hours = seconds/3600;

    // 使用QString::arg()的格式化功能确保两位数显示
    if (hours == 0) {
        // 总时长小于1小时，只显示分钟和秒

        QString Time = QString("%1:%2")
                               .arg(mins, 2, 10, QLatin1Char('0'))  // 分钟，两位数
                               .arg(secs, 2, 10, QLatin1Char('0'));  // 秒，两位数

        // qDebug() << Time;
        return Time;
    } else {
        // 总时长大于1小时，显示完整时间
        QString Time = QString("%1:%2:%3")
                               .arg(hours, 2, 10, QLatin1Char('0'))  // 小时，两位数
                               .arg(mins, 2, 10, QLatin1Char('0'))   // 分钟，两位数
                               .arg(secs, 2, 10, QLatin1Char('0'));   // 秒，两位数
        // qDebug() << Time;
        return Time;

    }
}


//设置当前播放时间
void CBottomCtrlBar::setCurPlayTime(const qint64& curMs) {
    m_pCurPlayTimeLabel->setText(formatTimeMs(curMs));
}

//设置总的播放时间
void CBottomCtrlBar::setTotalTime(const qint64& totalMs) {
    m_pTotalTimeLabel->setText("/  " + formatTimeMs(totalMs));
}

void CBottomCtrlBar::setVolume_Value(int value)
{

    if(m_pPlayButtonGroupWidget){
        m_pPlayButtonGroupWidget->setVolume_Value(value);
    }
}


//功能：当控件大小改变时，重新定位子控件（m_pPlayButtonGroupWidget）到父控件的中心位置
void CBottomCtrlBar::resizeEvent(QResizeEvent* event) {
    if (m_pPlayButtonGroupWidget) {
        int x = this->width() / 2 - m_pPlayButtonGroupWidget->width() / 2; //计算子控件的水平居中位置：x = (父控件宽度 - 子控件宽度) / 2
        int y = this->height() / 2 - m_pPlayButtonGroupWidget->height() / 2;//计算子控件的垂直居中位置：y = (父控件高度 - 子控件高度) / 2
        m_pPlayButtonGroupWidget->move(x, y); //将子控件移动到计算出的位置 (x, y)
    }
}
