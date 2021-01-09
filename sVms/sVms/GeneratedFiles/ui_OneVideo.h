/********************************************************************************
** Form generated from reading UI file 'OneVideo.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ONEVIDEO_H
#define UI_ONEVIDEO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OneVideo
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QLabel *m_displayScreen;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *OneVideo)
    {
        if (OneVideo->objectName().isEmpty())
            OneVideo->setObjectName(QStringLiteral("OneVideo"));
        OneVideo->resize(400, 300);
        centralWidget = new QWidget(OneVideo);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        m_displayScreen = new QLabel(centralWidget);
        m_displayScreen->setObjectName(QStringLiteral("m_displayScreen"));
        m_displayScreen->setStyleSheet(QStringLiteral(""));

        gridLayout->addWidget(m_displayScreen, 0, 0, 1, 1);

        OneVideo->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(OneVideo);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        OneVideo->setStatusBar(statusBar);

        retranslateUi(OneVideo);

        QMetaObject::connectSlotsByName(OneVideo);
    } // setupUi

    void retranslateUi(QMainWindow *OneVideo)
    {
        OneVideo->setWindowTitle(QApplication::translate("OneVideo", "OneVideo", Q_NULLPTR));
        m_displayScreen->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class OneVideo: public Ui_OneVideo {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ONEVIDEO_H
