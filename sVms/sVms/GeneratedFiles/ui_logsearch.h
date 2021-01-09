/********************************************************************************
** Form generated from reading UI file 'logsearch.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGSEARCH_H
#define UI_LOGSEARCH_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LogSearch
{
public:
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QDateTimeEdit *dateTimeEdit;
    QLabel *label_4;
    QDateTimeEdit *dateTimeEdit_2;
    QSpacerItem *horizontalSpacer_10;
    QPushButton *btnLogAlmSearch;
    QTableWidget *tableWidget_Alm;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_11;
    QPushButton *btnLogDel;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *btnClear;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btnExport;
    QSpacerItem *horizontalSpacer_4;
    QCheckBox *checkBox;

    void setupUi(QWidget *LogSearch)
    {
        if (LogSearch->objectName().isEmpty())
            LogSearch->setObjectName(QStringLiteral("LogSearch"));
        LogSearch->resize(843, 491);
        QFont font;
        font.setPointSize(14);
        LogSearch->setFont(font);
        gridLayout = new QGridLayout(LogSearch);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_3 = new QLabel(LogSearch);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_5->addWidget(label_3);

        dateTimeEdit = new QDateTimeEdit(LogSearch);
        dateTimeEdit->setObjectName(QStringLiteral("dateTimeEdit"));
        dateTimeEdit->setCalendarPopup(true);

        horizontalLayout_5->addWidget(dateTimeEdit);

        label_4 = new QLabel(LogSearch);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_5->addWidget(label_4);

        dateTimeEdit_2 = new QDateTimeEdit(LogSearch);
        dateTimeEdit_2->setObjectName(QStringLiteral("dateTimeEdit_2"));
        dateTimeEdit_2->setCalendarPopup(true);

        horizontalLayout_5->addWidget(dateTimeEdit_2);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_10);

        btnLogAlmSearch = new QPushButton(LogSearch);
        btnLogAlmSearch->setObjectName(QStringLiteral("btnLogAlmSearch"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/res/SoftIcon/search.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnLogAlmSearch->setIcon(icon);
        btnLogAlmSearch->setIconSize(QSize(25, 25));

        horizontalLayout_5->addWidget(btnLogAlmSearch);


        gridLayout->addLayout(horizontalLayout_5, 0, 0, 1, 1);

        tableWidget_Alm = new QTableWidget(LogSearch);
        tableWidget_Alm->setObjectName(QStringLiteral("tableWidget_Alm"));

        gridLayout->addWidget(tableWidget_Alm, 1, 0, 1, 1);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_11);

        btnLogDel = new QPushButton(LogSearch);
        btnLogDel->setObjectName(QStringLiteral("btnLogDel"));
        QFont font1;
        font1.setFamily(QStringLiteral("Arial"));
        font1.setPointSize(12);
        btnLogDel->setFont(font1);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/res/SoftIcon/Cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnLogDel->setIcon(icon1);
        btnLogDel->setIconSize(QSize(25, 25));

        horizontalLayout_7->addWidget(btnLogDel);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_5);

        btnClear = new QPushButton(LogSearch);
        btnClear->setObjectName(QStringLiteral("btnClear"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(btnClear->sizePolicy().hasHeightForWidth());
        btnClear->setSizePolicy(sizePolicy);
        btnClear->setMinimumSize(QSize(0, 33));
        btnClear->setFont(font1);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/res/SoftIcon/Clear.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnClear->setIcon(icon2);
        btnClear->setIconSize(QSize(25, 25));

        horizontalLayout_7->addWidget(btnClear);

        horizontalSpacer_3 = new QSpacerItem(37, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_3);

        btnExport = new QPushButton(LogSearch);
        btnExport->setObjectName(QStringLiteral("btnExport"));
        btnExport->setMinimumSize(QSize(0, 33));
        btnExport->setFont(font1);
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/res/SoftIcon/excel.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnExport->setIcon(icon3);
        btnExport->setIconSize(QSize(20, 20));

        horizontalLayout_7->addWidget(btnExport);

        horizontalSpacer_4 = new QSpacerItem(37, 17, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_4);

        checkBox = new QCheckBox(LogSearch);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setFont(font1);

        horizontalLayout_7->addWidget(checkBox);


        gridLayout->addLayout(horizontalLayout_7, 2, 0, 1, 1);


        retranslateUi(LogSearch);

        QMetaObject::connectSlotsByName(LogSearch);
    } // setupUi

    void retranslateUi(QWidget *LogSearch)
    {
        LogSearch->setWindowTitle(QApplication::translate("LogSearch", "LogSearch", Q_NULLPTR));
        label_3->setText(QApplication::translate("LogSearch", "\345\274\200\345\247\213\346\227\266\351\227\264", Q_NULLPTR));
        label_4->setText(QApplication::translate("LogSearch", "\347\273\223\346\235\237\346\227\266\351\227\264", Q_NULLPTR));
        btnLogAlmSearch->setText(QApplication::translate("LogSearch", "\346\220\234\347\264\242", Q_NULLPTR));
        btnLogDel->setText(QApplication::translate("LogSearch", "\345\210\240\351\231\244", Q_NULLPTR));
        btnClear->setText(QApplication::translate("LogSearch", "\346\270\205\351\231\244\345\205\250\351\203\250", Q_NULLPTR));
        btnExport->setText(QApplication::translate("LogSearch", "\345\257\274\345\207\272", Q_NULLPTR));
        checkBox->setText(QApplication::translate("LogSearch", "\344\270\215\345\206\215\345\274\271\345\207\272", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class LogSearch: public Ui_LogSearch {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGSEARCH_H
