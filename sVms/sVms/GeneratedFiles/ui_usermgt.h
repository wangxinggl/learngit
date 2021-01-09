/********************************************************************************
** Form generated from reading UI file 'usermgt.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERMGT_H
#define UI_USERMGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserMgt
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnAdd;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnModify;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btnDel;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_4;
    QLineEdit *lineEdit;
    QTableView *tableView;

    void setupUi(QWidget *UserMgt)
    {
        if (UserMgt->objectName().isEmpty())
            UserMgt->setObjectName(QStringLiteral("UserMgt"));
        UserMgt->resize(694, 369);
        gridLayout = new QGridLayout(UserMgt);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(UserMgt);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setFamily(QString::fromUtf8("\346\226\260\345\256\213\344\275\223"));
        font.setPointSize(12);
        font.setBold(false);
        font.setWeight(50);
        label->setFont(font);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnAdd = new QPushButton(UserMgt);
        btnAdd->setObjectName(QStringLiteral("btnAdd"));
        btnAdd->setMinimumSize(QSize(0, 30));
        QIcon icon;
        icon.addFile(QStringLiteral(":/res/SoftIcon/add.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnAdd->setIcon(icon);
        btnAdd->setIconSize(QSize(25, 25));

        horizontalLayout->addWidget(btnAdd);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        btnModify = new QPushButton(UserMgt);
        btnModify->setObjectName(QStringLiteral("btnModify"));
        btnModify->setMinimumSize(QSize(0, 30));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/res/SoftIcon/mod.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnModify->setIcon(icon1);
        btnModify->setIconSize(QSize(25, 25));

        horizontalLayout->addWidget(btnModify);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        btnDel = new QPushButton(UserMgt);
        btnDel->setObjectName(QStringLiteral("btnDel"));
        btnDel->setEnabled(true);
        btnDel->setMinimumSize(QSize(0, 30));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/res/SoftIcon/Cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnDel->setIcon(icon2);
        btnDel->setIconSize(QSize(25, 25));

        horizontalLayout->addWidget(btnDel);


        gridLayout->addLayout(horizontalLayout, 0, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        lineEdit = new QLineEdit(UserMgt);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setMinimumSize(QSize(0, 30));

        horizontalLayout_2->addWidget(lineEdit);


        gridLayout->addLayout(horizontalLayout_2, 0, 2, 1, 1);

        tableView = new QTableView(UserMgt);
        tableView->setObjectName(QStringLiteral("tableView"));

        gridLayout->addWidget(tableView, 1, 0, 1, 3);


        retranslateUi(UserMgt);

        QMetaObject::connectSlotsByName(UserMgt);
    } // setupUi

    void retranslateUi(QWidget *UserMgt)
    {
        UserMgt->setWindowTitle(QApplication::translate("UserMgt", "UserMgt", Q_NULLPTR));
        label->setText(QApplication::translate("UserMgt", "\347\224\250\346\210\267\345\210\227\350\241\250", Q_NULLPTR));
        btnAdd->setText(QApplication::translate("UserMgt", "\346\267\273\345\212\240\347\224\250\346\210\267", Q_NULLPTR));
        btnModify->setText(QApplication::translate("UserMgt", "\344\277\256\346\224\271\347\224\250\346\210\267", Q_NULLPTR));
        btnDel->setText(QApplication::translate("UserMgt", "\345\210\240\351\231\244\347\224\250\346\210\267", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class UserMgt: public Ui_UserMgt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERMGT_H
