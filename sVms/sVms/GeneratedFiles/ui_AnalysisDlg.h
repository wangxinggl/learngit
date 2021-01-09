/********************************************************************************
** Form generated from reading UI file 'AnalysisDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANALYSISDLG_H
#define UI_ANALYSISDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AnalysisDlg
{
public:
    QPushButton *btnClose;
    QPushButton *btnAll;
    QPushButton *btnClear;
    QCheckBox *checkBox;
    QPushButton *btnAreaSet;
    QPushButton *btnSave;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBox;
    QCheckBox *checkBox_Laser;
    QLabel *label_3;
    QComboBox *comboBox_AreaType;
    QLineEdit *lineEdit_Temperature;
    QLabel *label_Temp;

    void setupUi(QDialog *AnalysisDlg)
    {
        if (AnalysisDlg->objectName().isEmpty())
            AnalysisDlg->setObjectName(QStringLiteral("AnalysisDlg"));
        AnalysisDlg->resize(1038, 828);
        btnClose = new QPushButton(AnalysisDlg);
        btnClose->setObjectName(QStringLiteral("btnClose"));
        btnClose->setGeometry(QRect(1000, 10, 30, 30));
        btnClose->setMinimumSize(QSize(30, 30));
        btnClose->setMaximumSize(QSize(30, 30));
        QIcon icon;
        icon.addFile(QStringLiteral(":/res/SoftIcon/Cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnClose->setIcon(icon);
        btnClose->setIconSize(QSize(30, 30));
        btnAll = new QPushButton(AnalysisDlg);
        btnAll->setObjectName(QStringLiteral("btnAll"));
        btnAll->setGeometry(QRect(900, 450, 91, 31));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnAll->sizePolicy().hasHeightForWidth());
        btnAll->setSizePolicy(sizePolicy);
        btnClear = new QPushButton(AnalysisDlg);
        btnClear->setObjectName(QStringLiteral("btnClear"));
        btnClear->setGeometry(QRect(900, 530, 91, 31));
        sizePolicy.setHeightForWidth(btnClear->sizePolicy().hasHeightForWidth());
        btnClear->setSizePolicy(sizePolicy);
        checkBox = new QCheckBox(AnalysisDlg);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(920, 200, 71, 16));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(checkBox->sizePolicy().hasHeightForWidth());
        checkBox->setSizePolicy(sizePolicy1);
        btnAreaSet = new QPushButton(AnalysisDlg);
        btnAreaSet->setObjectName(QStringLiteral("btnAreaSet"));
        btnAreaSet->setGeometry(QRect(900, 370, 91, 31));
        sizePolicy.setHeightForWidth(btnAreaSet->sizePolicy().hasHeightForWidth());
        btnAreaSet->setSizePolicy(sizePolicy);
        btnSave = new QPushButton(AnalysisDlg);
        btnSave->setObjectName(QStringLiteral("btnSave"));
        btnSave->setGeometry(QRect(900, 610, 91, 31));
        layoutWidget_2 = new QWidget(AnalysisDlg);
        layoutWidget_2->setObjectName(QStringLiteral("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(870, 70, 121, 22));
        horizontalLayout = new QHBoxLayout(layoutWidget_2);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget_2);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        comboBox = new QComboBox(layoutWidget_2);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        sizePolicy.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(comboBox);

        checkBox_Laser = new QCheckBox(AnalysisDlg);
        checkBox_Laser->setObjectName(QStringLiteral("checkBox_Laser"));
        checkBox_Laser->setGeometry(QRect(920, 250, 71, 16));
        sizePolicy1.setHeightForWidth(checkBox_Laser->sizePolicy().hasHeightForWidth());
        checkBox_Laser->setSizePolicy(sizePolicy1);
        label_3 = new QLabel(AnalysisDlg);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(869, 132, 851, 20));
        label_3->setMinimumSize(QSize(100, 20));
        comboBox_AreaType = new QComboBox(AnalysisDlg);
        comboBox_AreaType->setObjectName(QStringLiteral("comboBox_AreaType"));
        comboBox_AreaType->setGeometry(QRect(930, 132, 91, 20));
        comboBox_AreaType->setMinimumSize(QSize(0, 0));
        lineEdit_Temperature = new QLineEdit(AnalysisDlg);
        lineEdit_Temperature->setObjectName(QStringLiteral("lineEdit_Temperature"));
        lineEdit_Temperature->setGeometry(QRect(917, 300, 83, 20));
        label_Temp = new QLabel(AnalysisDlg);
        label_Temp->setObjectName(QStringLiteral("label_Temp"));
        label_Temp->setGeometry(QRect(881, 300, 30, 16));

        retranslateUi(AnalysisDlg);

        QMetaObject::connectSlotsByName(AnalysisDlg);
    } // setupUi

    void retranslateUi(QDialog *AnalysisDlg)
    {
        AnalysisDlg->setWindowTitle(QApplication::translate("AnalysisDlg", "Dialog", Q_NULLPTR));
        btnClose->setText(QString());
        btnAll->setText(QApplication::translate("AnalysisDlg", "\345\205\250\351\203\250", Q_NULLPTR));
        btnClear->setText(QApplication::translate("AnalysisDlg", "\346\270\205\351\231\244", Q_NULLPTR));
        checkBox->setText(QApplication::translate("AnalysisDlg", "\345\214\272\345\237\237\350\256\276\347\275\256", Q_NULLPTR));
        btnAreaSet->setText(QApplication::translate("AnalysisDlg", "\346\243\200\346\265\213\345\214\272\345\237\237\350\256\276\347\275\256", Q_NULLPTR));
        btnSave->setText(QApplication::translate("AnalysisDlg", "\344\277\235\345\255\230", Q_NULLPTR));
        label->setText(QApplication::translate("AnalysisDlg", "\351\200\232\351\201\223", Q_NULLPTR));
        checkBox_Laser->setText(QApplication::translate("AnalysisDlg", "\346\277\200\345\205\211\344\275\277\350\203\275", Q_NULLPTR));
        label_3->setText(QApplication::translate("AnalysisDlg", "\345\214\272\345\237\237\347\261\273\345\236\213:", Q_NULLPTR));
        comboBox_AreaType->clear();
        comboBox_AreaType->insertItems(0, QStringList()
         << QApplication::translate("AnalysisDlg", "\345\214\272\345\237\237\350\257\206\345\210\253", Q_NULLPTR)
         << QApplication::translate("AnalysisDlg", "\345\214\272\345\237\237\345\261\217\350\224\275", Q_NULLPTR)
         << QApplication::translate("AnalysisDlg", "\346\270\251\345\272\246\350\257\206\345\210\253\345\214\272\345\237\237", Q_NULLPTR)
        );
        lineEdit_Temperature->setText(QApplication::translate("AnalysisDlg", "37.3", Q_NULLPTR));
        label_Temp->setText(QApplication::translate("AnalysisDlg", "\346\270\251\345\272\246:", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class AnalysisDlg: public Ui_AnalysisDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANALYSISDLG_H
