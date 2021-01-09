#pragma once

#include <QWidget>
#include "ui_ExcelImport.h"

class ExcelImport : public QWidget
{
	Q_OBJECT

public:
	ExcelImport(QWidget *parent = Q_NULLPTR);
	~ExcelImport();
	void initTablewidget();
private slots:
	void on_btnOpenExcel_clicked();
private:
	Ui::ExcelImport ui;
};
