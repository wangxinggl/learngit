#ifndef UNRECOGNITION_H
#define UNRECOGNITION_H

#include <QWidget>
#include "ui_unrecognition.h"
#include <QLabel>
#include "table_structs.h"

class unRecognition : public QWidget
{
	Q_OBJECT

public:
	unRecognition(QWidget *parent = 0);
	~unRecognition();

public:
	Ui::unRecognition ui;

	void ShowInfo(SMART_FACE_CMP_QUERY_INFO *pCompareInfoTmp, BOOL bInVailid, QString pszStatus);
private:
	char* m_pPicName;
	char* m_pSnapPath;
	char* m_pszTime;
	QString m_strImagePath;
	QString m_strSnapTime;
	QImage m_Image;
};

#endif // UNRECOGNITION_H
