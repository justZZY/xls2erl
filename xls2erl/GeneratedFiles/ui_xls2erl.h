/********************************************************************************
** Form generated from reading UI file 'xls2erl.ui'
**
** Created by: Qt User Interface Compiler version 5.12.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_XLS2ERL_H
#define UI_XLS2ERL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

QT_BEGIN_NAMESPACE

class Ui_xls2erlClass
{
public:

    void setupUi(QDialog *xls2erlClass)
    {
        if (xls2erlClass->objectName().isEmpty())
            xls2erlClass->setObjectName(QString::fromUtf8("xls2erlClass"));
        xls2erlClass->resize(600, 400);

        retranslateUi(xls2erlClass);

        QMetaObject::connectSlotsByName(xls2erlClass);
    } // setupUi

    void retranslateUi(QDialog *xls2erlClass)
    {
        xls2erlClass->setWindowTitle(QApplication::translate("xls2erlClass", "xls2erl", nullptr));
    } // retranslateUi

};

namespace Ui {
    class xls2erlClass: public Ui_xls2erlClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_XLS2ERL_H
