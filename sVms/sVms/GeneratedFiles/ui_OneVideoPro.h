/********************************************************************************
** Form generated from reading UI file 'OneVideoPro.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ONEVIDEOPRO_H
#define UI_ONEVIDEOPRO_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OneVideoPro
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QLabel *label;

    void setupUi(QMainWindow *OneVideoPro)
    {
        if (OneVideoPro->objectName().isEmpty())
            OneVideoPro->setObjectName(QStringLiteral("OneVideoPro"));
        OneVideoPro->resize(400, 299);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(OneVideoPro->sizePolicy().hasHeightForWidth());
        OneVideoPro->setSizePolicy(sizePolicy);
        OneVideoPro->setStyleSheet(QStringLiteral(""));
        centralWidget = new QWidget(OneVideoPro);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setFocusPolicy(Qt::NoFocus);
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(0);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setFocusPolicy(Qt::NoFocus);
        label->setStyleSheet(QStringLiteral(""));
        label->setFrameShape(QFrame::NoFrame);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        OneVideoPro->setCentralWidget(centralWidget);

        retranslateUi(OneVideoPro);

        QMetaObject::connectSlotsByName(OneVideoPro);
    } // setupUi

    void retranslateUi(QMainWindow *OneVideoPro)
    {
        OneVideoPro->setWindowTitle(QApplication::translate("OneVideoPro", "OneVideoPro", Q_NULLPTR));
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class OneVideoPro: public Ui_OneVideoPro {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ONEVIDEOPRO_H
