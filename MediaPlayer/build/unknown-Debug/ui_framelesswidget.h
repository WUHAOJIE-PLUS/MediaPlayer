/********************************************************************************
** Form generated from reading UI file 'framelesswidget.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FRAMELESSWIDGET_H
#define UI_FRAMELESSWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FramelessWidget
{
public:

    void setupUi(QWidget *FramelessWidget)
    {
        if (FramelessWidget->objectName().isEmpty())
            FramelessWidget->setObjectName("FramelessWidget");
        FramelessWidget->resize(800, 600);

        retranslateUi(FramelessWidget);

        QMetaObject::connectSlotsByName(FramelessWidget);
    } // setupUi

    void retranslateUi(QWidget *FramelessWidget)
    {
        FramelessWidget->setWindowTitle(QCoreApplication::translate("FramelessWidget", "FramelessWidget", nullptr));
    } // retranslateUi

};

namespace Ui {
    class FramelessWidget: public Ui_FramelessWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FRAMELESSWIDGET_H
