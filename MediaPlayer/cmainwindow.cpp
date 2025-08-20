#include "cmainwindow.h"
#include "playlistdialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QStyleFactory>
#include <QFileDialog>
#include <QMenu>
#include <QTimer>

#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QPainter>

CMainWindow::CMainWindow(QWidget * parent)
    : FramelessWidget(parent)
    ,vlckits(new VLCKits(this))
    ,_ptitleBar(new CTitleBar(this))
    ,wbody(new VideoWidget(this))
    ,Show_Playlist_btn(new QPushButton(this))
    ,_buttonmenu(new ButtonMenu(wbody))
    ,_imageLabel(new QLabel(wbody))
    ,_pbottom_play(new CcombinationPlay(this))
{
    _pbottom_play->setSlideHide();
    initUI();
}

void CMainWindow::closeSlot()
{
// macOS 专用样式
    QString styleSheet = R"(
    QMessageBox {
        background-color: rgba(245, 245, 247, 0.95);
        border: 1px solid rgba(0, 0, 0, 0.1);
        border-radius: 12px;
        padding: 25px;
        font-family: -apple-system, BlinkMacSystemFont, "Helvetica Neue", sans-serif;
        box-shadow: 0 10px 30px rgba(0, 0, 0, 0.1);
    }

    QMessageBox QLabel#qt_msgbox_label {
        color: #333;
        font-size: 16px;
        font-weight: 500;
        margin-bottom: 25px;
    }

    QMessageBox QPushButton {
        background-color: #007aff;
        color: white;
        border-radius: 6px;
        padding: 8px 24px;
        font-size: 14px;
        min-width: 80px;
    }

    QMessageBox QPushButton:hover {
        background-color: #0066cc;
    }

    QMessageBox QPushButton:pressed {
        background-color: #0055aa;
    }

    QMessageBox QPushButton:focus {
        outline: none;
        box-shadow: 0 0 0 2px rgba(0, 122, 255, 0.3);
    }
)";

    // 创建消息框
    QMessageBox msgBox;
    msgBox.setWindowTitle("提示");
    msgBox.setText("你确定要退出吗？");
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);


    // 添加淡入动画
    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect(&msgBox);
    msgBox.setGraphicsEffect(opacityEffect);

    QPropertyAnimation *anim = new QPropertyAnimation(opacityEffect, "opacity");
    anim->setDuration(300);
    anim->setStartValue(0.0);
    anim->setEndValue(1.0);
    anim->setEasingCurve(QEasingCurve::OutQuad);
    anim->start();

    // 设置自定义警告图标
    QPixmap warningIcon(64, 64);
    warningIcon.fill(Qt::transparent);

    QPainter painter(&warningIcon);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QColor(255, 204, 0)); // 黄色警告色
    painter.setPen(Qt::NoPen);
    painter.drawEllipse(0, 0, 64, 64);
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial", 48, QFont::Bold));
    painter.drawText(warningIcon.rect(), Qt::AlignCenter, "!");

    msgBox.setIconPixmap(warningIcon);

    // 应用样式表
    msgBox.setStyleSheet(styleSheet);

    // 显示消息框
    int ret = msgBox.exec();

    if(ret == QMessageBox::Yes) {
        Stop();
        close();
    }
}


