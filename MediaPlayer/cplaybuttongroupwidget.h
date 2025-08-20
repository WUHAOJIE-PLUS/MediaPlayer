#ifndef CPLAYBUTTONGROUPWIDGET_H
#define CPLAYBUTTONGROUPWIDGET_H

#include <QWidget>
#include <QPushButton>
#include "cvolumebutton.h"


class CPlayButtonGroupWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CPlayButtonGroupWidget(QWidget *parent = nullptr);
    ~CPlayButtonGroupWidget();

    void setVolume_Value(int value);

    void setStart_bnt();
    void setPause_bnt();

signals:
    void sig_play();
    void sig_stop();
    void sig_next();
    void sig_pre();

    void sig_volume(int);

private:
    QPushButton* m_pStopButton = nullptr;
    QPushButton* m_pPreButton = nullptr;
    QPushButton* m_pPlayButton = nullptr;
    QPushButton* m_pNextButton = nullptr;
    CVolumeButton* m_pAudioButton = nullptr;
};

#endif // CPLAYBUTTONGROUPWIDGET_H
