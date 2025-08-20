#ifndef CPOSITIONSLIDER_H
#define CPOSITIONSLIDER_H

#include <QDialog>
#include <QSlider>

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

private:
    QSlider * _pslider = nullptr;
};
#endif // CPOSITIONSLIDER_H
