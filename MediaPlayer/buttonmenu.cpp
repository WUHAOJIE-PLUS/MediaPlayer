#include "buttonmenu.h"
#include <QFile>
#include <QMenu>
#include <QFileDialog>
#include <string>
#include <QTimer>
#include <QPushButton>
using std::string;

ButtonMenu::ButtonMenu(QWidget *parent)
    : QWidget(parent)
{

    //禁止父窗口影响子窗口样式
    setAttribute(Qt::WA_StyledBackground);
    setMouseTracking(true);

    this->setFixedHeight(50);

    setStyleSheet("background-color:rgb(54,54,54)");





    QMenu * fileMenuItems = new QMenu(this);
    // QMenu * fileMenuItems = new QMenu;


    fileMenuItems->setIcon(QIcon(":/3/resources/file.png"));
    fileMenuItems->setTitle("文件");

    QList<QAction *> fileAcList;

    QAction * openFileAc = new QAction(QIcon(":/3/resources/file.png"), "打开文件", this);

    openFileAc->setShortcut(QKeySequence("Ctrl+O"));// 设置快捷键

    QAction * openFolderAc = new QAction("打开文件夹", this);
    QAction * openUrlAc = new QAction("打开url", this);

    fileAcList << openFileAc << openFolderAc << openUrlAc;
    fileMenuItems->addActions(fileAcList);//添加二级子菜单


    QMenu * menu = new QMenu(this);//主菜单
    // QMenu * menu = new QMenu;//主菜单

    menu->addMenu(fileMenuItems);//添加一级子菜单

    QAction * playAc = new QAction(QIcon(":/3/resources/play.png"), "播放", this);
    QAction * toolsAc = new QAction(QIcon(":/3/resources/tools.png"), "工具", this);

    menu->addAction(playAc);
    menu->addAction(toolsAc);
    menu->addSeparator();//添加分隔线

    QMenu * setMenuItems = new QMenu(this);
    // QMenu * setMenuItems = new QMenu;

    setMenuItems->setTitle("设置");
    setMenuItems->setIcon(QIcon(":/3/resources/set.png"));

    QList<QAction*> setAcList;
    QAction * sysSetAc = new QAction("系统设置", this);
    QAction * playSetAc = new QAction("播放设置", this);
    QAction * captionSetAc = new QAction("字幕设置", this);


    setAcList << sysSetAc << playSetAc << captionSetAc;
    setMenuItems->addActions(setAcList);//添加二级子菜单

    menu->addMenu(setMenuItems);
    menu->addSeparator();//添加分隔线

    QAction * exitAc = new QAction(QIcon(":/3/resources/file.png"), "退出", this);
    menu->addAction(exitAc);

    // menu->setStyleSheet(QString::fromStdString(menuQss));



    wd_bnt = new QPushButton("王道影音",this);
    wd_bnt->setMenu(menu);//在按钮上设置菜单

    wd_bnt->setText("王道影音");
    wd_bnt->setFixedSize(120,50);
    wd_bnt->setMenu(menu);//在按钮上设置菜单
    // wd_bnt->setStyleSheet(QString::fromStdString(buttonQss));
    wd_bnt->setStyleSheet("color:white");

    // menu->setStyleSheet(QString::fromStdString(menuQss));//设置样式表
    menu->setStyleSheet("color:white");
    // fileMenuItems->setStyleSheet(QString::fromStdString(menuItemQss));//设置样式表
    // setMenuItems->setStyleSheet(QString::fromStdString(menuItemQss));//设置样式表
    fileMenuItems->setStyleSheet("color:white");
    setMenuItems->setStyleSheet("color:white");


    //绑定信号与槽
    connect(openFileAc, &QAction::triggered, this,&ButtonMenu::sig_openfile);
}


ButtonMenu::~ButtonMenu()
{
}

