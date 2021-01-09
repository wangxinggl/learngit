/********************************************************************************
** Form generated from reading UI file 'AnalyseVideoAreaDlg.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ANALYSEVIDEOAREADLG_H
#define UI_ANALYSEVIDEOAREADLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_AnalyseVideoAreaDlg
{
public:
    QGridLayout *gridLayout;

    void setupUi(QDialog *AnalyseVideoAreaDlg)
    {
        if (AnalyseVideoAreaDlg->objectName().isEmpty())
            AnalyseVideoAreaDlg->setObjectName(QStringLiteral("AnalyseVideoAreaDlg"));
        AnalyseVideoAreaDlg->resize(704, 576);
        AnalyseVideoAreaDlg->setStyleSheet(QStringLiteral("border:1px solid white"));
        gridLayout = new QGridLayout(AnalyseVideoAreaDlg);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));

        retranslateUi(AnalyseVideoAreaDlg);

        QMetaObject::connectSlotsByName(AnalyseVideoAreaDlg);
    } // setupUi

    void retranslateUi(QDialog *AnalyseVideoAreaDlg)
    {
        AnalyseVideoAreaDlg->setWindowTitle(QApplication::translate("AnalyseVideoAreaDlg", "AnalyseVideoAreaDlg", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class AnalyseVideoAreaDlg: public Ui_AnalyseVideoAreaDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ANALYSEVIDEOAREADLG_H
