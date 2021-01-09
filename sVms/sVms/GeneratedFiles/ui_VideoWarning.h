/********************************************************************************
** Form generated from reading UI file 'VideoWarning.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEOWARNING_H
#define UI_VIDEOWARNING_H

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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VideoWarning
{
public:
    QPushButton *btnClose;
    QComboBox *comboBox;
    QLabel *label;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QComboBox *comboBox_2;
    QPushButton *btnAreaSet;
    QPushButton *btnAll;
    QPushButton *btnSave;
    QPushButton *btnClear;
    QCheckBox *checkBox;

    void setupUi(QDialog *VideoWarning)
    {
        if (VideoWarning->objectName().isEmpty())
            VideoWarning->setObjectName(QStringLiteral("VideoWarning"));
        VideoWarning->resize(1020, 669);
        btnClose = new QPushButton(VideoWarning);
        btnClose->setObjectName(QStringLiteral("btnClose"));
        btnClose->setGeometry(QRect(980, 10, 30, 30));
        btnClose->setMinimumSize(QSize(30, 30));
        btnClose->setMaximumSize(QSize(30, 30));
        QIcon icon;
        icon.addFile(QStringLiteral(":/res/SoftIcon/Cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnClose->setIcon(icon);
        btnClose->setIconSize(QSize(30, 30));
        comboBox = new QComboBox(VideoWarning);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(880, 80, 121, 22));
        label = new QLabel(VideoWarning);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(820, 80, 51, 20));
        layoutWidget = new QWidget(VideoWarning);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(880, 150, 121, 22));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout->addWidget(label_2);

        comboBox_2 = new QComboBox(layoutWidget);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBox_2->sizePolicy().hasHeightForWidth());
        comboBox_2->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(comboBox_2);

        btnAreaSet = new QPushButton(VideoWarning);
        btnAreaSet->setObjectName(QStringLiteral("btnAreaSet"));
        btnAreaSet->setGeometry(QRect(890, 210, 91, 31));
        sizePolicy.setHeightForWidth(btnAreaSet->sizePolicy().hasHeightForWidth());
        btnAreaSet->setSizePolicy(sizePolicy);
        btnAll = new QPushButton(VideoWarning);
        btnAll->setObjectName(QStringLiteral("btnAll"));
        btnAll->setGeometry(QRect(890, 290, 91, 31));
        sizePolicy.setHeightForWidth(btnAll->sizePolicy().hasHeightForWidth());
        btnAll->setSizePolicy(sizePolicy);
        btnSave = new QPushButton(VideoWarning);
        btnSave->setObjectName(QStringLiteral("btnSave"));
        btnSave->setGeometry(QRect(890, 450, 91, 31));
        btnClear = new QPushButton(VideoWarning);
        btnClear->setObjectName(QStringLiteral("btnClear"));
        btnClear->setGeometry(QRect(890, 370, 91, 31));
        sizePolicy.setHeightForWidth(btnClear->sizePolicy().hasHeightForWidth());
        btnClear->setSizePolicy(sizePolicy);
        checkBox = new QCheckBox(VideoWarning);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(910, 110, 71, 16));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(checkBox->sizePolicy().hasHeightForWidth());
        checkBox->setSizePolicy(sizePolicy1);

        retranslateUi(VideoWarning);

        QMetaObject::connectSlotsByName(VideoWarning);
    } // setupUi

    void retranslateUi(QDialog *VideoWarning)
    {
        VideoWarning->setWindowTitle(QApplication::translate("VideoWarning", "VideoWarning", Q_NULLPTR));
        btnClose->setText(QString());
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("VideoWarning", "\344\272\272\345\275\242\344\276\246\346\265\213\346\212\245\350\255\246", Q_NULLPTR)
         << QApplication::translate("VideoWarning", "\344\272\272\345\275\242\350\266\212\347\225\214\346\212\245\350\255\246", Q_NULLPTR)
         << QApplication::translate("VideoWarning", "\344\272\272\350\204\270\344\276\246\346\265\213\346\212\245\350\255\246", Q_NULLPTR)
         << QApplication::translate("VideoWarning", "\344\272\272\350\204\270\350\266\212\347\225\214\346\212\245\350\255\246", Q_NULLPTR)
         << QString()
        );
        label->setText(QApplication::translate("VideoWarning", "\346\212\245\350\255\246\347\261\273\345\210\253", Q_NULLPTR));
        label_2->setText(QApplication::translate("VideoWarning", "\351\200\232\351\201\223", Q_NULLPTR));
        btnAreaSet->setText(QApplication::translate("VideoWarning", "\346\243\200\346\265\213\345\214\272\345\237\237\350\256\276\347\275\256", Q_NULLPTR));
        btnAll->setText(QApplication::translate("VideoWarning", "\345\205\250\351\203\250", Q_NULLPTR));
        btnSave->setText(QApplication::translate("VideoWarning", "\344\277\235\345\255\230", Q_NULLPTR));
        btnClear->setText(QApplication::translate("VideoWarning", "\346\270\205\351\231\244", Q_NULLPTR));
        checkBox->setText(QApplication::translate("VideoWarning", "\345\220\257\347\224\250", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class VideoWarning: public Ui_VideoWarning {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEOWARNING_H
