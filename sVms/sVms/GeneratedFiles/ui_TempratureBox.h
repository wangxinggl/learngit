/********************************************************************************
** Form generated from reading UI file 'TempratureBox.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEMPRATUREBOX_H
#define UI_TEMPRATUREBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Temperature_Box
{
public:
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_displayTime;
    QLabel *label;
    QLabel *label_Temperature;
    QPushButton *btnClose;

    void setupUi(QWidget *Temperature_Box)
    {
        if (Temperature_Box->objectName().isEmpty())
            Temperature_Box->setObjectName(QStringLiteral("Temperature_Box"));
        Temperature_Box->resize(212, 300);
        layoutWidget = new QWidget(Temperature_Box);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(0, 35, 211, 261));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_displayTime = new QLabel(layoutWidget);
        label_displayTime->setObjectName(QStringLiteral("label_displayTime"));
        label_displayTime->setMinimumSize(QSize(0, 20));
        label_displayTime->setMaximumSize(QSize(2000, 20));
        label_displayTime->setScaledContents(true);
        label_displayTime->setWordWrap(false);

        gridLayout->addWidget(label_displayTime, 2, 0, 1, 1);

        label = new QLabel(layoutWidget);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(10, 10));
        label->setMaximumSize(QSize(1000, 1000));
        label->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        label->setScaledContents(true);
        label->setWordWrap(true);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_Temperature = new QLabel(layoutWidget);
        label_Temperature->setObjectName(QStringLiteral("label_Temperature"));
        label_Temperature->setMinimumSize(QSize(0, 20));
        label_Temperature->setMaximumSize(QSize(16777215, 20));

        gridLayout->addWidget(label_Temperature, 1, 0, 1, 1);

        btnClose = new QPushButton(Temperature_Box);
        btnClose->setObjectName(QStringLiteral("btnClose"));
        btnClose->setGeometry(QRect(180, 0, 30, 30));
        btnClose->setMinimumSize(QSize(30, 30));
        btnClose->setMaximumSize(QSize(30, 30));
        QIcon icon;
        icon.addFile(QStringLiteral(":/res/SoftIcon/Cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnClose->setIcon(icon);
        btnClose->setIconSize(QSize(30, 30));

        retranslateUi(Temperature_Box);

        QMetaObject::connectSlotsByName(Temperature_Box);
    } // setupUi

    void retranslateUi(QWidget *Temperature_Box)
    {
        Temperature_Box->setWindowTitle(QApplication::translate("Temperature_Box", "Temprature", Q_NULLPTR));
        label_displayTime->setText(QString());
        label->setText(QString());
        label_Temperature->setText(QString());
        btnClose->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Temperature_Box: public Ui_Temperature_Box {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEMPRATUREBOX_H
