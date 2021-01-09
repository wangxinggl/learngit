#pragma once

#include <QWidget>
#include <QScrollBar>
#include <QToolButton>
#include <QPainter>
#include <QSlider>

class TimeScaleControlWidget : public QWidget
{
	Q_OBJECT

public:
	TimeScaleControlWidget(QWidget *parent = NULL);
	~TimeScaleControlWidget();

private:
	void initWidget();

	void paintEvent(QPaintEvent *event)
	{
		QPainter painter(this);
		painter.fillRect(this->rect(), QColor(31, 32, 38));
	}

signals:
	// 时间轴比例修改;
	void signalTimeScaleChanged(int);

public slots:
	// 放缩比例改变;
	void onScaleChanged(bool isAdd);

private:
	QToolButton* m_pButtonSub;
	QToolButton* m_pButtonAdd;

	QSlider* m_scaleSlider;
	
};
