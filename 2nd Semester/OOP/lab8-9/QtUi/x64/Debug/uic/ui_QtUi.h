/********************************************************************************
** Form generated from reading UI file 'QtUi.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QTUI_H
#define UI_QTUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QtUiClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QtUiClass)
    {
        if (QtUiClass->objectName().isEmpty())
            QtUiClass->setObjectName("QtUiClass");
        QtUiClass->resize(600, 400);
        menuBar = new QMenuBar(QtUiClass);
        menuBar->setObjectName("menuBar");
        QtUiClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QtUiClass);
        mainToolBar->setObjectName("mainToolBar");
        QtUiClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(QtUiClass);
        centralWidget->setObjectName("centralWidget");
        QtUiClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(QtUiClass);
        statusBar->setObjectName("statusBar");
        QtUiClass->setStatusBar(statusBar);

        retranslateUi(QtUiClass);

        QMetaObject::connectSlotsByName(QtUiClass);
    } // setupUi

    void retranslateUi(QMainWindow *QtUiClass)
    {
        QtUiClass->setWindowTitle(QCoreApplication::translate("QtUiClass", "QtUi", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QtUiClass: public Ui_QtUiClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QTUI_H
