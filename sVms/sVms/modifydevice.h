#ifndef MODIFYDEVICE_H
#define MODIFYDEVICE_H

#include <QWidget>
#include "ui_modifydevice.h"
#include <QLineEdit>
#include <QComboBox>
#include "table_structs.h"
#include "DB.h"
#include "clickedlabel.h"
#include <QDialog>

class ModifyDevice : public QWidget
{
	Q_OBJECT

public:
	ModifyDevice(QWidget *parent = 0);
	~ModifyDevice();
	void initForm();
	TabDevInfo_t* m_pDevInfo;
	TabDevInfo_t* m_pNewDevInfo;
private slots:
	void on_btnSure_clicked();
	void on_btnCancel_clicked();
	void on_btnClose_clicked();
private:
	Ui::ModifyDevice ui;
public:
	QLineEdit *m_displayName;
	QLineEdit *m_displayIP;
	QLineEdit *m_displayPort;
	QLineEdit *m_displayUsr;
	QLineEdit *m_displayPwd;
	QComboBox *m_displySubType;
	QComboBox *m_displayChannel;

	
};

#endif // MODIFYDEVICE_H
