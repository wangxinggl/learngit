#ifndef MODIFYDEVICE_H
#define MODIFYDEVICE_H

#include <QWidget>
#include "ui_modifydevice.h"
#include <QLineEdit>
#include <QComboBox>
#include "table_structs.h"
#include "DB.h"
#include "clickedlabel.h"


class ModifyDevice : public QWidget
{
	Q_OBJECT

public:
	ModifyDevice(QWidget *parent = 0);
	~ModifyDevice();
	void initForm();

private slots:
	void on_btnSure_clicked();
	void on_btnCancel_clicked();
	void on_btnClose_clicked();
private:
	Ui::ModifyDevice ui;
	TabDevInfo_t devInfo;
public:
	QLineEdit *m_displayName;
	QLineEdit *m_displayIP;
	QLineEdit *m_displayPort;
	QLineEdit *m_displayUsr;
	QLineEdit *m_displayPwd;
	QComboBox *m_displySubType;

	
};

#endif // MODIFYDEVICE_H
