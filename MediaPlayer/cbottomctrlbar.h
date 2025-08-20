#ifndef CBOTTOMCTRLBAR_H
#define CBOTTOMCTRLBAR_H

#include "cplaybuttongroupwidget.h"
#include <QWidget>
#include <QLabel>
#include <QPushButton>

class CBottomCtrlBar : public QWidget
{
    Q_OBJECT
public:
    explicit CBottomCtrlBar(QWidget *parent = nullptr);
    ~CBottomCtrlBar();

    void showTimeLabel(bool isShow);
    void setCurPlayTime(const qint64& curMs);
    void setTotalTime(const qint64& totalMs);

    void setVolume_Value(int value);

    void setStart_bnt(){
        m_pPlayButtonGroupWidget->setStart_bnt();
    }
    void setPause_bnt(){
        m_pPlayButtonGroupWidget->setPause_bnt();
    }

signals:
    void sig_play();//与播放connect
    void sig_stop();//与停止connect
    void sig_pre();
    void sig_next();

    void sig_fullScreen();

    void sig_volume(int);

    void open_file();

private:
    QString formatTimeMs(const qint64& timeMs);

private:
    void resizeEvent(QResizeEvent* event) override;

private:
    QLabel* m_pCurPlayTimeLabel = nullptr;
    QLabel* m_pTotalTimeLabel = nullptr;
    CPlayButtonGroupWidget* m_pPlayButtonGroupWidget = nullptr;
    QPushButton* m_pFileBoxButton = nullptr;
    QPushButton* m_pEffectButton = nullptr;
    QPushButton* m_pFullscreenButton = nullptr;
};



#endif // CBOTTOMCTRLBAR_H
