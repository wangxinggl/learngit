/********************************************************************************
** Form generated from reading UI file 'videoplayback.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIDEOPLAYBACK_H
#define UI_VIDEOPLAYBACK_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateTimeEdit>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_videoPlayback
{
public:
    QGridLayout *gridLayout_2;
    QWidget *widge_Main;
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout_main;
    QWidget *VideoTimeLineBackFrame;
    QGridLayout *gridLayout_3;
    QHBoxLayout *hLayout;
    QHBoxLayout *horizontalLayout;
    QCheckBox *m_chkReplay;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnPlay;
    QPushButton *btnStop;
    QPushButton *btnPre;
    QPushButton *btnNext;
    QPushButton *btnShear;
    QPushButton *btnVoice;
    QSpacerItem *horizontalSpacer_2;
    QWidget *widge_Search;
    QGridLayout *gridLayout;
    QTreeWidget *treeWidget;
    QLabel *label;
    QLabel *label_2;
    QPushButton *btnVSearch;
    QPushButton *btnDowned;
    QPushButton *btnSearchPic;
    QPushButton *btnSearchVideo;
    QTableWidget *tableWidget;
    QDateTimeEdit *dateTimeEdit;
    QDateTimeEdit *dateTimeEdit_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_5;
    QComboBox *comboBox;
    QLineEdit *lineEdit_Search;
    QPushButton *btnExtend;

    void setupUi(QWidget *videoPlayback)
    {
        if (videoPlayback->objectName().isEmpty())
            videoPlayback->setObjectName(QStringLiteral("videoPlayback"));
        videoPlayback->resize(1517, 800);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(videoPlayback->sizePolicy().hasHeightForWidth());
        videoPlayback->setSizePolicy(sizePolicy);
        videoPlayback->setMinimumSize(QSize(1281, 675));
        gridLayout_2 = new QGridLayout(videoPlayback);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        widge_Main = new QWidget(videoPlayback);
        widge_Main->setObjectName(QStringLiteral("widge_Main"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(widge_Main->sizePolicy().hasHeightForWidth());
        widge_Main->setSizePolicy(sizePolicy1);
        gridLayout_4 = new QGridLayout(widge_Main);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        gridLayout_4->setContentsMargins(0, 0, 0, 0);
        gridLayout_main = new QGridLayout();
        gridLayout_main->setSpacing(0);
        gridLayout_main->setObjectName(QStringLiteral("gridLayout_main"));
        gridLayout_main->setContentsMargins(2, 2, 2, 2);

        gridLayout_4->addLayout(gridLayout_main, 0, 0, 1, 1);


        gridLayout_2->addWidget(widge_Main, 0, 2, 1, 1);

        VideoTimeLineBackFrame = new QWidget(videoPlayback);
        VideoTimeLineBackFrame->setObjectName(QStringLiteral("VideoTimeLineBackFrame"));
        VideoTimeLineBackFrame->setMinimumSize(QSize(0, 140));
        VideoTimeLineBackFrame->setMaximumSize(QSize(16777215, 140));
        gridLayout_3 = new QGridLayout(VideoTimeLineBackFrame);
        gridLayout_3->setSpacing(0);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        gridLayout_3->setContentsMargins(0, 0, 3, 0);
        hLayout = new QHBoxLayout();
        hLayout->setSpacing(0);
        hLayout->setObjectName(QStringLiteral("hLayout"));

        gridLayout_3->addLayout(hLayout, 0, 0, 1, 1);


        gridLayout_2->addWidget(VideoTimeLineBackFrame, 2, 2, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(5, 5, 5, 5);
        m_chkReplay = new QCheckBox(videoPlayback);
        m_chkReplay->setObjectName(QStringLiteral("m_chkReplay"));

        horizontalLayout->addWidget(m_chkReplay);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnPlay = new QPushButton(videoPlayback);
        btnPlay->setObjectName(QStringLiteral("btnPlay"));
        btnPlay->setMinimumSize(QSize(30, 30));
        btnPlay->setMaximumSize(QSize(30, 30));
        btnPlay->setStyleSheet(QStringLiteral(""));
        QIcon icon;
        icon.addFile(QStringLiteral(":/res/images/b_play.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnPlay->setIcon(icon);
        btnPlay->setIconSize(QSize(25, 25));

        horizontalLayout->addWidget(btnPlay);

        btnStop = new QPushButton(videoPlayback);
        btnStop->setObjectName(QStringLiteral("btnStop"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(btnStop->sizePolicy().hasHeightForWidth());
        btnStop->setSizePolicy(sizePolicy2);
        btnStop->setMinimumSize(QSize(30, 30));
        btnStop->setMaximumSize(QSize(30, 30));
        btnStop->setStyleSheet(QStringLiteral(""));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/res/images/b_stop.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnStop->setIcon(icon1);
        btnStop->setIconSize(QSize(25, 25));

        horizontalLayout->addWidget(btnStop);

        btnPre = new QPushButton(videoPlayback);
        btnPre->setObjectName(QStringLiteral("btnPre"));
        btnPre->setMinimumSize(QSize(30, 30));
        btnPre->setMaximumSize(QSize(30, 30));
        btnPre->setStyleSheet(QStringLiteral(""));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/res/images/b_pre.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnPre->setIcon(icon2);
        btnPre->setIconSize(QSize(25, 25));

        horizontalLayout->addWidget(btnPre);

        btnNext = new QPushButton(videoPlayback);
        btnNext->setObjectName(QStringLiteral("btnNext"));
        btnNext->setMinimumSize(QSize(30, 30));
        btnNext->setMaximumSize(QSize(30, 30));
        btnNext->setStyleSheet(QStringLiteral(""));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/res/images/b_next.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnNext->setIcon(icon3);
        btnNext->setIconSize(QSize(25, 25));

        horizontalLayout->addWidget(btnNext);

        btnShear = new QPushButton(videoPlayback);
        btnShear->setObjectName(QStringLiteral("btnShear"));
        btnShear->setMinimumSize(QSize(30, 30));
        btnShear->setMaximumSize(QSize(30, 30));
        btnShear->setStyleSheet(QStringLiteral(""));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/res/images/b_cut.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnShear->setIcon(icon4);
        btnShear->setIconSize(QSize(25, 25));

        horizontalLayout->addWidget(btnShear);

        btnVoice = new QPushButton(videoPlayback);
        btnVoice->setObjectName(QStringLiteral("btnVoice"));
        btnVoice->setMinimumSize(QSize(30, 30));
        btnVoice->setMaximumSize(QSize(30, 30));
        btnVoice->setStyleSheet(QStringLiteral(""));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/res/images/voiceClose.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnVoice->setIcon(icon5);
        btnVoice->setIconSize(QSize(25, 25));

        horizontalLayout->addWidget(btnVoice);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        gridLayout_2->addLayout(horizontalLayout, 1, 2, 1, 1);

        widge_Search = new QWidget(videoPlayback);
        widge_Search->setObjectName(QStringLiteral("widge_Search"));
        widge_Search->setMinimumSize(QSize(280, 0));
        widge_Search->setMaximumSize(QSize(280, 16777215));
        gridLayout = new QGridLayout(widge_Search);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(2, 2, 2, 2);
        treeWidget = new QTreeWidget(widge_Search);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        treeWidget->setHeaderItem(__qtreewidgetitem);
        treeWidget->setObjectName(QStringLiteral("treeWidget"));
        sizePolicy1.setHeightForWidth(treeWidget->sizePolicy().hasHeightForWidth());
        treeWidget->setSizePolicy(sizePolicy1);
        treeWidget->setColumnCount(1);

        gridLayout->addWidget(treeWidget, 1, 0, 1, 3);

        label = new QLabel(widge_Search);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(16777215, 30));

        gridLayout->addWidget(label, 2, 0, 1, 1);

        label_2 = new QLabel(widge_Search);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMaximumSize(QSize(16777215, 30));

        gridLayout->addWidget(label_2, 4, 0, 1, 1);

        btnVSearch = new QPushButton(widge_Search);
        btnVSearch->setObjectName(QStringLiteral("btnVSearch"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(btnVSearch->sizePolicy().hasHeightForWidth());
        btnVSearch->setSizePolicy(sizePolicy3);
        btnVSearch->setMinimumSize(QSize(50, 0));

        gridLayout->addWidget(btnVSearch, 7, 0, 1, 1);

        btnDowned = new QPushButton(widge_Search);
        btnDowned->setObjectName(QStringLiteral("btnDowned"));
        sizePolicy3.setHeightForWidth(btnDowned->sizePolicy().hasHeightForWidth());
        btnDowned->setSizePolicy(sizePolicy3);
        btnDowned->setMinimumSize(QSize(50, 0));

        gridLayout->addWidget(btnDowned, 7, 2, 1, 1);

        btnSearchPic = new QPushButton(widge_Search);
        btnSearchPic->setObjectName(QStringLiteral("btnSearchPic"));
        sizePolicy3.setHeightForWidth(btnSearchPic->sizePolicy().hasHeightForWidth());
        btnSearchPic->setSizePolicy(sizePolicy3);
        btnSearchPic->setMinimumSize(QSize(50, 0));

        gridLayout->addWidget(btnSearchPic, 8, 0, 1, 1);

        btnSearchVideo = new QPushButton(widge_Search);
        btnSearchVideo->setObjectName(QStringLiteral("btnSearchVideo"));
        sizePolicy3.setHeightForWidth(btnSearchVideo->sizePolicy().hasHeightForWidth());
        btnSearchVideo->setSizePolicy(sizePolicy3);
        btnSearchVideo->setMinimumSize(QSize(50, 0));

        gridLayout->addWidget(btnSearchVideo, 8, 2, 1, 1);

        tableWidget = new QTableWidget(widge_Search);
        tableWidget->setObjectName(QStringLiteral("tableWidget"));
        sizePolicy1.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(tableWidget, 9, 0, 1, 3);

        dateTimeEdit = new QDateTimeEdit(widge_Search);
        dateTimeEdit->setObjectName(QStringLiteral("dateTimeEdit"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(dateTimeEdit->sizePolicy().hasHeightForWidth());
        dateTimeEdit->setSizePolicy(sizePolicy4);
        dateTimeEdit->setWrapping(false);
        dateTimeEdit->setReadOnly(false);
        dateTimeEdit->setAccelerated(false);
        dateTimeEdit->setProperty("showGroupSeparator", QVariant(false));
        dateTimeEdit->setDateTime(QDateTime(QDate(2019, 4, 29), QTime(11, 41, 0)));
        dateTimeEdit->setCurrentSection(QDateTimeEdit::HourSection);
        dateTimeEdit->setCalendarPopup(true);

        gridLayout->addWidget(dateTimeEdit, 3, 0, 1, 3);

        dateTimeEdit_2 = new QDateTimeEdit(widge_Search);
        dateTimeEdit_2->setObjectName(QStringLiteral("dateTimeEdit_2"));
        dateTimeEdit_2->setReadOnly(false);
        dateTimeEdit_2->setDateTime(QDateTime(QDate(2019, 4, 30), QTime(12, 0, 5)));
        dateTimeEdit_2->setCalendarPopup(true);

        gridLayout->addWidget(dateTimeEdit_2, 5, 0, 1, 3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_5 = new QLabel(widge_Search);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_2->addWidget(label_5);

        comboBox = new QComboBox(widge_Search);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        horizontalLayout_2->addWidget(comboBox);


        gridLayout->addLayout(horizontalLayout_2, 6, 0, 1, 3);

        lineEdit_Search = new QLineEdit(widge_Search);
        lineEdit_Search->setObjectName(QStringLiteral("lineEdit_Search"));

        gridLayout->addWidget(lineEdit_Search, 0, 0, 1, 3);


        gridLayout_2->addWidget(widge_Search, 0, 4, 3, 1);

        btnExtend = new QPushButton(videoPlayback);
        btnExtend->setObjectName(QStringLiteral("btnExtend"));
        sizePolicy1.setHeightForWidth(btnExtend->sizePolicy().hasHeightForWidth());
        btnExtend->setSizePolicy(sizePolicy1);
        btnExtend->setMaximumSize(QSize(12, 16777215));
        QIcon icon6;
        icon6.addFile(QStringLiteral(":/res/SoftIcon/you.png"), QSize(), QIcon::Normal, QIcon::Off);
        btnExtend->setIcon(icon6);

        gridLayout_2->addWidget(btnExtend, 0, 3, 3, 1);


        retranslateUi(videoPlayback);

        QMetaObject::connectSlotsByName(videoPlayback);
    } // setupUi

    void retranslateUi(QWidget *videoPlayback)
    {
        videoPlayback->setWindowTitle(QApplication::translate("videoPlayback", "videoPlayback", Q_NULLPTR));
        m_chkReplay->setText(QApplication::translate("videoPlayback", "\345\220\214\346\255\245\346\216\247\345\210\266", Q_NULLPTR));
        btnPlay->setText(QString());
        btnStop->setText(QString());
        btnPre->setText(QString());
        btnNext->setText(QString());
        btnShear->setText(QString());
        btnVoice->setText(QString());
        label->setText(QApplication::translate("videoPlayback", "\345\274\200\345\247\213\346\227\266\351\227\264", Q_NULLPTR));
        label_2->setText(QApplication::translate("videoPlayback", "\347\273\223\346\235\237\346\227\266\351\227\264", Q_NULLPTR));
        btnVSearch->setText(QApplication::translate("videoPlayback", "\346\220\234\347\264\242", Q_NULLPTR));
        btnDowned->setText(QApplication::translate("videoPlayback", "\344\270\213\350\275\275", Q_NULLPTR));
        btnSearchPic->setText(QApplication::translate("videoPlayback", "\344\273\245\345\233\276\346\220\234\345\233\276", Q_NULLPTR));
        btnSearchVideo->setText(QApplication::translate("videoPlayback", "\344\273\245\345\233\276\346\220\234\345\275\225\345\203\217", Q_NULLPTR));
        label_5->setText(QApplication::translate("videoPlayback", "\346\226\207\344\273\266\347\261\273\345\236\213", Q_NULLPTR));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("videoPlayback", "\345\205\250\351\203\250", Q_NULLPTR)
         << QApplication::translate("videoPlayback", "\346\212\245\350\255\246\345\275\225\345\203\217", Q_NULLPTR)
         << QApplication::translate("videoPlayback", "\345\256\232\346\227\266\345\275\225\345\203\217", Q_NULLPTR)
         << QApplication::translate("videoPlayback", "\345\233\276\347\211\207\346\226\207\344\273\266", Q_NULLPTR)
         << QApplication::translate("videoPlayback", "\344\272\272\350\204\270\345\233\276\347\211\207", Q_NULLPTR)
         << QApplication::translate("videoPlayback", "\350\275\246\347\211\214\345\233\276\347\211\207", Q_NULLPTR)
         << QApplication::translate("videoPlayback", "WiFi\346\216\242\351\222\210\344\277\241\346\201\257", Q_NULLPTR)
        );
        btnExtend->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class videoPlayback: public Ui_videoPlayback {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIDEOPLAYBACK_H
