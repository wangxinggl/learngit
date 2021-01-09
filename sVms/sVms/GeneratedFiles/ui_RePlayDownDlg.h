/********************************************************************************
** Form generated from reading UI file 'RePlayDownDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REPLAYDOWNDLG_H
#define UI_REPLAYDOWNDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_RePlayDownDlg
{
public:
    QGridLayout *gridLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnStop;
    QSpacerItem *horizontalSpacer_2;
    QLabel *display_Process;
    QProgressBar *progressBarDowned;

    void setupUi(QWidget *RePlayDownDlg)
    {
        if (RePlayDownDlg->objectName().isEmpty())
            RePlayDownDlg->setObjectName(QStringLiteral("RePlayDownDlg"));
        RePlayDownDlg->resize(494, 195);
        gridLayout = new QGridLayout(RePlayDownDlg);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalSpacer = new QSpacerItem(192, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 0, 1, 1);

        btnStop = new QPushButton(RePlayDownDlg);
        btnStop->setObjectName(QStringLiteral("btnStop"));

        gridLayout->addWidget(btnStop, 2, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(191, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 2, 2, 1, 1);

        display_Process = new QLabel(RePlayDownDlg);
        display_Process->setObjectName(QStringLiteral("display_Process"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(display_Process->sizePolicy().hasHeightForWidth());
        display_Process->setSizePolicy(sizePolicy);

        gridLayout->addWidget(display_Process, 0, 0, 1, 3);

        progressBarDowned = new QProgressBar(RePlayDownDlg);
        progressBarDowned->setObjectName(QStringLiteral("progressBarDowned"));
        progressBarDowned->setValue(0);

        gridLayout->addWidget(progressBarDowned, 1, 0, 1, 3);


        retranslateUi(RePlayDownDlg);

        QMetaObject::connectSlotsByName(RePlayDownDlg);
    } // setupUi

    void retranslateUi(QWidget *RePlayDownDlg)
    {
        RePlayDownDlg->setWindowTitle(QApplication::translate("RePlayDownDlg", "RePlayDownDlg", Q_NULLPTR));
        btnStop->setText(QApplication::translate("RePlayDownDlg", "\345\201\234\346\255\242\344\270\213\350\275\275", Q_NULLPTR));
        display_Process->setText(QApplication::translate("RePlayDownDlg", "\346\255\243\345\234\250\344\270\213\350\275\275\346\226\207\344\273\266...", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class RePlayDownDlg: public Ui_RePlayDownDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REPLAYDOWNDLG_H
