/********************************************************************************
** Form generated from reading UI file 'hj.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HJ_H
#define UI_HJ_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_hj
{
public:

    void setupUi(QWidget *hj)
    {
        if (hj->objectName().isEmpty())
            hj->setObjectName("hj");
        hj->resize(400, 300);

        retranslateUi(hj);

        QMetaObject::connectSlotsByName(hj);
    } // setupUi

    void retranslateUi(QWidget *hj)
    {
        hj->setWindowTitle(QCoreApplication::translate("hj", "hj", nullptr));
    } // retranslateUi

};

namespace Ui {
    class hj: public Ui_hj {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HJ_H
