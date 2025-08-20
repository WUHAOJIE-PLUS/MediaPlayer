#include "cvolumesliderdialog.h"
#include <QVBoxLayout>

CVolumeSliderDialog::CVolumeSliderDialog(QWidget *parent)
    : QDialog(parent)
    ,_pslider(new QSlider(this))
{

    this->setFixedSize(60, 200);
    this->setAttribute(Qt::WA_StyledBackground);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::ToolTip);
    this->setStyleSheet("QDialog{background-color: rgba(54,54,54, 0.5)}");

    _pslider->setOrientation(Qt::Vertical);//设置滑动条的朝向
    _pslider->setRange(0,100);
    _pslider->setValue(50);
    QVBoxLayout * pvlayout = new QVBoxLayout(this);
    pvlayout->addWidget(_pslider);


    connect(_pslider,&QSlider::sliderMoved,this,&CVolumeSliderDialog::sig_volume);

}

CVolumeSliderDialog::~CVolumeSliderDialog()
{
}

int CVolumeSliderDialog::value()
{
    if(_pslider){
        return _pslider->value();
    }
    return -1;
}

void CVolumeSliderDialog::setSliderValue(int value)
{
    if(_pslider){
        _pslider->setValue(value);
    }
}

