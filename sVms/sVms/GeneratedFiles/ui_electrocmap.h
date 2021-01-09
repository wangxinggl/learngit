/********************************************************************************
** Form generated from reading UI file 'electrocmap.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ELECTROCMAP_H
#define UI_ELECTROCMAP_H

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
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_electrocMap
{
public:
    QGridLayout *gridLayout_3;
    QTreeWidget *treeWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_9;
    QLabel *label_10;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QLineEdit *lineEdit_3;
    QToolButton *toolButton;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_4;
    QLineEdit *lineEdit_4;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_5;
    QLineEdit *lineEdit_5;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_6;
    QLineEdit *lineEdit_6;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_7;
    QLineEdit *lineEdit_7;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_8;
    QLineEdit *lineEdit_8;
    QHBoxLayout *horizontalLayout_10;
    QPushButton *pushButton_4;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton_5;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pushButton_6;

    void setupUi(QWidget *electrocMap)
    {
        if (electrocMap->objectName().isEmpty())
            electrocMap->setObjectName(QStringLiteral("electrocMap"));
        electrocMap->resize(1010, 693);
        gridLayout_3 = new QGridLayout(electrocMap);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        treeWidget = new QTreeWidget(electrocMap);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(treeWidget->sizePolicy().hasHeightForWidth());
        treeWidget->setSizePolicy(sizePolicy);
        treeWidget->setMaximumSize(QSize(250, 16777215));

        gridLayout_3->addWidget(treeWidget, 0, 0, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMaximumSize);
        label_9 = new QLabel(electrocMap);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setMaximumSize(QSize(16777215, 30));

        verticalLayout->addWidget(label_9);

        label_10 = new QLabel(electrocMap);
        label_10->setObjectName(QStringLiteral("label_10"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy1);
        label_10->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));

        verticalLayout->addWidget(label_10);


        gridLayout_3->addLayout(verticalLayout, 0, 1, 3, 1);

        groupBox = new QGroupBox(electrocMap);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy2);
        groupBox->setMaximumSize(QSize(250, 16777215));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(50, 16777215));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(groupBox);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy3);

        horizontalLayout->addWidget(lineEdit);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_3->addWidget(label_3);

        lineEdit_3 = new QLineEdit(groupBox);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));
        sizePolicy3.setHeightForWidth(lineEdit_3->sizePolicy().hasHeightForWidth());
        lineEdit_3->setSizePolicy(sizePolicy3);

        horizontalLayout_3->addWidget(lineEdit_3);

        toolButton = new QToolButton(groupBox);
        toolButton->setObjectName(QStringLiteral("toolButton"));

        horizontalLayout_3->addWidget(toolButton);


        gridLayout->addLayout(horizontalLayout_3, 2, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/res/SoftIcon/add.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton->setIcon(icon);
        pushButton->setIconSize(QSize(20, 20));

        horizontalLayout_4->addWidget(pushButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        pushButton_2 = new QPushButton(groupBox);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/res/SoftIcon/Save.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_2->setIcon(icon1);

        horizontalLayout_4->addWidget(pushButton_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        pushButton_3 = new QPushButton(groupBox);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/res/SoftIcon/Cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_3->setIcon(icon2);

        horizontalLayout_4->addWidget(pushButton_3);


        gridLayout->addLayout(horizontalLayout_4, 3, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_2->addWidget(label_2);

        lineEdit_2 = new QLineEdit(groupBox);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));
        sizePolicy3.setHeightForWidth(lineEdit_2->sizePolicy().hasHeightForWidth());
        lineEdit_2->setSizePolicy(sizePolicy3);

        horizontalLayout_2->addWidget(lineEdit_2);


        gridLayout->addLayout(horizontalLayout_2, 1, 0, 1, 1);


        gridLayout_3->addWidget(groupBox, 1, 0, 1, 1);

        groupBox_2 = new QGroupBox(electrocMap);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        sizePolicy2.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy2);
        groupBox_2->setMaximumSize(QSize(250, 16777215));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_4 = new QLabel(groupBox_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_5->addWidget(label_4);

        lineEdit_4 = new QLineEdit(groupBox_2);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));
        sizePolicy3.setHeightForWidth(lineEdit_4->sizePolicy().hasHeightForWidth());
        lineEdit_4->setSizePolicy(sizePolicy3);

        horizontalLayout_5->addWidget(lineEdit_4);


        gridLayout_2->addLayout(horizontalLayout_5, 0, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_6->addWidget(label_5);

        lineEdit_5 = new QLineEdit(groupBox_2);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));
        sizePolicy3.setHeightForWidth(lineEdit_5->sizePolicy().hasHeightForWidth());
        lineEdit_5->setSizePolicy(sizePolicy3);

        horizontalLayout_6->addWidget(lineEdit_5);


        gridLayout_2->addLayout(horizontalLayout_6, 1, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_6 = new QLabel(groupBox_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_7->addWidget(label_6);

        lineEdit_6 = new QLineEdit(groupBox_2);
        lineEdit_6->setObjectName(QStringLiteral("lineEdit_6"));
        sizePolicy3.setHeightForWidth(lineEdit_6->sizePolicy().hasHeightForWidth());
        lineEdit_6->setSizePolicy(sizePolicy3);

        horizontalLayout_7->addWidget(lineEdit_6);


        gridLayout_2->addLayout(horizontalLayout_7, 2, 0, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_8->addWidget(label_7);

        lineEdit_7 = new QLineEdit(groupBox_2);
        lineEdit_7->setObjectName(QStringLiteral("lineEdit_7"));
        sizePolicy3.setHeightForWidth(lineEdit_7->sizePolicy().hasHeightForWidth());
        lineEdit_7->setSizePolicy(sizePolicy3);

        horizontalLayout_8->addWidget(lineEdit_7);


        gridLayout_2->addLayout(horizontalLayout_8, 3, 0, 1, 1);

        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_9->addWidget(label_8);

        lineEdit_8 = new QLineEdit(groupBox_2);
        lineEdit_8->setObjectName(QStringLiteral("lineEdit_8"));
        sizePolicy3.setHeightForWidth(lineEdit_8->sizePolicy().hasHeightForWidth());
        lineEdit_8->setSizePolicy(sizePolicy3);

        horizontalLayout_9->addWidget(lineEdit_8);


        gridLayout_2->addLayout(horizontalLayout_9, 4, 0, 1, 1);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        pushButton_4 = new QPushButton(groupBox_2);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setIcon(icon);

        horizontalLayout_10->addWidget(pushButton_4);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_3);

        pushButton_5 = new QPushButton(groupBox_2);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setIcon(icon1);

        horizontalLayout_10->addWidget(pushButton_5);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_4);

        pushButton_6 = new QPushButton(groupBox_2);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setIcon(icon2);

        horizontalLayout_10->addWidget(pushButton_6);


        gridLayout_2->addLayout(horizontalLayout_10, 5, 0, 1, 1);


        gridLayout_3->addWidget(groupBox_2, 2, 0, 1, 1);


        retranslateUi(electrocMap);

        QMetaObject::connectSlotsByName(electrocMap);
    } // setupUi

    void retranslateUi(QWidget *electrocMap)
    {
        electrocMap->setWindowTitle(QApplication::translate("electrocMap", "electrocMap", Q_NULLPTR));
        label_9->setText(QApplication::translate("electrocMap", "\345\233\276\347\211\207\346\234\200\344\275\263\345\210\206\350\276\250\347\216\207\344\270\272800x600", Q_NULLPTR));
        label_10->setText(QString());
        groupBox->setTitle(QApplication::translate("electrocMap", "\345\234\260\345\233\276\344\277\241\346\201\257", Q_NULLPTR));
        label->setText(QApplication::translate("electrocMap", "\345\234\260\345\233\276\345\220\215             ", Q_NULLPTR));
        label_3->setText(QApplication::translate("electrocMap", "\345\234\260\345\233\276\350\267\257\345\276\204", Q_NULLPTR));
        toolButton->setText(QApplication::translate("electrocMap", "...", Q_NULLPTR));
        pushButton->setText(QApplication::translate("electrocMap", "\345\242\236\345\212\240", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("electrocMap", "\344\277\235\345\255\230", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("electrocMap", "\345\210\240\351\231\244", Q_NULLPTR));
        label_2->setText(QApplication::translate("electrocMap", "\345\234\260\345\233\276\346\217\217\350\277\260", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("electrocMap", "\350\256\276\345\244\207\344\277\241\346\201\257", Q_NULLPTR));
        label_4->setText(QApplication::translate("electrocMap", "\350\256\276\345\244\207\345\220\215  ", Q_NULLPTR));
        label_5->setText(QApplication::translate("electrocMap", "\350\256\276\345\244\207\346\217\217\350\277\260", Q_NULLPTR));
        label_6->setText(QApplication::translate("electrocMap", "\350\256\276\345\244\207\347\261\273\345\236\213", Q_NULLPTR));
        label_7->setText(QApplication::translate("electrocMap", "X\345\235\220\346\240\207   ", Q_NULLPTR));
        label_8->setText(QApplication::translate("electrocMap", "Y\345\235\220\346\240\207   ", Q_NULLPTR));
        pushButton_4->setText(QApplication::translate("electrocMap", "\345\242\236\345\212\240", Q_NULLPTR));
        pushButton_5->setText(QApplication::translate("electrocMap", "\344\277\235\345\255\230", Q_NULLPTR));
        pushButton_6->setText(QApplication::translate("electrocMap", "\345\210\240\351\231\244", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class electrocMap: public Ui_electrocMap {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ELECTROCMAP_H
