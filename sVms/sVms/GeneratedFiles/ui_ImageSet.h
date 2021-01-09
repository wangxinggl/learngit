/********************************************************************************
** Form generated from reading UI file 'ImageSet.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGESET_H
#define UI_IMAGESET_H

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
#include <QtWidgets/QSlider>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ImageSet
{
public:
    QTabWidget *tabWidget;
    QWidget *tab;
    QPushButton *pushButton;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_2;
    QSlider *horizontalSlider;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label_3;
    QSlider *horizontalSlider_2;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_4;
    QSlider *horizontalSlider_3;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_5;
    QSlider *horizontalSlider_4;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_6;
    QSlider *horizontalSlider_5;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_7;
    QSlider *horizontalSlider_6;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_8;
    QSlider *horizontalSlider_7;
    QWidget *tab_2;
    QCheckBox *checkBox;
    QLabel *label_10;
    QComboBox *comboBox_3;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label_9;
    QComboBox *comboBox_2;
    QWidget *tab_3;
    QCheckBox *checkBox_2;
    QCheckBox *checkBox_3;
    QWidget *layoutWidget2;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_11;
    QComboBox *comboBox_4;
    QWidget *layoutWidget3;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_12;
    QComboBox *comboBox_5;
    QWidget *layoutWidget4;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *comboBox;
    QPushButton *btnClose;

    void setupUi(QDialog *ImageSet)
    {
        if (ImageSet->objectName().isEmpty())
            ImageSet->setObjectName(QStringLiteral("ImageSet"));
        ImageSet->resize(1089, 670);
        tabWidget = new QTabWidget(ImageSet);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(766, 110, 311, 541));
        tabWidget->setTabPosition(QTabWidget::West);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        pushButton = new QPushButton(tab);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(180, 490, 75, 23));
        layoutWidget = new QWidget(tab);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(20, 20, 251, 371));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QStringLiteral("horizontalLayout_8"));
        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        horizontalLayout_8->addWidget(label_2);

        horizontalSlider = new QSlider(layoutWidget);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_8->addWidget(horizontalSlider);


        verticalLayout->addLayout(horizontalLayout_8);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        horizontalLayout_7->addWidget(label_3);

        horizontalSlider_2 = new QSlider(layoutWidget);
        horizontalSlider_2->setObjectName(QStringLiteral("horizontalSlider_2"));
        horizontalSlider_2->setOrientation(Qt::Horizontal);

        horizontalLayout_7->addWidget(horizontalSlider_2);


        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_6->addWidget(label_4);

        horizontalSlider_3 = new QSlider(layoutWidget);
        horizontalSlider_3->setObjectName(QStringLiteral("horizontalSlider_3"));
        horizontalSlider_3->setOrientation(Qt::Horizontal);

        horizontalLayout_6->addWidget(horizontalSlider_3);


        verticalLayout->addLayout(horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_5->addWidget(label_5);

        horizontalSlider_4 = new QSlider(layoutWidget);
        horizontalSlider_4->setObjectName(QStringLiteral("horizontalSlider_4"));
        horizontalSlider_4->setOrientation(Qt::Horizontal);

        horizontalLayout_5->addWidget(horizontalSlider_4);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QStringLiteral("label_6"));

        horizontalLayout_4->addWidget(label_6);

        horizontalSlider_5 = new QSlider(layoutWidget);
        horizontalSlider_5->setObjectName(QStringLiteral("horizontalSlider_5"));
        horizontalSlider_5->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(horizontalSlider_5);


        verticalLayout->addLayout(horizontalLayout_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        horizontalLayout_3->addWidget(label_7);

        horizontalSlider_6 = new QSlider(layoutWidget);
        horizontalSlider_6->setObjectName(QStringLiteral("horizontalSlider_6"));
        horizontalSlider_6->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(horizontalSlider_6);


        verticalLayout->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_8 = new QLabel(layoutWidget);
        label_8->setObjectName(QStringLiteral("label_8"));

        horizontalLayout_2->addWidget(label_8);

        horizontalSlider_7 = new QSlider(layoutWidget);
        horizontalSlider_7->setObjectName(QStringLiteral("horizontalSlider_7"));
        horizontalSlider_7->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(horizontalSlider_7);


        verticalLayout->addLayout(horizontalLayout_2);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        checkBox = new QCheckBox(tab_2);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(70, 70, 121, 16));
        label_10 = new QLabel(tab_2);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(20, 110, 81, 16));
        comboBox_3 = new QComboBox(tab_2);
        comboBox_3->setObjectName(QStringLiteral("comboBox_3"));
        comboBox_3->setGeometry(QRect(100, 110, 131, 22));
        layoutWidget1 = new QWidget(tab_2);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(30, 40, 201, 22));
        horizontalLayout_9 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName(QStringLiteral("horizontalLayout_9"));
        horizontalLayout_9->setContentsMargins(0, 0, 0, 0);
        label_9 = new QLabel(layoutWidget1);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_9->addWidget(label_9);

        comboBox_2 = new QComboBox(layoutWidget1);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));

        horizontalLayout_9->addWidget(comboBox_2);

        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        checkBox_2 = new QCheckBox(tab_3);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));
        checkBox_2->setGeometry(QRect(80, 60, 71, 16));
        checkBox_3 = new QCheckBox(tab_3);
        checkBox_3->setObjectName(QStringLiteral("checkBox_3"));
        checkBox_3->setGeometry(QRect(80, 90, 71, 16));
        layoutWidget2 = new QWidget(tab_3);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(30, 20, 191, 22));
        horizontalLayout_10 = new QHBoxLayout(layoutWidget2);
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_10->setObjectName(QStringLiteral("horizontalLayout_10"));
        horizontalLayout_10->setContentsMargins(0, 0, 0, 0);
        label_11 = new QLabel(layoutWidget2);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_10->addWidget(label_11);

        comboBox_4 = new QComboBox(layoutWidget2);
        comboBox_4->setObjectName(QStringLiteral("comboBox_4"));

        horizontalLayout_10->addWidget(comboBox_4);

        layoutWidget3 = new QWidget(tab_3);
        layoutWidget3->setObjectName(QStringLiteral("layoutWidget3"));
        layoutWidget3->setGeometry(QRect(40, 110, 181, 22));
        horizontalLayout_11 = new QHBoxLayout(layoutWidget3);
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_11->setObjectName(QStringLiteral("horizontalLayout_11"));
        horizontalLayout_11->setContentsMargins(0, 0, 0, 0);
        label_12 = new QLabel(layoutWidget3);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setMaximumSize(QSize(50, 16777215));

        horizontalLayout_11->addWidget(label_12);

        comboBox_5 = new QComboBox(layoutWidget3);
        comboBox_5->setObjectName(QStringLiteral("comboBox_5"));

        horizontalLayout_11->addWidget(comboBox_5);

        tabWidget->addTab(tab_3, QString());
        layoutWidget4 = new QWidget(ImageSet);
        layoutWidget4->setObjectName(QStringLiteral("layoutWidget4"));
        layoutWidget4->setGeometry(QRect(820, 80, 231, 22));
        horizontalLayout = new QHBoxLayout(layoutWidget4);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget4);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(80, 16777215));

        horizontalLayout->addWidget(label);

        comboBox = new QComboBox(layoutWidget4);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(comboBox);

        btnClose = new QPushButton(ImageSet);
        btnClose->setObjectName(QStringLiteral("btnClose"));
        btnClose->setGeometry(QRect(1050, 10, 30, 30));
        btnClose->setMinimumSize(QSize(30, 30));
        btnClose->setMaximumSize(QSize(30, 30));
        QIcon icon;
        icon.addFile(QStringLiteral(":/res/SoftIcon/Cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnClose->setIcon(icon);
        btnClose->setIconSize(QSize(30, 30));

        retranslateUi(ImageSet);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ImageSet);
    } // setupUi

    void retranslateUi(QDialog *ImageSet)
    {
        ImageSet->setWindowTitle(QApplication::translate("ImageSet", "ImageSet", Q_NULLPTR));
        pushButton->setText(QApplication::translate("ImageSet", "\351\273\230\350\256\244", Q_NULLPTR));
        label_2->setText(QApplication::translate("ImageSet", "  \344\272\256 \345\272\246   ", Q_NULLPTR));
        label_3->setText(QApplication::translate("ImageSet", "  \345\257\271\346\257\224\345\272\246  ", Q_NULLPTR));
        label_4->setText(QApplication::translate("ImageSet", "  \351\245\261\345\222\214\345\272\246  ", Q_NULLPTR));
        label_5->setText(QApplication::translate("ImageSet", "  \350\211\262 \345\272\246   ", Q_NULLPTR));
        label_6->setText(QApplication::translate("ImageSet", "  \351\224\220 \345\272\246   ", Q_NULLPTR));
        label_7->setText(QApplication::translate("ImageSet", "\346\225\260\345\255\227\345\256\275\345\212\250\345\272\246", Q_NULLPTR));
        label_8->setText(QApplication::translate("ImageSet", "\347\201\257\344\272\256\346\234\200\345\244\247\345\200\274", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("ImageSet", "\345\233\276\345\203\217", Q_NULLPTR));
        checkBox->setText(QApplication::translate("ImageSet", "\344\272\272\350\204\270\346\231\272\350\203\275\346\233\235\345\205\211\346\250\241\345\274\217", Q_NULLPTR));
        label_10->setText(QApplication::translate("ImageSet", "\350\275\257\345\205\211\346\225\217\347\201\265\346\225\217\345\272\246", Q_NULLPTR));
        label_9->setText(QApplication::translate("ImageSet", "\346\233\235\345\205\211\346\227\266\351\227\264", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("ImageSet", "\346\233\235\345\205\211", Q_NULLPTR));
        checkBox_2->setText(QApplication::translate("ImageSet", "\345\267\246\345\217\263\351\225\234\345\203\217", Q_NULLPTR));
        checkBox_3->setText(QApplication::translate("ImageSet", "\344\270\212\344\270\213\347\277\273\350\275\254", Q_NULLPTR));
        label_11->setText(QApplication::translate("ImageSet", "\346\227\245\345\244\234\346\243\200\346\265\213\346\250\241\345\274\217", Q_NULLPTR));
        label_12->setText(QApplication::translate("ImageSet", "\350\247\206\351\242\221\345\210\266\345\274\217", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("ImageSet", "\346\227\245\345\244\234\346\250\241\345\274\217", Q_NULLPTR));
        label->setText(QApplication::translate("ImageSet", "\351\200\232\351\201\223", Q_NULLPTR));
        btnClose->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ImageSet: public Ui_ImageSet {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGESET_H
