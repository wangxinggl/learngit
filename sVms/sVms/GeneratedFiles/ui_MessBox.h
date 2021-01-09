/********************************************************************************
** Form generated from reading UI file 'MessBox.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MESSBOX_H
#define UI_MESSBOX_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MessBox
{
public:
    QGridLayout *gridLayout;
    QWidget *widget_title;
    QHBoxLayout *horizontalLayout_2;
    QLabel *lab_Title;
    QWidget *widget_menu;
    QHBoxLayout *horizontalLayout;
    QPushButton *btnMenu_Close;
    QWidget *widget_main;
    QVBoxLayout *verticalLayout_2;
    QWidget *widget;
    QLabel *labIcoMain;
    QLabel *labInfo;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnOk;
    QPushButton *btnCancel;

    void setupUi(QWidget *MessBox)
    {
        if (MessBox->objectName().isEmpty())
            MessBox->setObjectName(QStringLiteral("MessBox"));
        MessBox->resize(377, 242);
        gridLayout = new QGridLayout(MessBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(-1, -1, 3, -1);
        widget_title = new QWidget(MessBox);
        widget_title->setObjectName(QStringLiteral("widget_title"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget_title->sizePolicy().hasHeightForWidth());
        widget_title->setSizePolicy(sizePolicy);
        widget_title->setMinimumSize(QSize(100, 28));
        horizontalLayout_2 = new QHBoxLayout(widget_title);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        lab_Title = new QLabel(widget_title);
        lab_Title->setObjectName(QStringLiteral("lab_Title"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lab_Title->sizePolicy().hasHeightForWidth());
        lab_Title->setSizePolicy(sizePolicy1);
        lab_Title->setStyleSheet(QString::fromUtf8("font: 10pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        lab_Title->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        horizontalLayout_2->addWidget(lab_Title);

        widget_menu = new QWidget(widget_title);
        widget_menu->setObjectName(QStringLiteral("widget_menu"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(widget_menu->sizePolicy().hasHeightForWidth());
        widget_menu->setSizePolicy(sizePolicy2);
        horizontalLayout = new QHBoxLayout(widget_menu);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        btnMenu_Close = new QPushButton(widget_menu);
        btnMenu_Close->setObjectName(QStringLiteral("btnMenu_Close"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(btnMenu_Close->sizePolicy().hasHeightForWidth());
        btnMenu_Close->setSizePolicy(sizePolicy3);
        btnMenu_Close->setMinimumSize(QSize(40, 0));
        btnMenu_Close->setMaximumSize(QSize(40, 16777215));
        btnMenu_Close->setCursor(QCursor(Qt::ArrowCursor));
        btnMenu_Close->setFocusPolicy(Qt::NoFocus);
        QIcon icon;
        icon.addFile(QStringLiteral(":/res/SoftIcon/Cancel.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnMenu_Close->setIcon(icon);
        btnMenu_Close->setIconSize(QSize(25, 25));
        btnMenu_Close->setFlat(true);

        horizontalLayout->addWidget(btnMenu_Close);


        horizontalLayout_2->addWidget(widget_menu);


        gridLayout->addWidget(widget_title, 0, 0, 1, 1);

        widget_main = new QWidget(MessBox);
        widget_main->setObjectName(QStringLiteral("widget_main"));
        widget_main->setStyleSheet(QString::fromUtf8("font: 11pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        verticalLayout_2 = new QVBoxLayout(widget_main);
        verticalLayout_2->setSpacing(5);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(5, 5, 5, 5);
        widget = new QWidget(widget_main);
        widget->setObjectName(QStringLiteral("widget"));
        labIcoMain = new QLabel(widget);
        labIcoMain->setObjectName(QStringLiteral("labIcoMain"));
        labIcoMain->setGeometry(QRect(0, 10, 61, 51));
        labIcoMain->setStyleSheet(QStringLiteral("border-image: url(:/image/info.png);"));
        labIcoMain->setFrameShape(QFrame::NoFrame);
        labInfo = new QLabel(widget);
        labInfo->setObjectName(QStringLiteral("labInfo"));
        labInfo->setGeometry(QRect(70, 10, 261, 101));
        labInfo->setFrameShape(QFrame::NoFrame);
        labInfo->setScaledContents(false);
        labInfo->setWordWrap(true);
        layoutWidget = new QWidget(widget);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(70, 130, 271, 41));
        horizontalLayout_3 = new QHBoxLayout(layoutWidget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        btnOk = new QPushButton(layoutWidget);
        btnOk->setObjectName(QStringLiteral("btnOk"));
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(btnOk->sizePolicy().hasHeightForWidth());
        btnOk->setSizePolicy(sizePolicy4);
        btnOk->setMinimumSize(QSize(90, 35));
        btnOk->setMaximumSize(QSize(70, 30));
        btnOk->setCursor(QCursor(Qt::PointingHandCursor));
        btnOk->setFocusPolicy(Qt::StrongFocus);
        btnOk->setStyleSheet(QStringLiteral(""));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/res/SoftIcon/check.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnOk->setIcon(icon1);
        btnOk->setIconSize(QSize(20, 20));

        horizontalLayout_3->addWidget(btnOk);

        btnCancel = new QPushButton(layoutWidget);
        btnCancel->setObjectName(QStringLiteral("btnCancel"));
        sizePolicy4.setHeightForWidth(btnCancel->sizePolicy().hasHeightForWidth());
        btnCancel->setSizePolicy(sizePolicy4);
        btnCancel->setMinimumSize(QSize(90, 35));
        btnCancel->setMaximumSize(QSize(70, 30));
        btnCancel->setIcon(icon);

        horizontalLayout_3->addWidget(btnCancel);


        verticalLayout_2->addWidget(widget);


        gridLayout->addWidget(widget_main, 1, 0, 1, 1);


        retranslateUi(MessBox);

        QMetaObject::connectSlotsByName(MessBox);
    } // setupUi

    void retranslateUi(QWidget *MessBox)
    {
        MessBox->setWindowTitle(QApplication::translate("MessBox", "MessBox", Q_NULLPTR));
        lab_Title->setText(QString());
#ifndef QT_NO_TOOLTIP
        btnMenu_Close->setToolTip(QApplication::translate("MessBox", "\345\205\263\351\227\255", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        btnMenu_Close->setText(QString());
        labIcoMain->setText(QString());
        labInfo->setText(QString());
        btnOk->setText(QApplication::translate("MessBox", "\347\241\256\345\256\232", Q_NULLPTR));
        btnCancel->setText(QApplication::translate("MessBox", "\345\217\226\346\266\210", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MessBox: public Ui_MessBox {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESSBOX_H
