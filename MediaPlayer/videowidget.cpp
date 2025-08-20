#include "videowidget.h"


VideoWidget::VideoWidget(QWidget *parent)
    : QWidget{parent}
    ,is_FullScreen(false)
{
}

void VideoWidget::set_is_FullScreen(bool on)
{
    is_FullScreen = on;
}
void VideoWidget::mousePressEvent(QMouseEvent *event)//右键移动才出现坐标
{
    if(is_FullScreen){
        emit combinwidget();
    }
}

void VideoWidget::mouseMoveEvent(QMouseEvent *event)//右键移动才出现坐标
{
    if(is_FullScreen){
        emit combinwidget();
    }
}

void VideoWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    emit is_full();
}
