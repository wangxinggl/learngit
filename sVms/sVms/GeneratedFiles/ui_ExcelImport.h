/********************************************************************************
** Form generated from reading UI file 'ExcelImport.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EXCELIMPORT_H
#define UI_EXCELIMPORT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ExcelImport
{
public:
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *btnOpenExcel;
    QTableWidget *tableWidget;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnImport;
    QPushButton *btnCancel;

    void setupUi(QWidget *ExcelImport)
    {
        if (ExcelImport->objectName().isEmpty())
            ExcelImport->setObjectName(QStringLiteral("ExcelImport"));
        ExcelImport->resize(751, 468);
        gridLayout = new QGridLayout(ExcelImport);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        label = new QLabel(ExcelImport);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(60, 16777215));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lineEdit = new QLineEdit(ExcelImport);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy);

        gridLayout->addWidget(lineEdit, 0, 1, 1, 2);

        btnOpenExcel = new QPushButton(ExcelImport);
        btnOpenExcel->setObjectName(QStringLiteral("btnOpenExcel"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(btnOpenExcel->sizePolicy().hasHeightForWidth());
        btnOpenExcel->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(btnOpenExcel, 0, 3, 1, 1);

        tableWidget = new QTableWidget(ExcelImport);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));

        gridLayout->addWidget(tableWidget, 1, 0, 1, 4);

        horizontalSpacer = new QSpacerItem(488, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 2, 0, 1, 2);

        btnImport = new QPushButton(ExcelImport);
        btnImport->setObjectName(QStringLiteral("btnImport"));
        sizePolicy1.setHeightForWidth(btnImport->sizePolicy().hasHeightForWidth());
        btnImport->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(btnImport, 2, 2, 1, 1);

        btnCancel = new QPushButton(ExcelImport);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));
        sizePolicy1.setHeightForWidth(btnCancel->sizePolicy().hasHeightForWidth());
        btnCancel->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(btnCancel, 2, 3, 1, 1);


        retranslateUi(ExcelImport);

        QMetaObject::connectSlotsByName(ExcelImport);
    } // setupUi

    void retranslateUi(QWidget *ExcelImport)
    {
        ExcelImport->setWindowTitle(QApplication::translate("ExcelImport", "ExcelImport", Q_NULLPTR));
        label->setText(QApplication::translate("ExcelImport", "Excel\346\226\207\344\273\266", Q_NULLPTR));
        btnOpenExcel->setText(QApplication::translate("ExcelImport", "\346\211\223\345\274\200", Q_NULLPTR));
        btnImport->setText(QApplication::translate("ExcelImport", "\345\257\274\345\205\245", Q_NULLPTR));
        btnCancel->setText(QApplication::translate("ExcelImport", "\345\217\226\346\266\210", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ExcelImport: public Ui_ExcelImport {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EXCELIMPORT_H
