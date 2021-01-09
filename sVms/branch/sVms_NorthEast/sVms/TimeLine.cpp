#include "TimeLine.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QTime>

#define HOUR_HEIGHT				15			// 小时刻度线高度;
#define MINUTE_HEIGHT			10			// 分钟刻度线高度;
#define INTERVAL_DISTANCE		5			// 分钟间隔距离;
#define MOVE_STEP_DISTANCE		20			// 鼠标单击移动步长;

#define MAX_SCALE_FACTOR		8			// 最大放大比例;
#define MIN_SCALE_FACTOR		1			// 最小放大比例;

#define ANIMATION_DURATION		800			// 动画时长;

#define TOTLE_TIME				24			// 时间轴时长;

TimeLine::TimeLine(QWidget *parent)
	: QWidget(parent)
	, m_isMousePressed(false)
	, m_isMouseMoved(false)
	, m_timeInterval(INTERVAL_DISTANCE)
	, m_currentMouseStepDistance(MOVE_STEP_DISTANCE)
	, m_currentScaleFactor (1)
	, m_isFirstSet(true)
	, m_centerX(0)
{
	m_adjustScaleAnimation = new QPropertyAnimation(this, "");
	m_adjustScaleAnimation->setDuration(ANIMATION_DURATION);
	m_adjustScaleAnimation->setEasingCurve(QEasingCurve::OutElastic);

	connect(m_adjustScaleAnimation, &QPropertyAnimation::valueChanged, this, [=](const QVariant &value) {
		m_transformX = value.toInt();
		update();
	});
	connect(m_adjustScaleAnimation, &QPropertyAnimation::finished, this, [=] {
		m_transformBeforeX = m_transformX;
		update();
	});
}

void TimeLine::paintEvent(QPaintEvent *event)
{	
	QPainter painter(this);
	painter.fillRect(this->rect(), QColor(169, 169, 169));
	
	painter.setPen(QPen(QColor(37, 197, 220)));
	painter.drawLine(QLine(QPoint(m_centerX, 0), QPoint(m_centerX, this->height())));

	painter.setPen(QPen(QColor(230, 60, 25)));
	painter.drawLine(QLine(QPoint(m_transformX, this->height()), QPoint(m_transformX, this->height() - HOUR_HEIGHT)));
	painter.drawText(QPoint(m_transformX - 8, this->height() - HOUR_HEIGHT - 5), "00");

	// 绘制时间轴;
	for (int i = 1; i <= TOTLE_TIME; i++)
	{
		drawOneHour(&painter, i);
	}

	painter.setFont(QFont("Microsoft YaHei", 11));
	painter.setPen(QPen(Qt::yellow));
	// 绘制当前时间;
	if (m_adjustScaleAnimation->state() == QAbstractAnimation::Stopped)
	{	
		m_strCurrentTime = QString("CurrentTime : %1").arg(getCurrentTime().toString("hh:mm:ss"));
	}
	painter.drawText(QPoint(10, 20), m_strCurrentTime);

	// 绘制当前缩放倍率;
	QString strScaleFactor = QString("ScaleFactor   : %1").arg(m_currentScaleFactor);
	painter.drawText(QPoint(10, 45), strScaleFactor);
}

void TimeLine::drawOneHour(QPainter* painter, int hour)
{
	int hourDistance = (hour - 1) * 10 * m_timeInterval;
	int startPosX = m_transformX + hourDistance;
	int i = 1;
	for (; i < 10; i++)
	{
		int minuteStartPosX = startPosX + i * m_timeInterval;
		painter->drawLine(QLine(QPoint(minuteStartPosX, this->height()), QPoint(minuteStartPosX, this->height() - MINUTE_HEIGHT)));
	}

	painter->drawLine(QLine(QPoint(startPosX + i * m_timeInterval, this->height()), QPoint(startPosX + i * m_timeInterval, this->height() - HOUR_HEIGHT)));
	QString strHour = QString::number(hour);
	hour < 10 ? strHour.prepend("0") : strHour;
	painter->drawText(QPoint(startPosX + i * m_timeInterval - 8, this->height() - HOUR_HEIGHT - 5), strHour);
}

void TimeLine::mouseMoveEvent(QMouseEvent* event)
{
	if (m_adjustScaleAnimation->state() == QAbstractAnimation::Running)
	{
		return;
	}

	if (m_isMousePressed)
	{
		m_isMouseMoved = true;
		QPoint movePoint = event->pos();
		int distance = movePoint.x() - m_pressPoint.x();
		m_transformX = m_transformBeforeX + distance;

		int maxDistance = TOTLE_TIME * 10 * m_timeInterval - m_centerX;
		if (distance > 0 && m_transformX > m_centerX)
		{
			m_transformX = m_centerX;
		}
		else if (distance < 0 && m_transformX < (-maxDistance))
		{
			m_transformX = -maxDistance;
		}
		update();
	}	
}

