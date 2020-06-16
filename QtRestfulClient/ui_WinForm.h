/********************************************************************************
** Form generated from reading UI file 'WinForm.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINFORM_H
#define UI_WINFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WinForm
{
public:
    QWidget *centralWidget;

    void setupUi(QMainWindow *WinForm)
    {
        if (WinForm->objectName().isEmpty())
            WinForm->setObjectName(QStringLiteral("WinForm"));
        WinForm->resize(400, 300);
        centralWidget = new QWidget(WinForm);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        WinForm->setCentralWidget(centralWidget);

        retranslateUi(WinForm);

        QMetaObject::connectSlotsByName(WinForm);
    } // setupUi

    void retranslateUi(QMainWindow *WinForm)
    {
        WinForm->setWindowTitle(QApplication::translate("WinForm", "WinForm", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class WinForm: public Ui_WinForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINFORM_H
