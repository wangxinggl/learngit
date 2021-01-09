/********************************************************************************
** Form generated from reading UI file 'equimentmgt.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EQUIMENTMGT_H
#define UI_EQUIMENTMGT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_equimentMgt
{
public:
    QGridLayout *gridLayout_2;
    QWidget *widget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QTreeWidget *treeWidget;
    QCheckBox *checkBox;
    QLabel *label_Display;
    QLineEdit *lineEdit_Search;
    QLabel *label_manage;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnaddEq;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnModify;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnRefresh;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *btnDel;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btnClear;
    QLabel *label_Displayonline;
    QSpacerItem *horizontalSpacer_7;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnSearch;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *btnAdd;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *btnAddall;
    QSpacerItem *horizontalSpacer_8;
    QLabel *label_4;
    QLineEdit *lineEdit_Usr;
    QLabel *label_5;
    QLineEdit *lineEdit_Pwd;
    QTableView *tableView_manage;
    QTableWidget *tableWidget_Eq;
    QSpacerItem *horizontalSpacer_9;

    void setupUi(QWidget *equimentMgt)
    {
        if (equimentMgt->objectName().isEmpty())
            equimentMgt->setObjectName(QStringLiteral("equimentMgt"));
        equimentMgt->resize(1034, 775);
        equimentMgt->setMinimumSize(QSize(854, 522));
        equimentMgt->setStyleSheet(QStringLiteral(""));
        gridLayout_2 = new QGridLayout(equimentMgt);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        widget = new QWidget(equimentMgt);
        widget->setObjectName(QStringLiteral("widget"));
        gridLayout = new QGridLayout(widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        treeWidget = new QTreeWidget(widget);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(treeWidget->sizePolicy().hasHeightForWidth());
        treeWidget->setSizePolicy(sizePolicy);
        treeWidget->setMaximumSize(QSize(350, 16777215));

        verticalLayout->addWidget(treeWidget);

        checkBox = new QCheckBox(widget);
        checkBox->setObjectName(QStringLiteral("checkBox"));

        verticalLayout->addWidget(checkBox);

        label_Display = new QLabel(widget);
        label_Display->setObjectName(QStringLiteral("label_Display"));
        label_Display->setMaximumSize(QSize(400, 30));

        verticalLayout->addWidget(label_Display);


        gridLayout->addLayout(verticalLayout, 1, 0, 1, 2);

        lineEdit_Search = new QLineEdit(widget);
        lineEdit_Search->setObjectName(QStringLiteral("lineEdit_Search"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEdit_Search->sizePolicy().hasHeightForWidth());
        lineEdit_Search->setSizePolicy(sizePolicy1);
        lineEdit_Search->setMaximumSize(QSize(300, 16777215));

        gridLayout->addWidget(lineEdit_Search, 0, 0, 1, 2);


        gridLayout_2->addWidget(widget, 0, 0, 6, 1);

        label_manage = new QLabel(equimentMgt);
        label_manage->setObjectName(QStringLiteral("label_manage"));
        label_manage->setFrameShape(QFrame::NoFrame);

        gridLayout_2->addWidget(label_manage, 0, 1, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        btnaddEq = new QPushButton(equimentMgt);
        btnaddEq->setObjectName(QStringLiteral("btnaddEq"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/res/SoftIcon/add.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnaddEq->setIcon(icon);
        btnaddEq->setIconSize(QSize(20, 20));

        horizontalLayout->addWidget(btnaddEq);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnModify = new QPushButton(equimentMgt);
        btnModify->setObjectName(QStringLiteral("btnModify"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/res/SoftIcon/mod.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnModify->setIcon(icon1);
        btnModify->setIconSize(QSize(20, 20));

        horizontalLayout->addWidget(btnModify);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        btnRefresh = new QPushButton(equimentMgt);
        btnRefresh->setObjectName(QStringLiteral("btnRefresh"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/res/SoftIcon/Refresh.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnRefresh->setIcon(icon2);
        btnRefresh->setIconSize(QSize(20, 20));

        horizontalLayout->addWidget(btnRefresh);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        btnDel = new QPushButton(equimentMgt);
        btnDel->setObjectName(QStringLiteral("btnDel"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/res/SoftIcon/Cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnDel->setIcon(icon3);
        btnDel->setIconSize(QSize(20, 20));

        horizontalLayout->addWidget(btnDel);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        btnClear = new QPushButton(equimentMgt);
        btnClear->setObjectName(QStringLiteral("btnClear"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/res/SoftIcon/Clear.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnClear->setIcon(icon4);
        btnClear->setIconSize(QSize(20, 20));

        horizontalLayout->addWidget(btnClear);


        gridLayout_2->addLayout(horizontalLayout, 1, 1, 1, 3);

        label_Displayonline = new QLabel(equimentMgt);
        label_Displayonline->setObjectName(QStringLiteral("label_Displayonline"));
        sizePolicy1.setHeightForWidth(label_Displayonline->sizePolicy().hasHeightForWidth());
        label_Displayonline->setSizePolicy(sizePolicy1);
        label_Displayonline->setMinimumSize(QSize(130, 0));
        label_Displayonline->setMaximumSize(QSize(16777215, 30));
        label_Displayonline->setFrameShape(QFrame::NoFrame);

        gridLayout_2->addWidget(label_Displayonline, 3, 1, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(452, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_7, 3, 2, 1, 2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        btnSearch = new QPushButton(equimentMgt);
        btnSearch->setObjectName(QStringLiteral("btnSearch"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/res/SoftIcon/search.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnSearch->setIcon(icon5);
        btnSearch->setIconSize(QSize(20, 20));

        horizontalLayout_2->addWidget(btnSearch);

        horizontalSpacer_5 = new QSpacerItem(21, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);

        btnAdd = new QPushButton(equimentMgt);
        btnAdd->setObjectName(QStringLiteral("btnAdd"));
        btnAdd->setIcon(icon);
        btnAdd->setIconSize(QSize(20, 20));

        horizontalLayout_2->addWidget(btnAdd);

        horizontalSpacer_6 = new QSpacerItem(20, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_6);

        btnAddall = new QPushButton(equimentMgt);
        btnAddall->setObjectName(QStringLiteral("btnAddall"));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/res/SoftIcon/AddAll.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnAddall->setIcon(icon6);
        btnAddall->setIconSize(QSize(20, 20));

        horizontalLayout_2->addWidget(btnAddall);

        horizontalSpacer_8 = new QSpacerItem(21, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_8);

        label_4 = new QLabel(equimentMgt);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_2->addWidget(label_4);

        lineEdit_Usr = new QLineEdit(equimentMgt);
        lineEdit_Usr->setObjectName(QStringLiteral("lineEdit_Usr"));

        horizontalLayout_2->addWidget(lineEdit_Usr);

        label_5 = new QLabel(equimentMgt);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_2->addWidget(label_5);

        lineEdit_Pwd = new QLineEdit(equimentMgt);
        lineEdit_Pwd->setObjectName(QStringLiteral("lineEdit_Pwd"));

        horizontalLayout_2->addWidget(lineEdit_Pwd);


        gridLayout_2->addLayout(horizontalLayout_2, 4, 1, 1, 3);

        tableView_manage = new QTableView(equimentMgt);
        tableView_manage->setObjectName(QStringLiteral("tableView_manage"));

        gridLayout_2->addWidget(tableView_manage, 2, 1, 1, 3);

        tableWidget_Eq = new QTableWidget(equimentMgt);
        tableWidget_Eq->setObjectName(QStringLiteral("tableWidget_Eq"));

        gridLayout_2->addWidget(tableWidget_Eq, 5, 1, 1, 3);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_9, 0, 2, 1, 1);


        retranslateUi(equimentMgt);

        QMetaObject::connectSlotsByName(equimentMgt);
    } // setupUi

    void retranslateUi(QWidget *equimentMgt)
    {
        equimentMgt->setWindowTitle(QApplication::translate("equimentMgt", "equimentMgt", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("equimentMgt", "\350\256\276\345\244\207\345\210\227\350\241\250", Q_NULLPTR));
        checkBox->setText(QApplication::translate("equimentMgt", "\346\257\217\351\232\22460\347\247\222\350\207\252\345\212\250\346\220\234\347\264\242", Q_NULLPTR));
        label_Display->setText(QApplication::translate("equimentMgt", "\345\217\257\344\273\245\346\267\273\345\212\240\347\232\204IPC\350\256\276\345\244\207", Q_NULLPTR));
        label_manage->setText(QString());
        btnaddEq->setText(QApplication::translate("equimentMgt", "\346\267\273\345\212\240", Q_NULLPTR));
        btnModify->setText(QApplication::translate("equimentMgt", "\344\277\256\346\224\271", Q_NULLPTR));
        btnRefresh->setText(QApplication::translate("equimentMgt", "\345\210\267\346\226\260", Q_NULLPTR));
        btnDel->setText(QApplication::translate("equimentMgt", "\345\210\240\351\231\244", Q_NULLPTR));
        btnClear->setText(QApplication::translate("equimentMgt", "\346\270\205\347\251\272", Q_NULLPTR));
        label_Displayonline->setText(QString());
        btnSearch->setText(QApplication::translate("equimentMgt", "\346\220\234\347\264\242", Q_NULLPTR));
        btnAdd->setText(QApplication::translate("equimentMgt", "\346\267\273\345\212\240\350\256\276\345\244\207", Q_NULLPTR));
        btnAddall->setText(QApplication::translate("equimentMgt", "\346\267\273\345\212\240\346\211\200\346\234\211\350\256\276\345\244\207", Q_NULLPTR));
        label_4->setText(QApplication::translate("equimentMgt", "\347\224\250\346\210\267\345\220\215", Q_NULLPTR));
        label_5->setText(QApplication::translate("equimentMgt", "\345\257\206\347\240\201", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class equimentMgt: public Ui_equimentMgt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EQUIMENTMGT_H
