#include "recognition.h"

Recognition::Recognition(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	displayLib = new QLabel();
	displayPic = new QLabel();
	displayName = new QLabel();
	displayNo = new QLabel();
	displayDevice = new QLabel();
	displayType = new QLabel();
	displayTime = new QLabel();
	displayProgress = new QLabel();
	g_progressBar = new QProgressBar();

	displayPic = ui.label_pic;
	displayLib = ui.label_Lib;
	displayName = ui.label_Name;
	displayNo = ui.label_Number;
	displayDevice = ui.label_Device;
	displayType = ui.label_Type;
	displayTime = ui.label_Time;
	ui.progressBar->setMinimum(0);
	ui.progressBar->setMaximum(100);
	g_progressBar = ui.progressBar;
	
	displayProgress = ui.label_progress;
	setStyleSheet(".Recognition{background:transparent;border:2px solid green;}");

}

Recognition::~Recognition()
{

}
