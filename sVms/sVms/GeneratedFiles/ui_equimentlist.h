/********************************************************************************
** Form generated from reading UI file 'equimentlist.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EQUIMENTLIST_H
#define UI_EQUIMENTLIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_equimentList
{
public:
    QGridLayout *gridLayout_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnClose;
    QTreeWidget *treeWidget;

    void setupUi(QWidget *equimentList)
    {
        if (equimentList->objectName().isEmpty())
            equimentList->setObjectName(QStringLiteral("equimentList"));
        equimentList->resize(300, 600);
        equimentList->setMinimumSize(QSize(300, 600));
        equimentList->setMaximumSize(QSize(300, 600));
        gridLayout_2 = new QGridLayout(equimentList);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        scrollArea = new QScrollArea(equimentList);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 280, 580));
        gridLayout = new QGridLayout(scrollAreaWidgetContents);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(scrollAreaWidgetContents);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(16777215, 30));

        horizontalLayout->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnClose = new QPushButton(scrollAreaWidgetContents);
        btnClose->setObjectName(QStringLiteral("btnClose"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/Client/res/delete.ico"), QSize(), QIcon::Normal, QIcon::Off);
        btnClose->setIcon(icon);

        horizontalLayout->addWidget(btnClose);


        verticalLayout->addLayout(horizontalLayout);

        treeWidget = new QTreeWidget(scrollAreaWidgetContents);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));

        verticalLayout->addWidget(treeWidget);


        gridLayout->addLayout(verticalLayout, 0, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout_2->addWidget(scrollArea, 0, 0, 1, 1);


        retranslateUi(equimentList);

        QMetaObject::connectSlotsByName(equimentList);
    } // setupUi

    void retranslateUi(QWidget *equimentList)
    {
        equimentList->setWindowTitle(QApplication::translate("equimentList", "equimentList", Q_NULLPTR));
        label->setText(QApplication::translate("equimentList", "\350\256\276\345\244\207\347\256\241\347\220\206\344\270\255\345\277\203", Q_NULLPTR));
        btnClose->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class equimentList: public Ui_equimentList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EQUIMENTLIST_H
