/********************************************************************************
** Form generated from reading UI file 'capacityset.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CAPACITYSET_H
#define UI_CAPACITYSET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_capacitySet
{
public:
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QLabel *label_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLineEdit *lineEdit_unRec;
    QLineEdit *lineEdit_Rec;
    QLabel *label_2;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnSet;
    QPushButton *btnClose;

    void setupUi(QWidget *capacitySet)
    {
        if (capacitySet->objectName().isEmpty())
            capacitySet->setObjectName(QStringLiteral("capacitySet"));
        capacitySet->resize(399, 222);
        gridLayout_3 = new QGridLayout(capacitySet);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(-1, 0, -1, -1);
        groupBox_2 = new QGroupBox(capacitySet);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(10);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(50);
        label_3->setFont(font);
        label_3->setStyleSheet(QString::fromUtf8("font: 10pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));

        gridLayout_2->addWidget(label_3, 0, 0, 1, 2);

        groupBox = new QGroupBox(groupBox_2);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        lineEdit_unRec = new QLineEdit(groupBox);
        lineEdit_unRec->setObjectName(QStringLiteral("lineEdit_unRec"));
        lineEdit_unRec->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(lineEdit_unRec, 1, 1, 1, 1);

        lineEdit_Rec = new QLineEdit(groupBox);
        lineEdit_Rec->setObjectName(QStringLiteral("lineEdit_Rec"));
        lineEdit_Rec->setMinimumSize(QSize(0, 25));

        gridLayout->addWidget(lineEdit_Rec, 0, 1, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setMaximumSize(QSize(16777215, 16777215));
        label_2->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMaximumSize(QSize(16777215, 16777215));
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);


        gridLayout_2->addWidget(groupBox, 1, 0, 1, 3);

        horizontalSpacer = new QSpacerItem(208, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 2, 0, 1, 1);

        btnSet = new QPushButton(groupBox_2);
        btnSet->setObjectName(QStringLiteral("btnSet"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/res/SoftIcon/SystemSet.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnSet->setIcon(icon);

        gridLayout_2->addWidget(btnSet, 2, 1, 1, 2);

        btnClose = new QPushButton(groupBox_2);
        btnClose->setObjectName(QStringLiteral("btnClose"));
        btnClose->setMinimumSize(QSize(30, 30));
        btnClose->setMaximumSize(QSize(30, 30));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/res/SoftIcon/Cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnClose->setIcon(icon1);
        btnClose->setIconSize(QSize(30, 30));

        gridLayout_2->addWidget(btnClose, 0, 2, 1, 1);


        gridLayout_3->addWidget(groupBox_2, 0, 0, 1, 1);


        retranslateUi(capacitySet);

        QMetaObject::connectSlotsByName(capacitySet);
    } // setupUi

    void retranslateUi(QWidget *capacitySet)
    {
        capacitySet->setWindowTitle(QApplication::translate("capacitySet", "capacitySet", Q_NULLPTR));
        groupBox_2->setTitle(QString());
        label_3->setText(QApplication::translate("capacitySet", "\346\231\272\350\203\275\350\257\206\345\210\253", Q_NULLPTR));
        groupBox->setTitle(QString());
        label_2->setText(QApplication::translate("capacitySet", "\346\212\223\346\213\215\351\230\237\345\210\227", Q_NULLPTR));
        label->setText(QApplication::translate("capacitySet", "\350\257\206\345\210\253\351\230\237\345\210\227", Q_NULLPTR));
        btnSet->setText(QApplication::translate("capacitySet", "\350\256\276\347\275\256", Q_NULLPTR));
        btnClose->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class capacitySet: public Ui_capacitySet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CAPACITYSET_H
