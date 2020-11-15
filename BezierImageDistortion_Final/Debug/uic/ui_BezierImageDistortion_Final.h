/********************************************************************************
** Form generated from reading UI file 'BezierImageDistortion_Final.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BEZIERIMAGEDISTORTION_FINAL_H
#define UI_BEZIERIMAGEDISTORTION_FINAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BezierImageDistortion_FinalClass
{
public:
    QAction *action_open_image;
    QAction *action_open_video;
    QAction *action_open_test_img;
    QWidget *centralWidget;
    QLabel *label_show;
    QLabel *label;
    QComboBox *comboBox_count;
    QComboBox *comboBox_oper;
    QSpinBox *spinBox_grid_x;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QSpinBox *spinBox_grid_y;
    QLabel *label_6;
    QLabel *label_7;
    QDoubleSpinBox *doubleSpinBox_bzRow;
    QDoubleSpinBox *doubleSpinBox_bzCol;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *BezierImageDistortion_FinalClass)
    {
        if (BezierImageDistortion_FinalClass->objectName().isEmpty())
            BezierImageDistortion_FinalClass->setObjectName(QString::fromUtf8("BezierImageDistortion_FinalClass"));
        BezierImageDistortion_FinalClass->resize(1000, 1033);
        BezierImageDistortion_FinalClass->setMinimumSize(QSize(1000, 1033));
        BezierImageDistortion_FinalClass->setMaximumSize(QSize(1000, 1033));
        action_open_image = new QAction(BezierImageDistortion_FinalClass);
        action_open_image->setObjectName(QString::fromUtf8("action_open_image"));
        action_open_video = new QAction(BezierImageDistortion_FinalClass);
        action_open_video->setObjectName(QString::fromUtf8("action_open_video"));
        action_open_test_img = new QAction(BezierImageDistortion_FinalClass);
        action_open_test_img->setObjectName(QString::fromUtf8("action_open_test_img"));
        centralWidget = new QWidget(BezierImageDistortion_FinalClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        label_show = new QLabel(centralWidget);
        label_show->setObjectName(QString::fromUtf8("label_show"));
        label_show->setGeometry(QRect(20, 0, 960, 720));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(14);
        font.setBold(true);
        font.setWeight(75);
        label_show->setFont(font);
        label_show->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        label_show->setFrameShape(QFrame::Box);
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 740, 111, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        label->setFont(font1);
        comboBox_count = new QComboBox(centralWidget);
        comboBox_count->setObjectName(QString::fromUtf8("comboBox_count"));
        comboBox_count->setGeometry(QRect(150, 750, 87, 31));
        comboBox_oper = new QComboBox(centralWidget);
        comboBox_oper->addItem(QString());
        comboBox_oper->addItem(QString());
        comboBox_oper->addItem(QString());
        comboBox_oper->addItem(QString());
        comboBox_oper->setObjectName(QString::fromUtf8("comboBox_oper"));
        comboBox_oper->setGeometry(QRect(730, 740, 87, 31));
        spinBox_grid_x = new QSpinBox(centralWidget);
        spinBox_grid_x->setObjectName(QString::fromUtf8("spinBox_grid_x"));
        spinBox_grid_x->setGeometry(QRect(410, 740, 71, 31));
        spinBox_grid_x->setMaximum(960);
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(650, 740, 51, 31));
        label_2->setFont(font1);
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(290, 740, 91, 41));
        label_3->setFont(font1);
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(480, 810, 31, 21));
        label_4->setFont(font1);
        label_5 = new QLabel(centralWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(500, 740, 21, 41));
        label_5->setFont(font1);
        spinBox_grid_y = new QSpinBox(centralWidget);
        spinBox_grid_y->setObjectName(QString::fromUtf8("spinBox_grid_y"));
        spinBox_grid_y->setGeometry(QRect(540, 740, 71, 31));
        spinBox_grid_y->setMaximum(720);
        label_6 = new QLabel(centralWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(20, 800, 451, 41));
        label_6->setFont(font1);
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(620, 810, 31, 21));
        label_7->setFont(font1);
        doubleSpinBox_bzRow = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_bzRow->setObjectName(QString::fromUtf8("doubleSpinBox_bzRow"));
        doubleSpinBox_bzRow->setGeometry(QRect(510, 801, 81, 31));
        doubleSpinBox_bzRow->setDecimals(4);
        doubleSpinBox_bzRow->setMaximum(1.000000000000000);
        doubleSpinBox_bzRow->setSingleStep(0.000100000000000);
        doubleSpinBox_bzRow->setValue(0.100000000000000);
        doubleSpinBox_bzCol = new QDoubleSpinBox(centralWidget);
        doubleSpinBox_bzCol->setObjectName(QString::fromUtf8("doubleSpinBox_bzCol"));
        doubleSpinBox_bzCol->setGeometry(QRect(660, 800, 81, 31));
        doubleSpinBox_bzCol->setDecimals(4);
        doubleSpinBox_bzCol->setMaximum(1.000000000000000);
        doubleSpinBox_bzCol->setSingleStep(0.000100000000000);
        doubleSpinBox_bzCol->setValue(0.100000000000000);
        BezierImageDistortion_FinalClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(BezierImageDistortion_FinalClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1000, 26));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        BezierImageDistortion_FinalClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(BezierImageDistortion_FinalClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        BezierImageDistortion_FinalClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(BezierImageDistortion_FinalClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        BezierImageDistortion_FinalClass->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(action_open_test_img);
        menu->addAction(action_open_image);
        menu->addAction(action_open_video);

        retranslateUi(BezierImageDistortion_FinalClass);

        QMetaObject::connectSlotsByName(BezierImageDistortion_FinalClass);
    } // setupUi

    void retranslateUi(QMainWindow *BezierImageDistortion_FinalClass)
    {
        BezierImageDistortion_FinalClass->setWindowTitle(QCoreApplication::translate("BezierImageDistortion_FinalClass", "BezierImageDistortion_Final", nullptr));
        action_open_image->setText(QCoreApplication::translate("BezierImageDistortion_FinalClass", "\346\211\223\345\274\200\345\233\276\347\211\207", nullptr));
        action_open_video->setText(QCoreApplication::translate("BezierImageDistortion_FinalClass", "\346\211\223\345\274\200\350\247\206\351\242\221", nullptr));
        action_open_test_img->setText(QCoreApplication::translate("BezierImageDistortion_FinalClass", "\346\265\213\350\257\225\345\233\276\347\211\207", nullptr));
        label_show->setText(QCoreApplication::translate("BezierImageDistortion_FinalClass", "Image/Video SHOW", nullptr));
        label->setText(QCoreApplication::translate("BezierImageDistortion_FinalClass", "\346\240\274\345\255\220\346\225\260(NxN):", nullptr));
        comboBox_oper->setItemText(0, QCoreApplication::translate("BezierImageDistortion_FinalClass", "\351\200\217\350\247\206\345\217\230\346\215\242", nullptr));
        comboBox_oper->setItemText(1, QCoreApplication::translate("BezierImageDistortion_FinalClass", "\344\270\215\350\247\204\345\210\231\345\214\272\345\237\237", nullptr));
        comboBox_oper->setItemText(2, QCoreApplication::translate("BezierImageDistortion_FinalClass", "\347\237\253\346\255\243", nullptr));
        comboBox_oper->setItemText(3, QCoreApplication::translate("BezierImageDistortion_FinalClass", "Bezier\346\213\211\344\274\270", nullptr));

        label_2->setText(QCoreApplication::translate("BezierImageDistortion_FinalClass", "\346\223\215\344\275\234\357\274\232", nullptr));
        label_3->setText(QCoreApplication::translate("BezierImageDistortion_FinalClass", "\347\275\221\346\240\274\345\271\263\347\247\273:", nullptr));
        label_4->setText(QCoreApplication::translate("BezierImageDistortion_FinalClass", "\350\241\214\357\274\232", nullptr));
        label_5->setText(QCoreApplication::translate("BezierImageDistortion_FinalClass", "Y:", nullptr));
        label_6->setText(QCoreApplication::translate("BezierImageDistortion_FinalClass", "\346\233\262\347\272\277\344\270\212\347\232\204\350\277\236\346\216\245\347\202\271\344\270\252\346\225\260(\345\244\232\347\202\271\350\277\236\346\216\245\346\233\262\347\272\277\357\274\214\345\200\274\350\266\212\345\260\217\357\274\214\351\224\257\351\275\277\350\266\212\344\270\245\351\207\215)\357\274\232", nullptr));
        label_7->setText(QCoreApplication::translate("BezierImageDistortion_FinalClass", "\345\210\227\357\274\232", nullptr));
        menu->setTitle(QCoreApplication::translate("BezierImageDistortion_FinalClass", "\346\226\207\344\273\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BezierImageDistortion_FinalClass: public Ui_BezierImageDistortion_FinalClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BEZIERIMAGEDISTORTION_FINAL_H