void CMainWindow::initUI()
{
    wbody->setMinimumSize(800, 600);


    // 加载图片资源
    QPixmap logo(":/logo.png");
    _imageLabel->setPixmap(logo);

    Show_Playlist_btn->setText("");
    Show_Playlist_btn->setFixedSize(32, 32);
    Show_Playlist_btn->move(768,380);
    Show_Playlist_btn->setStyleSheet("QPushButton{background-image:url(:/left_arrow.svg);border:none;}"
                                 "QPushButton:hover{background-image:url(:/left_arrow_hover.svg);border:none;}"
                                 "QPushButton:pressed{background-image:url(:/left_arrow.svg);border:none;}");

    QVBoxLayout * pvLayout = new QVBoxLayout(this);
    pvLayout->addWidget(_ptitleBar);//可以直接传类
    pvLayout->addWidget(wbody);
    pvLayout->addWidget(_pbottom_play);
    pvLayout->setContentsMargins(0, 0, 0, 0);

    //右键菜单
    QMenu *contex_pmenu = new QMenu(this);
    QAction *open_file = new QAction("打开文件",this);
    QAction *stop_video = new QAction("停止视频",this);
    QAction *close_widget = new QAction("关闭app",this);

    open_file->setShortcut(Qt::CTRL | Qt::Key_O);
    close_widget->setShortcut(QKeySequence("Ctrl+E"));

    contex_pmenu->addAction(open_file);
    contex_pmenu->addAction(stop_video);
    contex_pmenu->addAction(close_widget);

    contex_pmenu->setStyleSheet(
        "QMenu {"
        "color: white;"      // 保留原文字颜色
        "border: 1px solid #5e5e5e;" // 添加1px深灰色边框
        "background-color: #333333;" // 添加背景色
        "}"
        );

    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this,&QWidget::customContextMenuRequested,[=](const QPoint &pos){
        contex_pmenu->exec(QCursor::pos());//显示菜单
    });


    connect(_ptitleBar, &CTitleBar::sigClose, this, &CMainWindow::closeSlot);
    connect(_buttonmenu,&ButtonMenu::sig_openfile,this,&CMainWindow::Openfile);
    connect(_buttonmenu,&ButtonMenu::sig_openfile,this,&CMainWindow::Openfile);
    connect(_pbottom_play,&CcombinationPlay::open_file,this,&CMainWindow::Openfile);
    connect(_pbottom_play,&CcombinationPlay::sig_play,this,&CMainWindow::Start_Pause);
    connect(_pbottom_play,&CcombinationPlay::sig_stop,this,&CMainWindow::Stop);
    connect(_pbottom_play,&CcombinationPlay::sig_pre,this,&CMainWindow::PlayPre);
    connect(_pbottom_play,&CcombinationPlay::sig_next,this,&CMainWindow::PlayNext);
    connect(vlckits,&VLCKits::sigTimeText,this,&CMainWindow::updateTimeText);
    connect(vlckits, &VLCKits::sigVolumeSliderPos, this, &CMainWindow::updateVolume);
    connect(_pbottom_play,&CcombinationPlay::sig_volume,this,&CMainWindow::setVolume);//手动托
    // //连接进度条拖动信号
    connect(_pbottom_play,&CcombinationPlay::sig_pslider,this,&CMainWindow::seekPosition);
    connect(vlckits, &VLCKits::sigTimeSliderPos, this, &CMainWindow::updatePosition);
    connect(_pbottom_play,&CcombinationPlay::sig_fullScreen,this,&CMainWindow::isFullScreenSlot);
    connect(Show_Playlist_btn, &QPushButton::clicked, this, &CMainWindow::onShowPlaylist);
    //绑定信号与槽
    connect(open_file, &QAction::triggered, this,&CMainWindow::Openfile);
    connect(stop_video, &QAction::triggered, this,&CMainWindow::Stop);
    connect(close_widget, &QAction::triggered, this,&CMainWindow::closeSlot);

    connect(wbody,&VideoWidget::combinwidget,this,&CMainWindow::showcombination);
    connect(wbody,&VideoWidget::is_full,this,&CMainWindow::isFullScreenSlot);


    QTimer *tm = new QTimer(this);
    tm->setInterval(5000); // 5秒触发一次
    connect(tm,&QTimer::timeout,this,&CMainWindow::hidecombination);
    tm->start();
}

