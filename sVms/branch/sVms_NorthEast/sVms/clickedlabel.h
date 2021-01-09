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
protected:
	// 鼠标单击事件
    ClickedLabel(const QString &text, QWidget *parent=0);
	void mouseReleaseEvent(QMouseEvent *);
    //void enterEvent(QEvent *);
   // void leaveEvent(QEvent *);
private:
	
};

#endif // CLICKEDLABEL_H
