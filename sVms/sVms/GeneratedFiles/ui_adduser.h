/********************************************************************************
** Form generated from reading UI file 'adduser.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDUSER_H
#define UI_ADDUSER_H

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

class Ui_addUser
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QLabel *label;
    QPushButton *btnClose;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QLineEdit *CustomerRePwd;
    QLabel *labUserPwd;
    QLabel *labUserPwd_2;
    QLabel *labUserName;
    QLineEdit *CustomerName;
    QLineEdit *CustomerPwd;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnOk;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnCancel;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *addUser)
    {
        if (addUser->objectName().isEmpty())
            addUser->setObjectName(QStringLiteral("addUser"));
        addUser->resize(538, 316);
        gridLayout_3 = new QGridLayout(addUser);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(-1, 0, -1, -1);
        groupBox_2 = new QGroupBox(addUser);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(10);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8("font: 10pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        btnClose = new QPushButton(groupBox_2);
        btnClose->setObjectName(QStringLiteral("btnClose"));
        btnClose->setMinimumSize(QSize(30, 30));
        btnClose->setMaximumSize(QSize(30, 30));
        QIcon icon;
        icon.addFile(QStringLiteral(":/res/SoftIcon/Cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnClose->setIcon(icon);
        btnClose->setIconSize(QSize(30, 30));

        gridLayout->addWidget(btnClose, 0, 1, 1, 1);

        groupBox = new QGroupBox(groupBox_2);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy);
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        CustomerRePwd = new QLineEdit(groupBox);
        CustomerRePwd->setObjectName(QStringLiteral("CustomerRePwd"));
        CustomerRePwd->setMinimumSize(QSize(0, 30));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font1.setPointSize(12);
        CustomerRePwd->setFont(font1);
        CustomerRePwd->setEchoMode(QLineEdit::Password);

        gridLayout_2->addWidget(CustomerRePwd, 2, 2, 1, 1);

        labUserPwd = new QLabel(groupBox);
        labUserPwd->setObjectName(QStringLiteral("labUserPwd"));
        labUserPwd->setFont(font1);

        gridLayout_2->addWidget(labUserPwd, 1, 0, 1, 1);

        labUserPwd_2 = new QLabel(groupBox);
        labUserPwd_2->setObjectName(QStringLiteral("labUserPwd_2"));
        labUserPwd_2->setFont(font1);

        gridLayout_2->addWidget(labUserPwd_2, 2, 0, 1, 2);

        labUserName = new QLabel(groupBox);
        labUserName->setObjectName(QStringLiteral("labUserName"));
        labUserName->setFont(font1);

        gridLayout_2->addWidget(labUserName, 0, 0, 1, 1);

        CustomerName = new QLineEdit(groupBox);
        CustomerName->setObjectName(QStringLiteral("CustomerName"));
        CustomerName->setMinimumSize(QSize(0, 30));
        CustomerName->setFont(font1);
        CustomerName->setEchoMode(QLineEdit::Normal);

        gridLayout_2->addWidget(CustomerName, 0, 2, 1, 1);

        CustomerPwd = new QLineEdit(groupBox);
        CustomerPwd->setObjectName(QStringLiteral("CustomerPwd"));
        CustomerPwd->setMinimumSize(QSize(0, 30));
        CustomerPwd->setFont(font1);
        CustomerPwd->setEchoMode(QLineEdit::Password);

        gridLayout_2->addWidget(CustomerPwd, 1, 2, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Maximum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);

        gridLayout_2->addWidget(label_2, 3, 1, 1, 2);


        gridLayout->addWidget(groupBox, 1, 0, 1, 2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnOk = new QPushButton(groupBox_2);
        btnOk->setObjectName(QStringLiteral("btnOk"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(btnOk->sizePolicy().hasHeightForWidth());
        btnOk->setSizePolicy(sizePolicy2);
        btnOk->setFont(font1);
        btnOk->setCursor(QCursor(Qt::OpenHandCursor));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/res/SoftIcon/check.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnOk->setIcon(icon1);
        btnOk->setIconSize(QSize(20, 20));

        horizontalLayout->addWidget(btnOk);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        btnCancel = new QPushButton(groupBox_2);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(btnCancel->sizePolicy().hasHeightForWidth());
        btnCancel->setSizePolicy(sizePolicy3);
        btnCancel->setFont(font1);
        btnCancel->setCursor(QCursor(Qt::OpenHandCursor));
        btnCancel->setIcon(icon);
        btnCancel->setIconSize(QSize(20, 20));

        horizontalLayout->addWidget(btnCancel);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        gridLayout->addLayout(horizontalLayout, 2, 0, 1, 2);


        gridLayout_3->addWidget(groupBox_2, 0, 0, 1, 1);


        retranslateUi(addUser);

        QMetaObject::connectSlotsByName(addUser);
    } // setupUi

    void retranslateUi(QWidget *addUser)
    {
        addUser->setWindowTitle(QApplication::translate("addUser", "addUser", Q_NULLPTR));
        groupBox_2->setTitle(QString());
        label->setText(QApplication::translate("addUser", "\347\224\250\346\210\267\346\263\250\345\206\214", Q_NULLPTR));
        btnClose->setText(QString());
        groupBox->setTitle(QString());
        CustomerRePwd->setPlaceholderText(QApplication::translate("addUser", "\350\257\267\345\206\215\346\254\241\350\276\223\345\205\245\345\257\206\347\240\201", Q_NULLPTR));
        labUserPwd->setText(QApplication::translate("addUser", "\345\257\206\347\240\201\357\274\232*", Q_NULLPTR));
        labUserPwd_2->setText(QApplication::translate("addUser", "\347\241\256\350\256\244\345\257\206\347\240\201\357\274\232*", Q_NULLPTR));
        labUserName->setText(QApplication::translate("addUser", "\347\224\250\346\210\267\345\220\215\357\274\232*   ", Q_NULLPTR));
        CustomerName->setPlaceholderText(QApplication::translate("addUser", "\350\257\267\350\276\223\345\205\245\347\224\250\346\210\267\345\220\215", Q_NULLPTR));
        CustomerPwd->setPlaceholderText(QApplication::translate("addUser", "\350\257\267\350\276\223\345\205\245\345\257\206\347\240\201", Q_NULLPTR));
        label_2->setText(QApplication::translate("addUser", "         (\345\257\206\347\240\201\345\217\257\344\273\245\346\230\2576~16\344\275\215\346\225\260\345\255\227\343\200\201\345\255\227\346\257\215\357\274\214\344\270\215\350\203\275\345\214\205\345\220\253\344\270\213\345\210\222\347\272\277\347\255\211\347\211\271\346\256\212\345\255\227\347\254\246)", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        btnOk->setToolTip(QApplication::translate("addUser", "\347\241\256\350\256\244\346\263\250\345\206\214", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        btnOk->setText(QApplication::translate("addUser", "\347\241\256\350\256\244", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        btnCancel->setToolTip(QApplication::translate("addUser", "<html><head/><body><p><br/></p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_WHATSTHIS
        btnCancel->setWhatsThis(QApplication::translate("addUser", "<html><head/><body><p><br/></p></body></html>", Q_NULLPTR));
#endif // QT_NO_WHATSTHIS
        btnCancel->setText(QApplication::translate("addUser", "\345\217\226\346\266\210", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class addUser: public Ui_addUser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDUSER_H
