/********************************************************************************
** Form generated from reading UI file 'unrecognition.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_UNRECOGNITION_H
#define UI_UNRECOGNITION_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_unRecognition
{
public:
    QWidget *widget;
    QGridLayout *gridLayout;
    QLabel *label_displayTime;
    QLabel *label;
    QLabel *label_Temperature;

    void setupUi(QWidget *unRecognition)
    {
        if (unRecognition->objectName().isEmpty())
            unRecognition->setObjectName(QStringLiteral("unRecognition"));
        unRecognition->resize(128, 150);
        unRecognition->setMinimumSize(QSize(128, 150));
        unRecognition->setMaximumSize(QSize(128, 150));
        widget = new QWidget(unRecognition);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(0, 1, 131, 146));
        gridLayout = new QGridLayout(widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_displayTime = new QLabel(widget);
        label_displayTime->setObjectName(QStringLiteral("label_displayTime"));
        label_displayTime->setMinimumSize(QSize(0, 20));
        label_displayTime->setMaximumSize(QSize(127, 20));
        label_displayTime->setScaledContents(true);
        label_displayTime->setWordWrap(false);

        gridLayout->addWidget(label_displayTime, 2, 0, 1, 1);

        label = new QLabel(widget);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(0, 50));
        label->setMaximumSize(QSize(122, 100));
        label->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 255);"));
        label->setScaledContents(true);
        label->setWordWrap(true);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        label_Temperature = new QLabel(widget);
        label_Temperature->setObjectName(QStringLiteral("label_Temperature"));
        label_Temperature->setMinimumSize(QSize(0, 20));

        gridLayout->addWidget(label_Temperature, 1, 0, 1, 1);


        retranslateUi(unRecognition);

        QMetaObject::connectSlotsByName(unRecognition);
    } // setupUi

    void retranslateUi(QWidget *unRecognition)
    {
        unRecognition->setWindowTitle(QApplication::translate("unRecognition", "unRecognition", Q_NULLPTR));
        label_displayTime->setText(QString());
        label->setText(QString());
        label_Temperature->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class unRecognition: public Ui_unRecognition {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_UNRECOGNITION_H
