/********************************************************************************
** Form generated from reading UI file 'OrdinarySet.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ORDINARYSET_H
#define UI_ORDINARYSET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OrdinarySet
{
public:
    QTabWidget *btntSave;
    QWidget *tab;
    QLabel *label;
    QLineEdit *lineEdit_Device;
    QLabel *label_2;
    QComboBox *comboBox_Language;
    QLabel *label_3;
    QComboBox *comboBox_vFormat;
    QWidget *tab_2;
    QLabel *label_4;
    QLabel *label_5;
    QComboBox *comboBox_dFormat;
    QLabel *label_6;
    QComboBox *comboBox_dInterval;
    QLabel *label_7;
    QComboBox *comboBox_tFormat;
    QPushButton *btnClose;
    QPushButton *btnUpgrade;
    QPushButton *btnSave;

    void setupUi(QDialog *OrdinarySet)
    {
        if (OrdinarySet->objectName().isEmpty())
            OrdinarySet->setObjectName(QStringLiteral("OrdinarySet"));
        OrdinarySet->resize(731, 434);
        btntSave = new QTabWidget(OrdinarySet);
        btntSave->setObjectName(QStringLiteral("btntSave"));
        btntSave->setGeometry(QRect(10, 50, 711, 341));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        label = new QLabel(tab);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(40, 40, 51, 16));
        lineEdit_Device = new QLineEdit(tab);
        lineEdit_Device->setObjectName(QStringLiteral("lineEdit_Device"));
        lineEdit_Device->setGeometry(QRect(100, 40, 211, 20));
        label_2 = new QLabel(tab);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(60, 90, 31, 16));
        comboBox_Language = new QComboBox(tab);
        comboBox_Language->setObjectName(QStringLiteral("comboBox_Language"));
        comboBox_Language->setGeometry(QRect(100, 90, 211, 22));
        label_3 = new QLabel(tab);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(30, 140, 51, 16));
        comboBox_vFormat = new QComboBox(tab);
        comboBox_vFormat->setObjectName(QStringLiteral("comboBox_vFormat"));
        comboBox_vFormat->setGeometry(QRect(100, 140, 211, 22));
        btntSave->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        label_4 = new QLabel(tab_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(40, 30, 54, 12));
        label_5 = new QLabel(tab_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(50, 30, 54, 12));
        comboBox_dFormat = new QComboBox(tab_2);
        comboBox_dFormat->setObjectName(QStringLiteral("comboBox_dFormat"));
        comboBox_dFormat->setGeometry(QRect(110, 20, 171, 22));
        label_6 = new QLabel(tab_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(40, 70, 61, 16));
        comboBox_dInterval = new QComboBox(tab_2);
        comboBox_dInterval->setObjectName(QStringLiteral("comboBox_dInterval"));
        comboBox_dInterval->setGeometry(QRect(110, 70, 171, 22));
        label_7 = new QLabel(tab_2);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(50, 120, 51, 16));
        comboBox_tFormat = new QComboBox(tab_2);
        comboBox_tFormat->setObjectName(QStringLiteral("comboBox_tFormat"));
        comboBox_tFormat->setGeometry(QRect(110, 120, 171, 22));
        btntSave->addTab(tab_2, QString());
        btnClose = new QPushButton(OrdinarySet);
        btnClose->setObjectName(QStringLiteral("btnClose"));
        btnClose->setGeometry(QRect(690, 10, 30, 30));
        btnClose->setMinimumSize(QSize(30, 30));
        btnClose->setMaximumSize(QSize(30, 30));
        QIcon icon;
        icon.addFile(QStringLiteral(":/res/SoftIcon/Cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnClose->setIcon(icon);
        btnClose->setIconSize(QSize(30, 30));
        btnUpgrade = new QPushButton(OrdinarySet);
        btnUpgrade->setObjectName(QStringLiteral("btnUpgrade"));
        btnUpgrade->setGeometry(QRect(640, 400, 75, 23));
        btnSave = new QPushButton(OrdinarySet);
        btnSave->setObjectName(QStringLiteral("btnSave"));
        btnSave->setGeometry(QRect(530, 400, 75, 23));

        retranslateUi(OrdinarySet);

        btntSave->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(OrdinarySet);
    } // setupUi

    void retranslateUi(QDialog *OrdinarySet)
    {
        OrdinarySet->setWindowTitle(QApplication::translate("OrdinarySet", "OrdinarySet", Q_NULLPTR));
        label->setText(QApplication::translate("OrdinarySet", "\350\256\276\345\244\207\345\220\215\347\247\260", Q_NULLPTR));
        label_2->setText(QApplication::translate("OrdinarySet", "\350\257\255\350\250\200", Q_NULLPTR));
        label_3->setText(QApplication::translate("OrdinarySet", "\350\247\206\351\242\221\345\210\266\345\274\217", Q_NULLPTR));
        btntSave->setTabText(btntSave->indexOf(tab), QApplication::translate("OrdinarySet", "\346\234\254\346\234\272\350\256\276\347\275\256", Q_NULLPTR));
        label_4->setText(QString());
        label_5->setText(QApplication::translate("OrdinarySet", "\346\227\245\346\234\237\346\240\274\345\274\217", Q_NULLPTR));
        label_6->setText(QApplication::translate("OrdinarySet", "\346\227\245\346\234\237\351\227\264\351\232\224\347\254\246", Q_NULLPTR));
        label_7->setText(QApplication::translate("OrdinarySet", "\346\227\266\351\227\264\346\240\274\345\274\217", Q_NULLPTR));
        btntSave->setTabText(btntSave->indexOf(tab_2), QApplication::translate("OrdinarySet", "\346\227\266\351\227\264\350\256\276\347\275\256", Q_NULLPTR));
        btnClose->setText(QString());
        btnUpgrade->setText(QApplication::translate("OrdinarySet", "\346\233\264\346\226\260", Q_NULLPTR));
        btnSave->setText(QApplication::translate("OrdinarySet", "\344\277\235\345\255\230", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class OrdinarySet: public Ui_OrdinarySet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ORDINARYSET_H
