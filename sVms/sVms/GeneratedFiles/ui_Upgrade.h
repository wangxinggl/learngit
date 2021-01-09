/********************************************************************************
** Form generated from reading UI file 'Upgrade.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UPGRADE_H
#define UI_UPGRADE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Upgrade
{
public:
    QGroupBox *groupBox;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QComboBox *comboBox;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *btnFormat;
    QSpacerItem *horizontalSpacer_8;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLabel *label_Version;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnUpgrade;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnRestore;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btnRestart;
    QSpacerItem *horizontalSpacer_6;
    QProgressBar *progressBar;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_4;
    QLineEdit *lineEdit;
    QPushButton *btnSelect;
    QLabel *label_Status;
    QPushButton *btnClose;

    void setupUi(QWidget *Upgrade)
    {
        if (Upgrade->objectName().isEmpty())
            Upgrade->setObjectName(QStringLiteral("Upgrade"));
        Upgrade->resize(544, 342);
        groupBox = new QGroupBox(Upgrade);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(30, 220, 481, 57));
        gridLayout_2 = new QGridLayout(groupBox);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_3->addWidget(label_2);

        comboBox = new QComboBox(groupBox);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setSizeIncrement(QSize(40, 0));

        horizontalLayout_3->addWidget(comboBox);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_4);

        btnFormat = new QPushButton(groupBox);
        btnFormat->setObjectName(QStringLiteral("btnFormat"));

        horizontalLayout_3->addWidget(btnFormat);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_8);


        gridLayout_2->addLayout(horizontalLayout_3, 0, 0, 1, 1);

        layoutWidget = new QWidget(Upgrade);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(40, 65, 481, 31));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMaximumSize(QSize(60, 16777215));

        horizontalLayout->addWidget(label);

        label_Version = new QLabel(layoutWidget);
        label_Version->setObjectName(QStringLiteral("label_Version"));
        sizePolicy.setHeightForWidth(label_Version->sizePolicy().hasHeightForWidth());
        label_Version->setSizePolicy(sizePolicy);
        label_Version->setMaximumSize(QSize(16677215, 40));
        label_Version->setFrameShape(QFrame::NoFrame);

        horizontalLayout->addWidget(label_Version);

        layoutWidget1 = new QWidget(Upgrade);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(10, 280, 521, 41));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        btnUpgrade = new QPushButton(layoutWidget1);
        btnUpgrade->setObjectName(QStringLiteral("btnUpgrade"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(btnUpgrade->sizePolicy().hasHeightForWidth());
        btnUpgrade->setSizePolicy(sizePolicy1);
        btnUpgrade->setMinimumSize(QSize(50, 0));
        btnUpgrade->setMaximumSize(QSize(16777215, 35));

        horizontalLayout_2->addWidget(btnUpgrade);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        btnRestore = new QPushButton(layoutWidget1);
        btnRestore->setObjectName(QStringLiteral("btnRestore"));
        sizePolicy1.setHeightForWidth(btnRestore->sizePolicy().hasHeightForWidth());
        btnRestore->setSizePolicy(sizePolicy1);
        btnRestore->setMinimumSize(QSize(50, 0));
        btnRestore->setMaximumSize(QSize(16777215, 35));

        horizontalLayout_2->addWidget(btnRestore);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        btnRestart = new QPushButton(layoutWidget1);
        btnRestart->setObjectName(QStringLiteral("btnRestart"));
        sizePolicy1.setHeightForWidth(btnRestart->sizePolicy().hasHeightForWidth());
        btnRestart->setSizePolicy(sizePolicy1);
        btnRestart->setMinimumSize(QSize(50, 0));
        btnRestart->setMaximumSize(QSize(16777215, 35));

        horizontalLayout_2->addWidget(btnRestart);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_6);

        progressBar = new QProgressBar(Upgrade);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(30, 180, 501, 30));
        progressBar->setMinimumSize(QSize(0, 30));
        progressBar->setValue(0);
        layoutWidget2 = new QWidget(Upgrade);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(40, 100, 483, 32));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        lineEdit = new QLineEdit(layoutWidget2);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        sizePolicy.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy);
        lineEdit->setMinimumSize(QSize(400, 30));
        lineEdit->setMaximumSize(QSize(16777215, 35));

        horizontalLayout_4->addWidget(lineEdit);

        btnSelect = new QPushButton(layoutWidget2);
        btnSelect->setObjectName(QStringLiteral("btnSelect"));

        horizontalLayout_4->addWidget(btnSelect);

        label_Status = new QLabel(Upgrade);
        label_Status->setObjectName(QStringLiteral("label_Status"));
        label_Status->setGeometry(QRect(50, 150, 141, 21));
        btnClose = new QPushButton(Upgrade);
        btnClose->setObjectName(QStringLiteral("btnClose"));
        btnClose->setGeometry(QRect(510, 0, 30, 30));
        btnClose->setMinimumSize(QSize(30, 30));
        btnClose->setMaximumSize(QSize(30, 30));
        QIcon icon;
        icon.addFile(QStringLiteral(":/res/SoftIcon/Cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnClose->setIcon(icon);
        btnClose->setIconSize(QSize(30, 30));

        retranslateUi(Upgrade);

        QMetaObject::connectSlotsByName(Upgrade);
    } // setupUi

    void retranslateUi(QWidget *Upgrade)
    {
        Upgrade->setWindowTitle(QApplication::translate("Upgrade", "Upgrade", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("Upgrade", "SD\345\215\241", Q_NULLPTR));
        label_2->setText(QApplication::translate("Upgrade", "\345\215\241\345\217\267", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("Upgrade", "1", Q_NULLPTR)
         << QApplication::translate("Upgrade", "2", Q_NULLPTR)
        );
        btnFormat->setText(QApplication::translate("Upgrade", "\346\240\274\345\274\217\345\214\226", Q_NULLPTR));
        label->setText(QApplication::translate("Upgrade", "\345\275\223\345\211\215\347\211\210\346\234\254", Q_NULLPTR));
        label_Version->setText(QString());
        btnUpgrade->setText(QApplication::translate("Upgrade", "\345\215\207\347\272\247", Q_NULLPTR));
        btnRestore->setText(QApplication::translate("Upgrade", "\346\201\242\345\244\215\345\207\272\345\216\202", Q_NULLPTR));
        btnRestart->setText(QApplication::translate("Upgrade", "\351\207\215\345\220\257", Q_NULLPTR));
        btnSelect->setText(QApplication::translate("Upgrade", "\351\200\211\346\213\251\346\226\207\344\273\266", Q_NULLPTR));
        label_Status->setText(QApplication::translate("Upgrade", "\345\215\207\347\272\247\350\277\233\345\272\246\357\274\232", Q_NULLPTR));
        btnClose->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Upgrade: public Ui_Upgrade {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UPGRADE_H
