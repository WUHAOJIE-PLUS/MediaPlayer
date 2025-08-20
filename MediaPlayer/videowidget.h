#ifndef VIDEOWIDGET_H
#define VIDEOWIDGET_H

#include <QWidget>
#include <QMouseEvent>

class VideoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit VideoWidget(QWidget *parent = nullptr);

    void set_is_FullScreen(bool on);
protected:
    void mousePressEvent(QMouseEvent *event)override;
    void mouseMoveEvent(QMouseEvent *event)override;
    void mouseDoubleClickEvent(QMouseEvent *event)override;

signals:
    void combinwidget();
    void is_full();
private:
    bool is_FullScreen;
};

#endif // VIDEOWIDGET_H
