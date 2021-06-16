/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QLabel *calclabel;
    QPushButton *calcButton;
    QLineEdit *numberEdit;
    QPushButton *saveButton;
    QCustomPlot *plot;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        calclabel = new QLabel(centralwidget);
        calclabel->setObjectName(QStringLiteral("calclabel"));

        gridLayout->addWidget(calclabel, 1, 0, 1, 1);

        calcButton = new QPushButton(centralwidget);
        calcButton->setObjectName(QStringLiteral("calcButton"));

        gridLayout->addWidget(calcButton, 1, 2, 1, 1);

        numberEdit = new QLineEdit(centralwidget);
        numberEdit->setObjectName(QStringLiteral("numberEdit"));
        numberEdit->setClearButtonEnabled(false);

        gridLayout->addWidget(numberEdit, 1, 1, 1, 1);

        saveButton = new QPushButton(centralwidget);
        saveButton->setObjectName(QStringLiteral("saveButton"));
        saveButton->setEnabled(false);
        saveButton->setCheckable(false);

        gridLayout->addWidget(saveButton, 3, 2, 1, 1);

        plot = new QCustomPlot(centralwidget);
        plot->setObjectName(QStringLiteral("plot"));

        gridLayout->addWidget(plot, 0, 0, 1, 3);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 20));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        calclabel->setText(QApplication::translate("MainWindow", "Input number of points:", Q_NULLPTR));
        calcButton->setText(QApplication::translate("MainWindow", "Calculate", Q_NULLPTR));
        numberEdit->setText(QApplication::translate("MainWindow", "500", Q_NULLPTR));
        saveButton->setText(QApplication::translate("MainWindow", "Save", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
