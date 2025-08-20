#ifndef CPOSITIONSLIDERDIALOG_H
#define CPOSITIONSLIDERDIALOG_H

#include <QDialog>
#include <QSlider>

class CPositionSliderDialog : public QDialog
{
    Q_OBJECT

public:
    CPositionSliderDialog(QWidget *parent = nullptr);
    ~CPositionSliderDialog();

    bool IsSliderDown();
    int value();
    void setSliderValue(int value);

signals:
    void sig_pslider(int);

private:
    QSlider * _pslider = nullptr;
};
#endif // CPOSITIONSLIDERDIALOG_H