void CMainWindow::isFullScreenSlot()
{
    if(this->isFullScreen()) {//是否全屏
        wbody->setMinimumSize(800, 600);
        _ptitleBar->show();
        _pbottom_play->show();
        wbody->set_is_FullScreen(false);
        this->showNormal();//退出全屏
    } else{
        wbody->set_is_FullScreen(true);
        this->showFullScreen();//全屏
        wbody->setMinimumSize(800, 790);
        _pbottom_play->hide();
        _ptitleBar->hide();
    }
}



//打开文件
void CMainWindow::Openfile()
{
    //一次选一个或者多个
    QStringList path = QFileDialog::getOpenFileNames(this,"xxx","/Users/aurora_sco/Movies/bilibili/ ","所有文件 (*.*);;MP4 视频 (*.mp4);;MP3 音频 (*.mp3);;AVI 视频 (*.avi)");
    for(auto &elem:path){
        qDebug() << elem;
    }
    if(path.isEmpty()){
        return;
    }

    if (vlckits->initVLC()) {
        qDebug() << "initVLC成功";
        // 初始化成功，然后播放
        if(vlckits->play(path,(void *)wbody->winId())){
            //播放成功则显示时间
            _pbottom_play->showTimeLabel(true);
        }

    } else {
        qDebug() << "initVLC失败";
        // 初始化失败
    }
    _buttonmenu->hide();
    _pbottom_play->setSlideShow();//进度条展示的代码
    _pbottom_play->setPause_bnt();
}

void CMainWindow::Start_Pause(){
    //获取vlc的状态
    if(vlckits->mediaPlayer()){
        if(vlckits->get_vlcState() == libvlc_Playing){
            vlckits->pause();
            _pbottom_play->setStart_bnt();
        }else{
            vlckits->play();
            _pbottom_play->setPause_bnt();
        }
    }

}

void CMainWindow::Stop(){
    if(vlckits->mediaPlayer()){
        _pbottom_play->setStart_bnt();
    }
    vlckits->stop();
    _buttonmenu->show();
    _pbottom_play->setSlideHide();//进度条隐藏的代码
    _pbottom_play->showTimeLabel(false);//关闭时间标签

}

void CMainWindow::PlayPre()
{
    vlckits->playPrevious();

    if(vlckits->mediaPlayer()){
        _pbottom_play->setPause_bnt();
    }
}

void CMainWindow::PlayNext()
{
    vlckits->playNext();

    if(vlckits->mediaPlayer()){
        _pbottom_play->setPause_bnt();
    }
}



//手动拖
void CMainWindow::setVolume(int value){
    vlckits->setVolume(value);
}

void CMainWindow::seekPosition(int value) {

    if(vlckits->durationArr()[vlckits->currentIndex()] > 0)
    {
        //设置播放位置
        vlckits->setPosition(value);//直接传送进度条的位置（0-100）
    }
}


//每秒自动更新
//更新进度条的位置
void CMainWindow::updatePosition(int value)
{
    // 如果用户正在拖动进度条，则跳过自动更新
    if(_pbottom_play->IsSliderDown()){
        return;
    }
    if(vlckits->durationArr()[vlckits->currentIndex()] > 0)
    {
        //将播放进度转换为百分比形式,这是乘以100的作用，不然就是小数
        _pbottom_play->setSliderValue(value);
    }
}

//考虑定时器，或者vlckits的信号
void CMainWindow::updateTimeText()
{
    libvlc_time_t curSecs = vlckits->getcurSecs();
    libvlc_time_t totalSecs = vlckits->get_totalSecs();

    _pbottom_play->setCurPlayTime(curSecs);
    _pbottom_play->setTotalTime(totalSecs);
}

void CMainWindow::updateVolume(int value)
{
    //将播放进度转换为百分比形式,这是乘以100的作用，不然就是小数
    _pbottom_play->setVolume_Value(value);
}



