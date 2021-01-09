#pragma once

#include <QtWidgets/QWidget>
#include <QPropertyAnimation>

class TimeLine : public QWidget
{
	Q_OBJECT

public:
	TimeLine(QWidget *parent = Q_NULLPTR);

	// 缩小;
	void setScaleSmall();
	// 放大;
	void setScaleBig();
	// 重置时间轴;
	void resetTimeLine();

	// 获取当前时间;
	QTime getCurrentTime();
	QString getCurrentStrTime();

	// 获取当前放缩倍数;
	int getCurrentScaleFactor();

private:
	// 绘制时间轴;
	void paintEvent(QPaintEvent *event);
	// 绘制每一个小时的时间轴;
	void drawOneHour(QPainter* painter, int hour);

	// 操作事件;
	void mouseMoveEvent(QMouseEvent* event);

	void mousePressEvent(QMouseEvent* event);

	void mouseReleaseEvent(QMouseEvent* event);

	void resizeEvent(QResizeEvent *event);

	void adjustCurrentScale();
public:
	// 偏移量;
	int m_transformX;
	// 偏移量备份值;
	int m_transformBeforeX;
	// 鼠标按下坐标;
	QPoint m_pressPoint;
	// 鼠标是否按下;
	bool m_isMousePressed;
	// 鼠标是否按下之后移动;
	bool m_isMouseMoved;
	// 当前时间间距;
	int m_timeInterval;
	// 当前放大倍数;
	int m_currentScaleFactor;
	// 当前鼠标点击移动步长;
	int m_currentMouseStepDistance;
	// 窗口中心点X坐标;
	int m_centerX;
	// 是否是第一次设置窗口宽度;
	bool m_isFirstSet;
	// 放大缩小动画;
	QPropertyAnimation *m_adjustScaleAnimation;
	// 保存当前时间轴时间;
	QString m_strCurrentTime;
};
