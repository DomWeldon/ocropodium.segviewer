/********************************************************************************
** Form generated from reading UI file 'segviewer.ui'
**
** Created: Tue Mar 16 13:16:40 2010
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEGVIEWER_H
#define UI_SEGVIEWER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SegViewer
{
public:
    QAction *actionZoom_In;
    QAction *actionZoom_Out;
    QAction *actionNormal_Size;
    QAction *actionFit_to_Window;
    QAction *actionOpen;
    QAction *actionQuit;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QMenu *menuView;
    QMenu *menuSegment;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SegViewer)
    {
        if (SegViewer->objectName().isEmpty())
            SegViewer->setObjectName(QString::fromUtf8("SegViewer"));
        SegViewer->resize(600, 400);
        actionZoom_In = new QAction(SegViewer);
        actionZoom_In->setObjectName(QString::fromUtf8("actionZoom_In"));
        actionZoom_In->setCheckable(false);
        actionZoom_Out = new QAction(SegViewer);
        actionZoom_Out->setObjectName(QString::fromUtf8("actionZoom_Out"));
        actionNormal_Size = new QAction(SegViewer);
        actionNormal_Size->setObjectName(QString::fromUtf8("actionNormal_Size"));
        actionFit_to_Window = new QAction(SegViewer);
        actionFit_to_Window->setObjectName(QString::fromUtf8("actionFit_to_Window"));
        actionFit_to_Window->setCheckable(true);
        actionFit_to_Window->setChecked(true);
        actionFit_to_Window->setEnabled(true);
        actionOpen = new QAction(SegViewer);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionQuit = new QAction(SegViewer);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        centralWidget = new QWidget(SegViewer);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        SegViewer->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(SegViewer);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 25));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        menuSegment = new QMenu(menuBar);
        menuSegment->setObjectName(QString::fromUtf8("menuSegment"));
        SegViewer->setMenuBar(menuBar);
        statusBar = new QStatusBar(SegViewer);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        SegViewer->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuSegment->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addSeparator();
        menuFile->addAction(actionQuit);
        menuView->addAction(actionZoom_In);
        menuView->addAction(actionZoom_Out);
        menuView->addAction(actionNormal_Size);
        menuView->addAction(actionFit_to_Window);

        retranslateUi(SegViewer);
        QObject::connect(actionQuit, SIGNAL(triggered()), SegViewer, SLOT(close()));

        QMetaObject::connectSlotsByName(SegViewer);
    } // setupUi

    void retranslateUi(QMainWindow *SegViewer)
    {
        SegViewer->setWindowTitle(QApplication::translate("SegViewer", "SegViewer", 0, QApplication::UnicodeUTF8));
        actionZoom_In->setText(QApplication::translate("SegViewer", "Zoom In", 0, QApplication::UnicodeUTF8));
        actionZoom_In->setShortcut(QApplication::translate("SegViewer", "=", 0, QApplication::UnicodeUTF8));
        actionZoom_Out->setText(QApplication::translate("SegViewer", "Zoom Out", 0, QApplication::UnicodeUTF8));
        actionZoom_Out->setShortcut(QApplication::translate("SegViewer", "-", 0, QApplication::UnicodeUTF8));
        actionNormal_Size->setText(QApplication::translate("SegViewer", "Normal Size", 0, QApplication::UnicodeUTF8));
        actionFit_to_Window->setText(QApplication::translate("SegViewer", "Fit to Window", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("SegViewer", "Open image...", 0, QApplication::UnicodeUTF8));
        actionOpen->setShortcut(QApplication::translate("SegViewer", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        actionQuit->setText(QApplication::translate("SegViewer", "Quit", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("SegViewer", "File", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("SegViewer", "Help", 0, QApplication::UnicodeUTF8));
        menuView->setTitle(QApplication::translate("SegViewer", "View", 0, QApplication::UnicodeUTF8));
        menuSegment->setTitle(QApplication::translate("SegViewer", "Segmenter", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SegViewer: public Ui_SegViewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEGVIEWER_H
