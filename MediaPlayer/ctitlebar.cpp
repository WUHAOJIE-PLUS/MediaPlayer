#include "ctitlebar.h"
#include <QHBoxLayout>
#include <QMessageBox>

CTitleBar::CTitleBar(QWidget *parent)
    : QWidget{parent}
{
    initUI();
}

void CTitleBar::initUI()
{
//禁止父窗口影响子窗口样式,必须加上，否则样式不会起作用
    setAttribute(Qt::WA_StyledBackground);//设置或清除指定的窗⼝部件属性,WA_StyledBackground,表⽰是否允许使⽤样式表来绘制窗⼝部件的背景

    this->setFixedHeight(32 + 10);
    this->setStyleSheet("background-color:rgb(54,54,54)");


    _plogoLabel = new QLabel(this);
    QPixmap logo(":/wangdao.png");
    if (!logo.isNull()) {
        // 高质量缩放保持清晰度
        QPixmap scaledLogo = logo.scaled(32, 32, Qt::KeepAspectRatio, Qt::SmoothTransformation);

        // 设置到标签
        _plogoLabel->setPixmap(scaledLogo);
        _plogoLabel->setFixedSize(32, 32); // 固定标签大小
        _plogoLabel->setScaledContents(true); // 确保图片自适应标签大小
    } else {
        qWarning() << "Logo image not found!";
    }

    _ptitleTextLabel = new QLabel(this);
    _ptitleTextLabel->setText("王道音视频播放器");
    _ptitleTextLabel->setFixedWidth(150);
    _ptitleTextLabel->setStyleSheet(
        "QLabel{font-family: Microsoft YaHei;"
            "font-size:18px;"
            "color:#BDC8E2;background-color:rgb(54,54,54);}");

    _psetButton = new QPushButton(this);
    _psetButton->setFixedSize(32, 32);
    _psetButton->setStyleSheet(
"QPushButton{background-image:url(:/1标题栏测试资源/resources/titlebar/set.svg);border:none}"
    "QPushButton:hover{"
                "background-color:rgb(99, 99, 99);"
                "background-image:url(:/1标题栏测试资源/resources/titlebar/set_hover.svg);border:none;}");

    _pminButton = new QPushButton(this);
    _pminButton->setFixedSize(32, 32);
    _pminButton->setStyleSheet(
        "QPushButton{background-image:url(:/1标题栏测试资源/resources/titlebar/min.svg);border:none}"
        "QPushButton:hover{"
                "background-color:rgb(99, 99, 99);"
"background-image:url(:/1标题栏测试资源/resources/titlebar/min_hover.svg);border:none;}");

    _pmaxButton = new QPushButton(this);
    _pmaxButton->setFixedSize(32, 32);
    _pmaxButton->setStyleSheet(
    "QPushButton{background-image:url(:/1标题栏测试资源/resources/titlebar/max.svg);border:none}"
        "QPushButton:hover{"
                "background-color:rgb(99, 99, 99);"
                "background-image:url(:/1标题栏测试资源/resources/titlebar/max_hover.svg);border:none;}");

    _pcloseButton = new QPushButton(this);
    _pcloseButton->setFixedSize(32, 32);
    _pcloseButton->setStyleSheet(
        "QPushButton{background-image:url(:/1标题栏测试资源/resources/titlebar/close.svg);border:none}"
        "QPushButton:hover{"
            "background-color:rgb(99, 99, 99);"
                "background-image:url(:/1标题栏测试资源/resources/titlebar/close_hover.svg);border:none;}");

    QHBoxLayout * phLayout = new QHBoxLayout(this);
    phLayout->addWidget(_plogoLabel);
    phLayout->addWidget(_ptitleTextLabel);

    phLayout->addStretch();//添加一个弹簧。它直接在布局中添加⼀个可伸缩的空⽩区域

    phLayout->addWidget(_psetButton);

    phLayout->addWidget(_pminButton);

    phLayout->addWidget(_pmaxButton);


    phLayout->addWidget(_pcloseButton);
    phLayout->setContentsMargins(5,5,5,5);

    connect(_pminButton, &QPushButton::clicked, this, &CTitleBar::onClickedSlot);
    connect(_pmaxButton, &QPushButton::clicked, this, &CTitleBar::onClickedSlot);
    connect(_pcloseButton, &QPushButton::clicked, this, &CTitleBar::onClickedSlot);

}


void CTitleBar::onClickedSlot()
{
    QPushButton * pbtn = qobject_cast<QPushButton*>(sender());//获取是哪个按钮点击的
    QWidget * pwindow = this->window();
    if(pbtn == _pminButton) {//_pminButton点击
        pwindow->showMinimized();//设置为最小化
    } else if(pbtn == _pmaxButton) {//_pmaxButton点击
        if(pwindow->isMaximized()) {//判断此时状态是否为最大化
            pwindow->showNormal();//恢复正常
            _pmaxButton->setStyleSheet(
                "QPushButton{background-image:url(:/1标题栏测试资源/resources/titlebar/normal.svg);border:none}"
                "QPushButton:hover{"
                "background-color:rgb(99, 99, 99);"
                "background-image:url(:/1标题栏测试资源/resources/titlebar/normal_hover.svg);border:none;}");
        } else  {
            pwindow->showMaximized();//设置为最大化
            _pmaxButton->setStyleSheet(
                "QPushButton{background-image:url(:/1标题栏测试资源/resources/titlebar/max.svg);border:none}"
                "QPushButton:hover{"
                "background-color:rgb(99, 99, 99);"
                "background-image:url(:/1标题栏测试资源/resources/titlebar/max_hover.svg);border:none;}");
        }
    } else if(pbtn == _pcloseButton) {//_pcloseButton点击
        emit sigClose();//发射信号，通知父窗口关闭//如果在这里关闭的话，关闭的是标题栏，而不是整个app
    }
}
