#include "cpositionSlider.h"
#include <QHBoxLayout>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
{
    this->setFixedSize(700, 50);
    this->setAttribute(Qt::WA_StyledBackground);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::ToolTip);
    this->setStyleSheet("QDialog{background-color: rgba(54,54,54, 0.5)}");
    _pslider = new QSlider(this);//进度滑动条
    _pslider->setOrientation(Qt::Horizontal);//设置滑动条的朝向
    _pslider->setRange(0,100);
    _pslider->setValue(0);
    QHBoxLayout * pvlayout = new QHBoxLayout(this);
    pvlayout->addWidget(_pslider);
}

Dialog::~Dialog() {}
