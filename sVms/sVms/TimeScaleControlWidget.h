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
	// ʱ��������޸�;
	void signalTimeScaleChanged(int);

public slots:
	// ���������ı�;
	void onScaleChanged(bool isAdd);

private:
	QToolButton* m_pButtonSub;
	QToolButton* m_pButtonAdd;

	QSlider* m_scaleSlider;
	
};
