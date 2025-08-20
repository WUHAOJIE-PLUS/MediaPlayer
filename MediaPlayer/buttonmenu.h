#ifndef BUTTONMENU_H
#define BUTTONMENU_H

#include <QWidget>
#include <QPushButton>

QT_END_NAMESPACE

class ButtonMenu : public QWidget
{
    Q_OBJECT

public:
    ButtonMenu(QWidget *parent = nullptr);
    ~ButtonMenu();
signals:
    void sig_openfile();
private:
    QPushButton *wd_bnt;
};
#endif // BUTTONMENU_H

