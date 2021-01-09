/********************************************************************************
** Form generated from reading UI file 'modifyuser.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MODIFYUSER_H
#define UI_MODIFYUSER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_modifyUser
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QPushButton *btnClose;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLabel *label_3;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLineEdit *lineEditOldPed;
    QLabel *label_6;
    QLineEdit *lineEditNewPwd;
    QLabel *label_7;
    QLineEdit *lineEditReNewPwd;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnSure;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnCancel;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *modifyUser)
    {
        if (modifyUser->objectName().isEmpty())
            modifyUser->setObjectName(QStringLiteral("modifyUser"));
        modifyUser->resize(550, 300);
        gridLayout_3 = new QGridLayout(modifyUser);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(-1, 0, -1, -1);
        groupBox_2 = new QGroupBox(modifyUser);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        QFont font;
        font.setFamily(QStringLiteral("Microsoft YaHei"));
        font.setPointSize(12);
        label_4->setFont(font);

        horizontalLayout_2->addWidget(label_4);

        btnClose = new QPushButton(groupBox_2);
        btnClose->setObjectName(QStringLiteral("btnClose"));
        btnClose->setMinimumSize(QSize(30, 30));
        btnClose->setMaximumSize(QSize(30, 30));
        QIcon icon;
        icon.addFile(QStringLiteral(":/res/SoftIcon/Cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnClose->setIcon(icon);
        btnClose->setIconSize(QSize(30, 30));

        horizontalLayout_2->addWidget(btnClose);


        gridLayout_2->addLayout(horizontalLayout_2, 0, 0, 1, 1);

        groupBox = new QGroupBox(groupBox_2);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 0, 0, 1, 1);

        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setEnabled(false);
        lineEdit->setMinimumSize(QSize(0, 30));

        gridLayout->addWidget(lineEdit, 0, 1, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        lineEditOldPed = new QLineEdit(groupBox);
        lineEditOldPed->setObjectName(QStringLiteral("lineEditOldPed"));
        lineEditOldPed->setMinimumSize(QSize(0, 30));
        lineEditOldPed->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(lineEditOldPed, 1, 1, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout->addWidget(label_6, 2, 0, 1, 1);

        lineEditNewPwd = new QLineEdit(groupBox);
        lineEditNewPwd->setObjectName(QStringLiteral("lineEditNewPwd"));
        lineEditNewPwd->setMinimumSize(QSize(0, 30));
        lineEditNewPwd->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(lineEditNewPwd, 2, 1, 1, 1);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout->addWidget(label_7, 3, 0, 1, 1);

        lineEditReNewPwd = new QLineEdit(groupBox);
        lineEditReNewPwd->setObjectName(QStringLiteral("lineEditReNewPwd"));
        lineEditReNewPwd->setMinimumSize(QSize(0, 30));
        lineEditReNewPwd->setEchoMode(QLineEdit::Password);

        gridLayout->addWidget(lineEditReNewPwd, 3, 1, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label, 4, 0, 1, 2);


        gridLayout_2->addWidget(groupBox, 1, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnSure = new QPushButton(groupBox_2);
        btnSure->setObjectName(QStringLiteral("btnSure"));
        btnSure->setMinimumSize(QSize(0, 30));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/res/SoftIcon/check.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnSure->setIcon(icon1);
        btnSure->setIconSize(QSize(20, 20));

        horizontalLayout->addWidget(btnSure);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        btnCancel = new QPushButton(groupBox_2);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));
        btnCancel->setMinimumSize(QSize(0, 30));
        btnCancel->setIcon(icon);
        btnCancel->setIconSize(QSize(20, 20));

        horizontalLayout->addWidget(btnCancel);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        gridLayout_2->addLayout(horizontalLayout, 2, 0, 1, 1);


        gridLayout_3->addWidget(groupBox_2, 0, 0, 1, 1);


        retranslateUi(modifyUser);

        QMetaObject::connectSlotsByName(modifyUser);
    } // setupUi

    void retranslateUi(QWidget *modifyUser)
    {
        modifyUser->setWindowTitle(QApplication::translate("modifyUser", "modifyUser", Q_NULLPTR));
        groupBox_2->setTitle(QString());
        label_4->setText(QApplication::translate("modifyUser", "\344\277\256\346\224\271\347\224\250\346\210\267", Q_NULLPTR));
        btnClose->setText(QString());
        groupBox->setTitle(QString());
        label_3->setText(QApplication::translate("modifyUser", "\347\224\250\346\210\267\345\220\215\357\274\232", Q_NULLPTR));
        lineEdit->setPlaceholderText(QApplication::translate("modifyUser", "\350\257\267\350\276\223\345\205\245\347\224\250\346\210\267\345\220\215", Q_NULLPTR));
        label_2->setText(QApplication::translate("modifyUser", "\346\227\247\345\257\206\347\240\201 \357\274\232", Q_NULLPTR));
        lineEditOldPed->setPlaceholderText(QApplication::translate("modifyUser", "\350\257\267\350\276\223\345\205\245\346\227\247\345\257\206\347\240\201", Q_NULLPTR));
        label_6->setText(QApplication::translate("modifyUser", "\346\226\260\345\257\206\347\240\201\357\274\232", Q_NULLPTR));
        lineEditNewPwd->setPlaceholderText(QApplication::translate("modifyUser", "\350\276\223\345\205\245\346\226\260\345\257\206\347\240\201", Q_NULLPTR));
        label_7->setText(QApplication::translate("modifyUser", "\347\241\256\350\256\244\345\257\206\347\240\201\357\274\232", Q_NULLPTR));
        lineEditReNewPwd->setPlaceholderText(QApplication::translate("modifyUser", "\350\257\267\345\206\215\346\254\241\350\276\223\345\205\245\346\226\260\345\257\206\347\240\201", Q_NULLPTR));
        label->setText(QApplication::translate("modifyUser", "         (\345\257\206\347\240\201\345\217\257\344\273\245\346\230\2576~16\344\275\215\346\225\260\345\255\227\343\200\201\345\255\227\346\257\215\357\274\214\344\270\215\350\203\275\345\214\205\345\220\253\344\270\213\345\210\222\347\272\277\347\255\211\347\211\271\346\256\212\345\255\227\347\254\246)", Q_NULLPTR));
        btnSure->setText(QApplication::translate("modifyUser", "\347\241\256\345\256\232", Q_NULLPTR));
        btnCancel->setText(QApplication::translate("modifyUser", "\345\217\226\346\266\210", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class modifyUser: public Ui_modifyUser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MODIFYUSER_H
