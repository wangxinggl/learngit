#include "ExcelImport.h"
#include <QFileDialog>
#include <QStandardPaths>
#pragma execution_character_set("utf-8")

ExcelImport::ExcelImport(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	initTablewidget();
}

ExcelImport::~ExcelImport()
{
}

void ExcelImport::initTablewidget()
{
	QStringList header;
	ui.tableWidget->setColumnCount(8);

	header << QObject::tr("编号") << QObject::tr("姓名") << QObject::tr("性别") << QObject::tr("身份证号") << QObject::tr("家庭地址") << QObject::tr("电话") << QObject::tr("岗位")<<QObject::tr("备注");
	ui.tableWidget->setHorizontalHeaderLabels(header);
	ui.tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);  //整行选中的方式
	ui.tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);   //禁止修改
	ui.tableWidget->setSortingEnabled(true);
	ui.tableWidget->horizontalHeader()->setStretchLastSection(true); //就是这个地方
	ui.tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch); //自适应列宽
	ui.tableWidget->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch); //自适应行高
}
void ExcelImport::on_btnOpenExcel_clicked()
{
	QString m_file = QFileDialog::getOpenFileName(this, QObject::tr("打开"), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation), QObject::tr("表格文件( *.xlsx)"));
	ui.lineEdit->setText(m_file);
}