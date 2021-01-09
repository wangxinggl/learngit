/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QComboBox *txtUserName;
    QLineEdit *txtUserPwd;
    QLabel *label;
    QCheckBox *checkBox_Pwd;
    QCheckBox *checkBox_Auto;
    QPushButton *btnresgister;
    QPushButton *btnLogin;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName(QStringLiteral("Login"));
        Login->resize(585, 473);
        Login->setStyleSheet(QStringLiteral(""));
        txtUserName = new QComboBox(Login);
        txtUserName->setObjectName(QStringLiteral("txtUserName"));
        txtUserName->setEnabled(true);
        txtUserName->setGeometry(QRect(170, 180, 261, 51));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(txtUserName->sizePolicy().hasHeightForWidth());
        txtUserName->setSizePolicy(sizePolicy);
        txtUserName->setMinimumSize(QSize(125, 25));
        txtUserName->setEditable(true);
        txtUserPwd = new QLineEdit(Login);
        txtUserPwd->setObjectName(QStringLiteral("txtUserPwd"));
        txtUserPwd->setGeometry(QRect(170, 240, 261, 51));
        txtUserPwd->setMinimumSize(QSize(125, 25));
        QFont font;
        font.setFamily(QString::fromUtf8("\346\245\267\344\275\223"));
        font.setPointSize(12);
        txtUserPwd->setFont(font);
        txtUserPwd->setEchoMode(QLineEdit::Password);
        txtUserPwd->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label = new QLabel(Login);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(0, 40, 581, 71));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setPointSize(24);
        label->setFont(font1);
        label->setMouseTracking(false);
        label->setStyleSheet(QLatin1String("QMainWindow{\n"
"	background-color: rgb(255, 254, 240);\n"
"	border-image: url(:/new/prefix1/back.jpg);\n"
"}\n"
" \n"
"QLineEdit{\n"
" \n"
"	border:2px solid#7b7b7b;\n"
"	border-radius:15px;\n"
"	background-color:#fffef0\n"
"}\n"
" \n"
"QPushButton{\n"
"	border:2px solid#7b7b7b;\n"
"	border-radius:15px;\n"
"	background-color:#6a92ff;\n"
"	font: 75 26pt \"Arial\";\n"
"}\n"
" \n"
"QPushButton:hover{\n"
"	background-color:#aa92ff\n"
"}\n"
"QPushButton:pressed{\n"
"	background-color:#FF90ff\n"
"}\n"
""));
        label->setAlignment(Qt::AlignCenter);
        checkBox_Pwd = new QCheckBox(Login);
        checkBox_Pwd->setObjectName(QStringLiteral("checkBox_Pwd"));
        checkBox_Pwd->setGeometry(QRect(160, 300, 161, 16));
        checkBox_Pwd->setTristate(false);
        checkBox_Auto = new QCheckBox(Login);
        checkBox_Auto->setObjectName(QStringLiteral("checkBox_Auto"));
        checkBox_Auto->setGeometry(QRect(380, 300, 160, 16));
        btnresgister = new QPushButton(Login);
        btnresgister->setObjectName(QStringLiteral("btnresgister"));
        btnresgister->setGeometry(QRect(330, 380, 160, 60));
        btnLogin = new QPushButton(Login);
        btnLogin->setObjectName(QStringLiteral("btnLogin"));
        btnLogin->setGeometry(QRect(100, 380, 160, 60));
        layoutWidget = new QWidget(Login);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 0, 581, 32));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QWidget *Login)
    {
        Login->setWindowTitle(QApplication::translate("Login", "Login", Q_NULLPTR));
        txtUserName->setCurrentText(QString());
#ifndef QT_NO_TOOLTIP
        txtUserPwd->setToolTip(QApplication::translate("Login", "\350\257\267\350\276\223\345\205\245\345\257\206\347\240\201", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        txtUserPwd->setText(QString());
        txtUserPwd->setPlaceholderText(QApplication::translate("Login", "\350\257\267\350\276\223\345\205\245\345\257\206\347\240\201", Q_NULLPTR));
        label->setText(QApplication::translate("Login", "sVMS2000", Q_NULLPTR));
        checkBox_Pwd->setText(QApplication::translate("Login", "\350\256\260\344\275\217\345\257\206\347\240\201", Q_NULLPTR));
        checkBox_Auto->setText(QApplication::translate("Login", "\350\207\252\345\212\250\347\231\273\345\275\225", Q_NULLPTR));
        btnresgister->setText(QApplication::translate("Login", "\345\217\226\346\266\210", Q_NULLPTR));
        btnLogin->setText(QApplication::translate("Login", "\347\231\273\345\275\225", Q_NULLPTR));
        label_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