void TimeLine::mousePressEvent(QMouseEvent* event)
{
	if (m_adjustScaleAnimation->state() == QAbstractAnimation::Running)
	{
		return;
	}

	m_isMousePressed = true;
	m_pressPoint = event->pos();
}

void TimeLine::mouseReleaseEvent(QMouseEvent* event)
{
	if (m_adjustScaleAnimation->state() == QAbstractAnimation::Running)
	{
		return;
	}

	if (m_isMouseMoved)
	{
		m_isMouseMoved = false;
	}
	else if(m_isMousePressed)
	{
		QPoint releasePoint = event->pos();
		int mousePressTransformX;
		if (releasePoint.x() > this->width() / 2)
		{
			int maxDistance = TOTLE_TIME * 10 * m_timeInterval - m_centerX;
			int currentMouseStepDistance = releasePoint.x() - m_centerX;
			mousePressTransformX = m_transformX - currentMouseStepDistance;
			if (mousePressTransformX < (-maxDistance))
			{
				mousePressTransformX = -maxDistance;
			}
		}
		else
		{
			int currentMouseStepDistance = releasePoint.x() - m_centerX;
			mousePressTransformX = m_transformX - currentMouseStepDistance;
			if (mousePressTransformX > m_centerX)
			{
				mousePressTransformX = m_centerX;
			}
		}
		m_adjustScaleAnimation->setStartValue(m_transformX);
		m_adjustScaleAnimation->setEndValue(mousePressTransformX);
		m_adjustScaleAnimation->start();
	}

	m_isMousePressed = false;
	m_transformBeforeX = m_transformX;
}

QTime TimeLine::getCurrentTime()
{
	int timeDistance = m_centerX - m_transformX;
	int second = 1.0 * timeDistance / 10 / m_timeInterval * 60 * 60;
	QTime currentTime = QTime(0, 0, 0).addSecs(second);
	return currentTime;
}

QString TimeLine::getCurrentStrTime()
{
	return m_strCurrentTime;
}

int TimeLine::getCurrentScaleFactor()
{
	return m_currentScaleFactor;
}

void TimeLine::resizeEvent(QResizeEvent *event)
{
	if (m_isFirstSet)
	{
		m_isFirstSet = false;
		m_centerX = this->width() / 2;
		m_transformX = m_centerX;
		m_transformBeforeX = m_centerX;
	}
	else
	{
		int disTance = this->width() / 2 - m_centerX;
		m_centerX = this->width() / 2;
		m_transformX += disTance;
		m_transformBeforeX = m_transformX;
	}
}

void TimeLine::adjustCurrentScale()
{
	QTime currentTime = getCurrentTime();
	int currentSecond = QTime(0, 0, 0).secsTo(currentTime);
	int timeDistance = m_centerX - m_transformX;
	if (currentTime.secsTo(QTime(0, 0, 0)) == 0 && timeDistance > 0)
	{
		// 说明是24h，因为QTime在时间为24:00:00时自动转为00:00:00;
		currentSecond = TOTLE_TIME * 60 * 60;
	}

	// 计算放缩之后的距离差;
	int timeDistanceBefore =  1.0 * currentSecond / 60 / 60 * 10 * m_timeInterval;

	m_timeInterval = INTERVAL_DISTANCE * m_currentScaleFactor;
	m_currentMouseStepDistance = MOVE_STEP_DISTANCE * m_currentScaleFactor;

	int timeDistanceAfter = 1.0 * currentSecond / 60 / 60 * 10 * m_timeInterval;
	int adjustTransformX = m_transformX + timeDistanceBefore - timeDistanceAfter;

	// 如果是零点则直接放缩，不需动画效果;
	if (currentSecond == 0)
	{
		m_transformX = adjustTransformX;
		update();
	}
	else
	{
		// 动画移动到对应的点;
		m_adjustScaleAnimation->setStartValue(m_transformX);
		m_adjustScaleAnimation->setEndValue(adjustTransformX);
		m_adjustScaleAnimation->start();
	}	
}

void TimeLine::setScaleSmall()
{
	if (m_adjustScaleAnimation->state() == QAbstractAnimation::Running)
	{
		return;
	}

	if (m_currentScaleFactor-- == MIN_SCALE_FACTOR)
	{
		m_currentScaleFactor = MIN_SCALE_FACTOR;
	}
	adjustCurrentScale();
}

void TimeLine::setScaleBig()
{
	if (m_adjustScaleAnimation->state() == QAbstractAnimation::Running)
	{
		return;
	}

	if (++m_currentScaleFactor > MAX_SCALE_FACTOR)
	{
		m_currentScaleFactor = MAX_SCALE_FACTOR;
	}
	adjustCurrentScale();
}

void TimeLine::resetTimeLine()
{
	m_currentScaleFactor = MIN_SCALE_FACTOR;
	m_timeInterval = INTERVAL_DISTANCE * m_currentScaleFactor;
	m_currentMouseStepDistance = MOVE_STEP_DISTANCE * m_currentScaleFactor;
	m_transformX = m_transformBeforeX = m_centerX;
	update();
}
