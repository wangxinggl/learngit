/********************************************************************************
** Form generated from reading UI file 'BehaviorAnalyseDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BEHAVIORANALYSEDLG_H
#define UI_BEHAVIORANALYSEDLG_H

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
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BehaviorAnalyseDlg
{
public:
    QGridLayout *gridLayout_2;
    QLineEdit *lineEdit_Search;
    QVBoxLayout *verticalLayout_6;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLabel *label_IP;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_4;
    QLabel *label_Version;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_6;
    QLabel *label_WebVersion;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_8;
    QLabel *label_Num;
    QSpacerItem *horizontalSpacer_4;
    QVBoxLayout *verticalLayout_5;
    QPushButton *btnUpGrade;
    QPushButton *btnWeb;
    QGroupBox *groupBox_2;
    QPushButton *btnEncode;
    QPushButton *btnImageSet;
    QGroupBox *groupBox_3;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnArea;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *btnWarning;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *btnFace;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *btnVideoWarning;
    QSpacerItem *horizontalSpacer_9;
    QGroupBox *groupBox_4;
    QPushButton *btnNetWork;
    QGroupBox *groupBox_5;
    QPushButton *btnordinarySet;
    QTreeWidget *treeWidget;
    QSpacerItem *verticalSpacer;

    void setupUi(QWidget *BehaviorAnalyseDlg)
    {
        if (BehaviorAnalyseDlg->objectName().isEmpty())
            BehaviorAnalyseDlg->setObjectName(QStringLiteral("BehaviorAnalyseDlg"));
        BehaviorAnalyseDlg->resize(1314, 648);
        gridLayout_2 = new QGridLayout(BehaviorAnalyseDlg);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        lineEdit_Search = new QLineEdit(BehaviorAnalyseDlg);
        lineEdit_Search->setObjectName(QStringLiteral("lineEdit_Search"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEdit_Search->sizePolicy().hasHeightForWidth());
        lineEdit_Search->setSizePolicy(sizePolicy);
        lineEdit_Search->setMaximumSize(QSize(220, 16777215));

        gridLayout_2->addWidget(lineEdit_Search, 0, 0, 1, 1);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        groupBox = new QGroupBox(BehaviorAnalyseDlg);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setMinimumSize(QSize(120, 0));
        label->setFrameShape(QFrame::NoFrame);

        verticalLayout->addWidget(label);

        label_IP = new QLabel(groupBox);
        label_IP->setObjectName(QStringLiteral("label_IP"));
        label_IP->setFrameShape(QFrame::NoFrame);
        label_IP->setScaledContents(true);

        verticalLayout->addWidget(label_IP);


        horizontalLayout->addLayout(verticalLayout);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setMinimumSize(QSize(120, 0));
        label_4->setFrameShape(QFrame::NoFrame);

        verticalLayout_2->addWidget(label_4);

        label_Version = new QLabel(groupBox);
        label_Version->setObjectName(QStringLiteral("label_Version"));
        label_Version->setFrameShape(QFrame::NoFrame);
        label_Version->setScaledContents(true);

        verticalLayout_2->addWidget(label_Version);


        horizontalLayout->addLayout(verticalLayout_2);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setMinimumSize(QSize(120, 0));
        label_6->setFrameShape(QFrame::NoFrame);

        verticalLayout_3->addWidget(label_6);

        label_WebVersion = new QLabel(groupBox);
        label_WebVersion->setObjectName(QStringLiteral("label_WebVersion"));
        label_WebVersion->setFrameShape(QFrame::NoFrame);
        label_WebVersion->setScaledContents(true);

        verticalLayout_3->addWidget(label_WebVersion);


        horizontalLayout->addLayout(verticalLayout_3);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setMinimumSize(QSize(120, 0));
        label_8->setFrameShape(QFrame::NoFrame);

        verticalLayout_4->addWidget(label_8);

        label_Num = new QLabel(groupBox);
        label_Num->setObjectName(QStringLiteral("label_Num"));
        label_Num->setFrameShape(QFrame::NoFrame);
        label_Num->setScaledContents(true);

        verticalLayout_4->addWidget(label_Num);


        horizontalLayout->addLayout(verticalLayout_4);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        btnUpGrade = new QPushButton(groupBox);
        btnUpGrade->setObjectName(QStringLiteral("btnUpGrade"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(btnUpGrade->sizePolicy().hasHeightForWidth());
        btnUpGrade->setSizePolicy(sizePolicy1);

        verticalLayout_5->addWidget(btnUpGrade);

        btnWeb = new QPushButton(groupBox);
        btnWeb->setObjectName(QStringLiteral("btnWeb"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(btnWeb->sizePolicy().hasHeightForWidth());
        btnWeb->setSizePolicy(sizePolicy2);

        verticalLayout_5->addWidget(btnWeb);


        horizontalLayout->addLayout(verticalLayout_5);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        verticalLayout_6->addWidget(groupBox);

        groupBox_2 = new QGroupBox(BehaviorAnalyseDlg);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setMinimumSize(QSize(0, 70));
        btnEncode = new QPushButton(groupBox_2);
        btnEncode->setObjectName(QStringLiteral("btnEncode"));
        btnEncode->setGeometry(QRect(20, 30, 130, 30));
        btnEncode->setMinimumSize(QSize(120, 30));
        btnImageSet = new QPushButton(groupBox_2);
        btnImageSet->setObjectName(QStringLiteral("btnImageSet"));
        btnImageSet->setGeometry(QRect(190, 30, 130, 30));
        btnImageSet->setMinimumSize(QSize(120, 30));

        verticalLayout_6->addWidget(groupBox_2);

        groupBox_3 = new QGroupBox(BehaviorAnalyseDlg);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setMinimumSize(QSize(0, 70));
        layoutWidget = new QWidget(groupBox_3);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 24, 661, 32));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        btnArea = new QPushButton(layoutWidget);
        btnArea->setObjectName(QStringLiteral("btnArea"));
        sizePolicy.setHeightForWidth(btnArea->sizePolicy().hasHeightForWidth());
        btnArea->setSizePolicy(sizePolicy);
        btnArea->setMinimumSize(QSize(120, 30));

        horizontalLayout_2->addWidget(btnArea);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);

        btnWarning = new QPushButton(layoutWidget);
        btnWarning->setObjectName(QStringLiteral("btnWarning"));
        sizePolicy.setHeightForWidth(btnWarning->sizePolicy().hasHeightForWidth());
        btnWarning->setSizePolicy(sizePolicy);
        btnWarning->setMinimumSize(QSize(120, 30));

        horizontalLayout_2->addWidget(btnWarning);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_7);

        btnFace = new QPushButton(layoutWidget);
        btnFace->setObjectName(QStringLiteral("btnFace"));
        sizePolicy.setHeightForWidth(btnFace->sizePolicy().hasHeightForWidth());
        btnFace->setSizePolicy(sizePolicy);
        btnFace->setMinimumSize(QSize(120, 30));

        horizontalLayout_2->addWidget(btnFace);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_8);

        btnVideoWarning = new QPushButton(layoutWidget);
        btnVideoWarning->setObjectName(QStringLiteral("btnVideoWarning"));
        btnVideoWarning->setMinimumSize(QSize(120, 30));

        horizontalLayout_2->addWidget(btnVideoWarning);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_9);


        verticalLayout_6->addWidget(groupBox_3);

        groupBox_4 = new QGroupBox(BehaviorAnalyseDlg);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setMinimumSize(QSize(0, 70));
        btnNetWork = new QPushButton(groupBox_4);
        btnNetWork->setObjectName(QStringLiteral("btnNetWork"));
        btnNetWork->setGeometry(QRect(20, 30, 130, 30));
        btnNetWork->setMinimumSize(QSize(120, 30));

        verticalLayout_6->addWidget(groupBox_4);

        groupBox_5 = new QGroupBox(BehaviorAnalyseDlg);
        groupBox_5->setObjectName(QStringLiteral("groupBox_5"));
        groupBox_5->setMinimumSize(QSize(0, 70));
        btnordinarySet = new QPushButton(groupBox_5);
        btnordinarySet->setObjectName(QStringLiteral("btnordinarySet"));
        btnordinarySet->setGeometry(QRect(20, 30, 130, 30));
        btnordinarySet->setMinimumSize(QSize(120, 30));

        verticalLayout_6->addWidget(groupBox_5);


        gridLayout_2->addLayout(verticalLayout_6, 0, 1, 2, 1);

        treeWidget = new QTreeWidget(BehaviorAnalyseDlg);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        treeWidget->setMinimumSize(QSize(220, 0));
        treeWidget->setMaximumSize(QSize(220, 16777215));

        gridLayout_2->addWidget(treeWidget, 1, 0, 2, 1);

        verticalSpacer = new QSpacerItem(20, 239, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 2, 1, 1, 1);


        retranslateUi(BehaviorAnalyseDlg);

        QMetaObject::connectSlotsByName(BehaviorAnalyseDlg);
    } // setupUi

    void retranslateUi(QWidget *BehaviorAnalyseDlg)
    {
        BehaviorAnalyseDlg->setWindowTitle(QApplication::translate("BehaviorAnalyseDlg", "BehaviorAnalyseDlg", Q_NULLPTR));
        groupBox->setTitle(QString());
        label->setText(QApplication::translate("BehaviorAnalyseDlg", "IP:", Q_NULLPTR));
        label_IP->setText(QString());
        label_4->setText(QApplication::translate("BehaviorAnalyseDlg", "\350\275\257\344\273\266\347\211\210\346\234\254:", Q_NULLPTR));
        label_Version->setText(QString());
        label_6->setText(QApplication::translate("BehaviorAnalyseDlg", "\351\241\265\351\235\242\347\211\210\346\234\254:", Q_NULLPTR));
        label_WebVersion->setText(QString());
        label_8->setText(QApplication::translate("BehaviorAnalyseDlg", "\345\272\217\345\210\227\345\217\267:", Q_NULLPTR));
        label_Num->setText(QString());
        btnUpGrade->setText(QApplication::translate("BehaviorAnalyseDlg", "\345\215\207\347\272\247", Q_NULLPTR));
        btnWeb->setText(QApplication::translate("BehaviorAnalyseDlg", "\351\223\276\346\216\245\345\210\260web", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("BehaviorAnalyseDlg", "\350\247\206\351\242\221\350\256\276\347\275\256", Q_NULLPTR));
        btnEncode->setText(QApplication::translate("BehaviorAnalyseDlg", "\347\240\201\346\265\201\350\256\276\347\275\256", Q_NULLPTR));
        btnImageSet->setText(QApplication::translate("BehaviorAnalyseDlg", "\345\233\276\345\203\217\350\256\276\347\275\256", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("BehaviorAnalyseDlg", "\346\231\272\350\203\275\345\217\202\346\225\260", Q_NULLPTR));
        btnArea->setText(QApplication::translate("BehaviorAnalyseDlg", "\345\214\272\345\237\237\350\256\276\347\275\256", Q_NULLPTR));
        btnWarning->setText(QApplication::translate("BehaviorAnalyseDlg", "\346\212\245\350\255\246\345\217\202\346\225\260", Q_NULLPTR));
        btnFace->setText(QApplication::translate("BehaviorAnalyseDlg", "\344\272\272\350\204\270\345\217\202\346\225\260", Q_NULLPTR));
        btnVideoWarning->setText(QApplication::translate("BehaviorAnalyseDlg", "\350\247\206\351\242\221\345\221\212\350\255\246\350\256\276\347\275\256", Q_NULLPTR));
        groupBox_4->setTitle(QApplication::translate("BehaviorAnalyseDlg", "\347\275\221\347\273\234\350\256\276\347\275\256", Q_NULLPTR));
        btnNetWork->setText(QApplication::translate("BehaviorAnalyseDlg", "\347\275\221\347\273\234\350\256\276\347\275\256", Q_NULLPTR));
        groupBox_5->setTitle(QApplication::translate("BehaviorAnalyseDlg", "\347\263\273\347\273\237\350\256\276\347\275\256", Q_NULLPTR));
        btnordinarySet->setText(QApplication::translate("BehaviorAnalyseDlg", "\346\231\256\351\200\232\350\256\276\347\275\256", Q_NULLPTR));
        QTreeWidgetItem *___qtreewidgetitem = treeWidget->headerItem();
        ___qtreewidgetitem->setText(0, QApplication::translate("BehaviorAnalyseDlg", "\350\256\276\345\244\207\345\210\227\350\241\250", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class BehaviorAnalyseDlg: public Ui_BehaviorAnalyseDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BEHAVIORANALYSEDLG_H
