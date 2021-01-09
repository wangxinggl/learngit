#ifndef ELECTROCMAP_H
#define ELECTROCMAP_H

#include <QWidget>
#include "ui_electrocmap.h"

class electrocMap : public QWidget
{
	Q_OBJECT

public:
	electrocMap(QWidget *parent = 0);
	~electrocMap();

private:
	Ui::electrocMap ui;
};

#endif // ELECTROCMAP_H
