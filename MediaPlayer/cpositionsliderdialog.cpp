#include "cpositionsliderdialog.h"
#include <QHBoxLayout>
#include <QTimer>
#include <QPropertyAnimation>

CPositionSliderDialog::CPositionSliderDialog(QWidget *parent)
    : QDialog(parent)
    ,_pslider(new QSlider(this))
{


    // macOS 特殊设置
#ifdef Q_OS_MAC
    // 移除 ToolTip 标志（macOS 上 ToolTip 窗口行为不同）
    setWindowFlags(Qt::FramelessWindowHint | Qt::SubWindow);

    // 添加透明背景支持
    // setAttribute(Qt::WA_TranslucentBackground);

    // 添加圆角效果
    setStyleSheet(R"(
        QDialog {
            background-color: rgba(54, 54, 54, 0.7);
            // border-radius: 8px;
            border-top-left-radius: 0;
            border-top-right-radius: 0;
            border: 1px solid rgba(100, 100, 100, 0.3);
        }
    )");
#else
    // 其他平台保持原样
    setFixedSize(800, 50);
    setWindowFlags(Qt::FramelessWindowHint | Qt::ToolTip);
    setStyleSheet("QDialog{background-color: rgba(54,54,54, 0.5)}");
#endif

    // 创建滑动条
    // _pslider = new QSlider(this);
    _pslider->setOrientation(Qt::Horizontal);
    _pslider->setRange(0, 100);
    _pslider->setValue(0);
    // macOS 滑动条样式优化


#ifdef Q_OS_MAC
    _pslider->setStyleSheet(R"(

        QSlider {
            height: 10px;
            background: rgba(100, 100, 100, 0.3);
            border-radius: 3px;
        }
        QSlider::groove:horizontal {
            background: rgba(100, 100, 100, 0.3);
            height: 6px;
            border-radius: 3px;
        }
        QSlider::handle:horizontal {
            background: #f0f0f0;
            width: 16px;
            height: 16px;
            margin: -5px 0;
            border-radius: 8px;
        }
        QSlider::sub-page:horizontal {
            background: #4a86e8;
            border-radius: 3px;
        }
    )");
#endif

    QHBoxLayout *pvlayout = new QHBoxLayout(this);
    pvlayout->addWidget(_pslider);

    // macOS 添加内边距
#ifdef Q_OS_MAC
    pvlayout->setContentsMargins(20, 10, 20, 15);
#else
    pvlayout->setContentsMargins(10, 5, 10, 5);
#endif

    connect(_pslider, &QSlider::sliderMoved, this, &CPositionSliderDialog::sig_pslider);

//     // macOS 添加动画效果
// #ifdef Q_OS_MAC
//     QTimer::singleShot(0, this, [=]{
//         QPropertyAnimation *anim = new QPropertyAnimation(this, "pos");
//         anim->setDuration(300);
//         anim->setStartValue(QPoint(0, parentWidget()->height()));
//         anim->setEndValue(QPoint(0, parentWidget()->height() - height()));
//         anim->setEasingCurve(QEasingCurve::OutQuad);
//         anim->start();
//     });
// #endif
}
CPositionSliderDialog::~CPositionSliderDialog() {}

bool CPositionSliderDialog::IsSliderDown()
{
    if(_pslider){
    return _pslider->isSliderDown();
    }
    return false;
}

int CPositionSliderDialog::value()
{
    if(_pslider){
        return _pslider->value();
    }
    return -1;
}

void CPositionSliderDialog::setSliderValue(int value)
{
    if(_pslider){
        _pslider->setValue(value);
    }
}
