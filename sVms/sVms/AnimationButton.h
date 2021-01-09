#pragma once

#include <QWidget>
#include <QVariant>
#include <QMouseEvent>
#include <QPropertyAnimation>

class AnimationButton : public QWidget
{
	Q_OBJECT

public:
	AnimationButton(QWidget *parent);
	~AnimationButton();
protected:
	void enterEvent(QEvent *);
	void leaveEvent(QEvent *);
	void paintEvent(QPaintEvent *);
	void mousePressEvent(QMouseEvent *ev);

private:
	bool enter;
	bool leave;
	int pixWidth;
	int pixHeight;
	int oldWidth;
	int oldHeight;

	QPropertyAnimation *enterAnimation;
	QPropertyAnimation *leaveAnimation;

	int targetWidth;
	int targetHeight;
	QString text;
	QString image;

private slots:
	void enterImageChanged(QVariant index);
	void leaveImageChanged(QVariant index);

signals:
	void widget_clicked();
public slots:
	void setText(QString text);
	void setImage(QString image);
};