void CMainWindow::onShowPlaylist() {

    if(vlckits->mediaPlayer()){

        Show_Playlist_btn->setStyleSheet("QPushButton{background-image:url(:/right_arrow.svg);border:none;}"
                                         "QPushButton:hover{background-image:url(:/right_arrow_hover.svg);border:none;}"
                                         "QPushButton:pressed{background-image:url(:/right_arrow.svg);border:none;}");

        medialist_dialog = new PlaylistDialog(vlckits->mediaList(),this);
        connect(medialist_dialog, &PlaylistDialog::itemSelected, this, &CMainWindow::onItemSelected);

        //当我点击列表按钮后，如果没有选择视频，则一直会阻塞这里
        //当选择视频后，会跳出阻塞，继续往下执行
        medialist_dialog->exec();
        medialist_dialog->deleteLater(); // 安全删除
        qDebug() << "onShowPlaylist";
    }

}

void CMainWindow::onItemSelected(int index) {
    vlckits->onItemSelected(index);
    Show_Playlist_btn->setStyleSheet("QPushButton{background-image:url(:/left_arrow.svg);border:none;}"
                                     "QPushButton:hover{background-image:url(:/left_arrow_hover.svg);border:none;}"
                                     "QPushButton:pressed{background-image:url(:/left_arrow.svg);border:none;}");

    _pbottom_play->setPause_bnt();
}

void CMainWindow::showcombination()
{
    if(this->isFullScreen()){
        _pbottom_play->show();
    }
}

void CMainWindow::hidecombination()
{
    if(this->isFullScreen()){
        _pbottom_play->hide();
    }
}


//功能：当控件大小改变时，重新定位子控件（m_pPlayButtonGroupWidget）到父控件的中心位置
//目的，让按钮菜单始终位于内容窗口中间
void CMainWindow::resizeEvent(QResizeEvent* event) {
    if (_buttonmenu) {
        int x = wbody->width() / 2 - _buttonmenu->width() / 2; //计算子控件的水平居中位置：x = (父控件宽度 - 子控件宽度) / 2
        int y = wbody->height() / 2 - _buttonmenu->height() / 2;//计算子控件的垂直居中位置：y = (父控件高度 - 子控件高度) / 2
        _buttonmenu->move(x, y + 150); //将子控件移动到计算出的位置 (x, y)
    }
    if (_imageLabel) {
        int x = wbody->width() / 2 - _imageLabel->width() / 2; //计算子控件的水平居中位置：x = (父控件宽度 - 子控件宽度) / 2
        int y = wbody->height() / 2 - _imageLabel->height() / 2;//计算子控件的垂直居中位置：y = (父控件高度 - 子控件高度) / 2
        _imageLabel->move(x-10, y); //将子控件移动到计算出的位置 (x, y)
    }
    if (Show_Playlist_btn) {
        int x = wbody->width() - Show_Playlist_btn->width(); //计算子控件的水平居中位置：x = (父控件宽度 - 子控件宽度) / 2
        int y = wbody->height() / 2 - Show_Playlist_btn->height() / 2;//计算子控件的垂直居中位置：y = (父控件高度 - 子控件高度) / 2
        Show_Playlist_btn->move(x, y + 30); //将子控件移动到计算出的位置 (x, y)
    }

}

void CMainWindow::mouseDoubleClickEvent(QMouseEvent *event) {
    qDebug() << "mouseDoubleClickEvent";
    if(this->isFullScreen()) {//是否全屏
        wbody->setMinimumSize(800, 600);
        _ptitleBar->show();
        _pbottom_play->show();
        wbody->set_is_FullScreen(false);
        this->showNormal();//退出全屏
    } else{
        wbody->set_is_FullScreen(true);
        this->showFullScreen();//全屏
        wbody->setMinimumSize(800, 790);
        _ptitleBar->hide();
        _pbottom_play->hide();
    }
}

void CMainWindow::keyPressEvent(QKeyEvent *event) {
    qDebug() << "keyPressEvent";
    if(event->key() == Qt::Key_Escape) {
        wbody->setMinimumSize(800, 600);
        _ptitleBar->show();
        _pbottom_play->show();
        wbody->set_is_FullScreen(false);
        this->showNormal();//退出全屏
    }
}

