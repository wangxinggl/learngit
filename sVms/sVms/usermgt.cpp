#include "usermgt.h"
#include <QMessageBox>
#include "myhelper.h"
#include "db.h"

UserMgt::UserMgt(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	

	initFresh();
	initSearchButton();
	//设置初始化时候删除按键不可用
	ui.btnDel->setEnabled(false);
	connect(ui.tableView,SIGNAL(clicked(const QModelIndex &)),this,SLOT(slotRowDoubleClicked()));
	add = new addUser();
	connect(add, SIGNAL(sendMsg(bool)), this, SLOT(getMsg(bool)));
}

UserMgt::~UserMgt()
{

}
void UserMgt::initSearchButton()
{
	QPushButton *pSearchButton = new QPushButton(this);

	pSearchButton->setCursor(Qt::PointingHandCursor);
	pSearchButton->setFixedSize(22, 22);
	pSearchButton->setToolTip(QStringLiteral("搜索"));
	pSearchButton->setStyleSheet("QPushButton{border-image:url(:/res/SoftIcon/icon_search_normal.png); background:transparent;} \
								 								 								 								 								 								 								 								QPushButton:hover{border-image:url(:/res/SoftIcon/icon_search_hover.png)} \
																																																																																																																																																																																																																																																																																								QPushButton:pressed{border-image:url(:/res/SoftIcon/icon_search_press.png)}");
	QMargins margins = ui.lineEdit->textMargins();
	ui.lineEdit->setTextMargins(margins.left(), margins.top(), pSearchButton->width(), margins.bottom());
	ui.lineEdit->setPlaceholderText(QStringLiteral("请输入搜索内容"));

	QHBoxLayout *pSearchLayout = new QHBoxLayout();
	pSearchLayout->addStretch();
	pSearchLayout->addWidget(pSearchButton);
	pSearchLayout->setSpacing(0);
	pSearchLayout->setContentsMargins(0, 0, 0, 0);
	ui.lineEdit->setLayout(pSearchLayout);
	connect(pSearchButton, SIGNAL(clicked(bool)), this, SLOT(on_btnSearch_clicked()));
}
void UserMgt::getMsg(bool Flag)
{
	if (Flag)
	{
		initFresh();
	}
}
void UserMgt::initFresh()
{
	//设置模型
	model = new QSqlTableModel(this, g_pDatabase->getDB());
	model->setTable("UserInfo");
	//把model放在view
	ui.tableView->setModel(model);

	//model显示数据
	model->select();
	model->setHeaderData(0, Qt::Horizontal, QObject::tr("索引"));
	model->setHeaderData(1, Qt::Horizontal, QObject::tr("用户名"));
	model->setHeaderData(3, Qt::Horizontal, QObject::tr("性别"));
	model->setHeaderData(4, Qt::Horizontal, QObject::tr("联系方式"));
	model->setEditStrategy(QSqlTableModel::OnManualSubmit);
	ui.tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
	ui.tableView->verticalHeader()->setVisible(false);
	ui.tableView->horizontalHeader()->setStretchLastSection(true);
	ui.tableView->setColumnHidden(2, true);
	ui.tableView->setSortingEnabled(true);
	//设置数据库不允许修改
	ui.tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}
void UserMgt::timerupdate()
{
	initFresh();
}
void UserMgt::on_btnAdd_clicked()
{
	
	add->show();
	
}

void UserMgt::on_btnModify_clicked()
{
	QString userName;
	QItemSelectionModel *sModel = ui.tableView->selectionModel();

	//取出模型中的索引
	QModelIndexList list = sModel->selectedRows();

	//删除所有选中的行
	for (int i = 0; i < list.size(); i++)
	{
		QModelIndex index = model->index(list.at(i).row(), 1);
		userName = model->data(index).toString();
		if (userName == "admin")
		{
			myHelper::ShowMessageBoxWarning(QObject::tr("不能修改admin"));
			return;
		}
	}
	mod = new modifyUser();
	mod->lineEdit_user->setText(userName);
	mod->show();
}

void UserMgt::on_btnDel_clicked()
{
	QItemSelectionModel *sModel = ui.tableView->selectionModel();
	
	//取出模型中的索引
	QModelIndexList list = sModel->selectedRows();
	
	//删除所有选中的行
	for(int i = 0;i < list.size();i++)
	{
		QModelIndex index = model->index(list.at(i).row(), 1);
		QString userName = model->data(index).toString();
		if (userName == "admin")
		{
			myHelper::ShowMessageBoxWarning(QObject::tr("当前用户是管理员用户不可删除"));
			return;
		}
		model->removeRow(list.at(i).row());
	}
	model->submitAll();
}

void UserMgt::slotRowDoubleClicked()
{
	ui.btnDel->setEnabled(true);
}

void UserMgt::on_btnSearch_clicked()
{
	if (ui.lineEdit->text() == NULL)
	{
		//QMessageBox::warning(this,QObject::tr("警告"),QObject::tr("请输入用户名"));
		//myHelper::ShowMessageBoxWarning(QObject::tr("请输入用户名!"));
		//return;
		initFresh();
		return;
	}
	QString str = ui.lineEdit->text();
	QString name = QString("UserName = '%1'").arg(str);
	model->setFilter(name);
	model->select();
}