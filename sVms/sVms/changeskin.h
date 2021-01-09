#ifndef CHANGESKIN_H
#define CHANGESKIN_H

#include <QDialog>
#include "ui_changeskin.h"
#include "clickedlabel.h"
#include "myhelper.h"
#include "iconhelper.h"


class changeSkin : public QDialog
{
	Q_OBJECT

public:
	changeSkin(QWidget *parent = 0);
	~changeSkin();
	
public slots:
	void on_black_label_clicked();
	void on_mei_label_clicked();
	void on_sky_label_clicked();
	void on_hui_label_clicked();
	void on_gray_label_clicked();
	void on_wathetgray_label_clicked();
	void on_darkgray_label_clicked();
	void on_sliver_label_clicked();
	void on_flatblack_label_clicked();
	void on_darkblack_label_clicked();
	void on_btnClose_clicked();
private:
	Ui::changeSkin ui;
	
};

#endif // CHANGESKIN_H
