#ifndef CLICKEDLABEL_H
#define CLICKEDLABEL_H

#include <QLabel>
#include <QMouseEvent>
class ClickedLabel : public QLabel
{
	Q_OBJECT
signals:
	void on_clicked();
protected:
	void mousePressEvent(QMouseEvent *event);
public:
	ClickedLabel(QWidget *parent);
	~ClickedLabel();
	
};

#endif // CLICKEDLABEL_H
