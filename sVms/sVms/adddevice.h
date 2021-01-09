#ifndef ADDDEVICE_H
#define ADDDEVICE_H

#include <QWidget>
#include "ui_adddevice.h"
#include "DB.h"


class AddDevice : public QWidget
{
	Q_OBJECT

public:
	AddDevice(QWidget *parent = 0);
	~AddDevice();

	
private slots:
	void on_btnSure_clicked();
	void on_radioButton_paragr_clicked();
	void on_radioButton_name_clicked();
	void on_btnCancel_clicked();
	void on_btnClose_clicked();
private:
	Ui::AddDevice ui;
	int m_Select;
	int m_nCompany;
};

#endif // ADDDEVICE_H
