/********************************************************************************
** Form generated from reading UI file 'WindowLock.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOWLOCK_H
#define UI_WINDOWLOCK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_WindowLock
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QLabel *label_displayErr;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnSure;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *lineEdit_Password;
    QLabel *label_2;

    void setupUi(QDialog *WindowLock)
    {
        if (WindowLock->objectName().isEmpty())
            WindowLock->setObjectName(QStringLiteral("WindowLock"));
        WindowLock->resize(402, 160);
        gridLayout = new QGridLayout(WindowLock);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        label_displayErr = new QLabel(WindowLock);
        label_displayErr->setObjectName(QStringLiteral("label_displayErr"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_displayErr->sizePolicy().hasHeightForWidth());
        label_displayErr->setSizePolicy(sizePolicy);
        label_displayErr->setMinimumSize(QSize(330, 0));

        horizontalLayout->addWidget(label_displayErr);


        gridLayout->addLayout(horizontalLayout, 2, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(278, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        btnSure = new QPushButton(WindowLock);
        btnSure->setObjectName(QStringLiteral("btnSure"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/res/SoftIcon/check.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnSure->setIcon(icon);
        btnSure->setIconSize(QSize(20, 20));

        horizontalLayout_3->addWidget(btnSure);


        gridLayout->addLayout(horizontalLayout_3, 3, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(WindowLock);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(120, 0));

        horizontalLayout_2->addWidget(label);

        lineEdit_Password = new QLineEdit(WindowLock);
        lineEdit_Password->setObjectName(QStringLiteral("lineEdit_Password"));
        sizePolicy.setHeightForWidth(lineEdit_Password->sizePolicy().hasHeightForWidth());
        lineEdit_Password->setSizePolicy(sizePolicy);
        lineEdit_Password->setEchoMode(QLineEdit::Password);

        horizontalLayout_2->addWidget(lineEdit_Password);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 1);

        label_2 = new QLabel(WindowLock);
        label_2->setObjectName(QStringLiteral("label_2"));
        QFont font;
        font.setFamily(QStringLiteral("Arial"));
        font.setPointSize(12);
        label_2->setFont(font);

        gridLayout->addWidget(label_2, 0, 0, 1, 1);


        retranslateUi(WindowLock);

        QMetaObject::connectSlotsByName(WindowLock);
    } // setupUi

    void retranslateUi(QDialog *WindowLock)
    {
        WindowLock->setWindowTitle(QApplication::translate("WindowLock", "WindowLock", Q_NULLPTR));
        label_displayErr->setText(QString());
        btnSure->setText(QApplication::translate("WindowLock", "\347\241\256\345\256\232", Q_NULLPTR));
        label->setText(QApplication::translate("WindowLock", "\350\257\267\350\276\223\345\205\245\347\231\273\345\275\225\345\257\206\347\240\201\350\247\243\351\224\201", Q_NULLPTR));
        label_2->setText(QApplication::translate("WindowLock", "\347\231\273\345\275\225\350\247\243\351\224\201", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class WindowLock: public Ui_WindowLock {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOWLOCK_H
