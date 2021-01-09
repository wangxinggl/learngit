#pragma once

#include <QtWidgets/QWidget>
#include <QPropertyAnimation>

class TimeLine : public QWidget
{
	Q_OBJECT

public:
	TimeLine(QWidget *parent = Q_NULLPTR);

	// ��С;
	void setScaleSmall();
	// �Ŵ�;
	void setScaleBig();
	// ����ʱ����;
	void resetTimeLine();

	// ��ȡ��ǰʱ��;
	QTime getCurrentTime();
	QString getCurrentStrTime();

	// ��ȡ��ǰ��������;
	int getCurrentScaleFactor();

private:
	// ����ʱ����;
	void paintEvent(QPaintEvent *event);
	// ����ÿһ��Сʱ��ʱ����;
	void drawOneHour(QPainter* painter, int hour);

	// �����¼�;
	void mouseMoveEvent(QMouseEvent* event);

	void mousePressEvent(QMouseEvent* event);

	void mouseReleaseEvent(QMouseEvent* event);

	void resizeEvent(QResizeEvent *event);

	void adjustCurrentScale();
public:
	// ƫ����;
	int m_transformX;
	// ƫ��������ֵ;
	int m_transformBeforeX;
	// ��갴������;
	QPoint m_pressPoint;
	// ����Ƿ���;
	bool m_isMousePressed;
	// ����Ƿ���֮���ƶ�;
	bool m_isMouseMoved;
	// ��ǰʱ����;
	int m_timeInterval;
	// ��ǰ�Ŵ���;
	int m_currentScaleFactor;
	// ��ǰ������ƶ�����;
	int m_currentMouseStepDistance;
	// �������ĵ�X����;
	int m_centerX;
	// �Ƿ��ǵ�һ�����ô��ڿ��;
	bool m_isFirstSet;
	// �Ŵ���С����;
	QPropertyAnimation *m_adjustScaleAnimation;
	// ���浱ǰʱ����ʱ��;
	QString m_strCurrentTime;
};
