#ifndef CVOLUMESLIDERDIALOG_H
#define CVOLUMESLIDERDIALOG_H

#include <QDialog>
#include <QSlider>

QT_END_NAMESPACE

class CVolumeSliderDialog : public QDialog
{
    Q_OBJECT

public:
    CVolumeSliderDialog(QWidget *parent = nullptr);
    ~CVolumeSliderDialog();

    int value();

    void setSliderValue(int value);
signals:
    void sig_volume(int);

private:
    QSlider * _pslider = nullptr;
};
#endif // CVOLUMESLIDERDIALOG_H
