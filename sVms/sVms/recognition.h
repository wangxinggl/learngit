#ifndef RECOGNITION_H
#define RECOGNITION_H

#include <QWidget>
#include "ui_recognition.h"
#include <QLabel>
#include <QProgressBar>
#include <QLineEdit>
#include "table_structs.h"

class Recognition : public QWidget
{
	Q_OBJECT

public:
	Recognition(QWidget *parent = 0);
	~Recognition();

private:
	QImage m_pImagePic;
	QImage m_pImageLib;
	char* m_pPicName;
	char* m_pLibName;
	char* m_pSnapPath;
	char* m_pTime;
public:
	Ui::Recognition ui;
	void ShowInfo(SMART_FACE_CMP_QUERY_INFO *pCompareInfoTmp, int nInvalid, QString strStatus);
};

#endif // RECOGNITION_H
