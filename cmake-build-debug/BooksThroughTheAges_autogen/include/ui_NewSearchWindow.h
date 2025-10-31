/********************************************************************************
** Form generated from reading UI file 'NewSearchWindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NEWSEARCHWINDOW_H
#define UI_NEWSEARCHWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_NewSearchWindow
{
public:

    void setupUi(QDialog *NewSearchWindow)
    {
        if (NewSearchWindow->objectName().isEmpty())
            NewSearchWindow->setObjectName("NewSearchWindow");
        NewSearchWindow->resize(400, 300);

        retranslateUi(NewSearchWindow);

        QMetaObject::connectSlotsByName(NewSearchWindow);
    } // setupUi

    void retranslateUi(QDialog *NewSearchWindow)
    {
        NewSearchWindow->setWindowTitle(QCoreApplication::translate("NewSearchWindow", "NewSearchWindow", nullptr));
    } // retranslateUi

};

namespace Ui {
    class NewSearchWindow: public Ui_NewSearchWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NEWSEARCHWINDOW_H
