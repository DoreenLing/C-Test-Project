/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QLabel *labelimage;
    QLabel *label_edge;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QPushButton *pushButton_checkSex;
    QPushButton *pushButton_Openfile;
    QLabel *label_model;
    QComboBox *comboBox_checkSex;
    QLabel *label_next;
    QPushButton *pushButton_NextImage;
    QLabel *label_check;
    QLabel *label_open;
    QWidget *gridLayoutWidget_2;
    QGridLayout *gridLayout_2;
    QLabel *label_show;
    QTextBrowser *textBrowser_Sex;
    QTextBrowser *textBrowser_2;
    QLabel *label_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(666, 660);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        labelimage = new QLabel(centralWidget);
        labelimage->setObjectName(QStringLiteral("labelimage"));
        labelimage->setGeometry(QRect(25, 34, 451, 611));
        label_edge = new QLabel(centralWidget);
        label_edge->setObjectName(QStringLiteral("label_edge"));
        label_edge->setGeometry(QRect(480, 30, 141, 611));
        gridLayoutWidget = new QWidget(centralWidget);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(490, 40, 121, 141));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_checkSex = new QPushButton(gridLayoutWidget);
        pushButton_checkSex->setObjectName(QStringLiteral("pushButton_checkSex"));
        QFont font;
        font.setFamily(QStringLiteral("Aharoni"));
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        pushButton_checkSex->setFont(font);

        gridLayout->addWidget(pushButton_checkSex, 3, 1, 1, 1);

        pushButton_Openfile = new QPushButton(gridLayoutWidget);
        pushButton_Openfile->setObjectName(QStringLiteral("pushButton_Openfile"));
        pushButton_Openfile->setFont(font);

        gridLayout->addWidget(pushButton_Openfile, 0, 1, 1, 1);

        label_model = new QLabel(gridLayoutWidget);
        label_model->setObjectName(QStringLiteral("label_model"));
        label_model->setFont(font);

        gridLayout->addWidget(label_model, 2, 0, 1, 1);

        comboBox_checkSex = new QComboBox(gridLayoutWidget);
        comboBox_checkSex->addItem(QString());
        comboBox_checkSex->addItem(QString());
        comboBox_checkSex->addItem(QString());
        comboBox_checkSex->addItem(QString());
        comboBox_checkSex->setObjectName(QStringLiteral("comboBox_checkSex"));
        comboBox_checkSex->setFont(font);

        gridLayout->addWidget(comboBox_checkSex, 2, 1, 1, 1);

        label_next = new QLabel(gridLayoutWidget);
        label_next->setObjectName(QStringLiteral("label_next"));
        label_next->setFont(font);

        gridLayout->addWidget(label_next, 1, 0, 1, 1);

        pushButton_NextImage = new QPushButton(gridLayoutWidget);
        pushButton_NextImage->setObjectName(QStringLiteral("pushButton_NextImage"));
        pushButton_NextImage->setFont(font);

        gridLayout->addWidget(pushButton_NextImage, 1, 1, 1, 1);

        label_check = new QLabel(gridLayoutWidget);
        label_check->setObjectName(QStringLiteral("label_check"));

        gridLayout->addWidget(label_check, 3, 0, 1, 1);

        label_open = new QLabel(gridLayoutWidget);
        label_open->setObjectName(QStringLiteral("label_open"));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial Black"));
        font1.setPointSize(10);
        font1.setBold(true);
        font1.setWeight(75);
        label_open->setFont(font1);

        gridLayout->addWidget(label_open, 0, 0, 1, 1);

        gridLayoutWidget_2 = new QWidget(centralWidget);
        gridLayoutWidget_2->setObjectName(QStringLiteral("gridLayoutWidget_2"));
        gridLayoutWidget_2->setGeometry(QRect(490, 210, 121, 81));
        gridLayout_2 = new QGridLayout(gridLayoutWidget_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        label_show = new QLabel(gridLayoutWidget_2);
        label_show->setObjectName(QStringLiteral("label_show"));
        label_show->setFont(font);

        gridLayout_2->addWidget(label_show, 0, 0, 1, 1);

        textBrowser_Sex = new QTextBrowser(gridLayoutWidget_2);
        textBrowser_Sex->setObjectName(QStringLiteral("textBrowser_Sex"));
        QFont font2;
        font2.setFamily(QStringLiteral("MS PMincho"));
        font2.setPointSize(10);
        textBrowser_Sex->setFont(font2);

        gridLayout_2->addWidget(textBrowser_Sex, 0, 1, 1, 1);

        textBrowser_2 = new QTextBrowser(gridLayoutWidget_2);
        textBrowser_2->setObjectName(QStringLiteral("textBrowser_2"));

        gridLayout_2->addWidget(textBrowser_2, 1, 1, 1, 1);

        label_2 = new QLabel(gridLayoutWidget_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setFont(font);

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        label_edge->raise();
        labelimage->raise();
        gridLayoutWidget->raise();
        gridLayoutWidget_2->raise();
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 666, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        labelimage->setText(QApplication::translate("MainWindow", "Labelimage", nullptr));
        label_edge->setText(QString());
        pushButton_checkSex->setText(QApplication::translate("MainWindow", "checkSex", nullptr));
        pushButton_Openfile->setText(QApplication::translate("MainWindow", "OpenFile", nullptr));
        label_model->setText(QApplication::translate("MainWindow", "MODEL", nullptr));
        comboBox_checkSex->setItemText(0, QApplication::translate("MainWindow", "PCA", nullptr));
        comboBox_checkSex->setItemText(1, QApplication::translate("MainWindow", "LBP", nullptr));
        comboBox_checkSex->setItemText(2, QApplication::translate("MainWindow", "Fisher", nullptr));
        comboBox_checkSex->setItemText(3, QApplication::translate("MainWindow", "SVM", nullptr));

        label_next->setText(QApplication::translate("MainWindow", "NEXT", nullptr));
        pushButton_NextImage->setText(QApplication::translate("MainWindow", "NextImage", nullptr));
        label_check->setText(QApplication::translate("MainWindow", "SHOWSEX", nullptr));
        label_open->setText(QApplication::translate("MainWindow", "OPEN", nullptr));
        label_show->setText(QApplication::translate("MainWindow", "showsex", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
