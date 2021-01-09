#include "LayerDrawWidget.h"
#include <QHBoxLayout>
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QMessageBox>

#pragma execution_character_set("utf-8")

TimeLineWidget::TimeLineWidget(QWidget* parent)
	: QWidget(parent)	
{
	this->setFixedSize(QSize(WIDGET_WIDTH, ROW_HEIGHT));

	QVector<QPoint> trianglePoint;
	trianglePoint << QPoint(-10, 0) << QPoint(10, 0) << QPoint(0, 12);
	m_timeLineTriangle = QPolygon(trianglePoint);
}

void TimeLineWidget::setLayerDrawInfoObject(LayerDrawInfo* object)
{
	m_layerDrawInfo = object;

	connect(m_layerDrawInfo, &LayerDrawInfo::signalNotifyUpdatePaint, this, [=] {
		update();
	});
}

void TimeLineWidget::drawTimeScale(QPainter& painter)
{
	painter.save();
	painter.setPen(QPen(Qt::white));

	painter.translate(QPoint(-m_layerDrawInfo->getTransformX(), 0));
	// 从0点开始绘制;
	QTime zeroTime(0, 0);
	int startPosX = 2;
	painter.drawLine(QLine(QPoint(startPosX, ROW_HEIGHT), QPoint(startPosX, ROW_HEIGHT - HOUR_HEIGHT)));
	painter.drawText(QPoint(startPosX, ROW_HEIGHT - HOUR_HEIGHT - 5), "0");
	zeroTime = zeroTime.addSecs(360);
	int iCurrentMinuteIndex = 1;
	while (zeroTime != QTime(0, 0, 0))
	{
		int iCurrentMinuteValue = zeroTime.minute();
		startPosX = iCurrentMinuteIndex * m_layerDrawInfo->getTimeInterval();
		// 每一个小时一个度;
		if (iCurrentMinuteValue == 0)
		{
			painter.drawLine(QLine(QPoint(startPosX, ROW_HEIGHT), QPoint(startPosX, ROW_HEIGHT - HOUR_HEIGHT)));
			QString strTime = zeroTime.toString("hh");
			painter.drawText(QPoint(startPosX - 5, ROW_HEIGHT - HOUR_HEIGHT - 7), strTime);
		}
		else
		{
			painter.drawLine(QLine(QPoint(startPosX, ROW_HEIGHT), QPoint(startPosX, ROW_HEIGHT - MINUTE_HEIGHT)));
		}
		iCurrentMinuteIndex += 1;
		zeroTime = zeroTime.addSecs(360);
	}
	// 绘制最后的零点;
	startPosX = iCurrentMinuteIndex * m_layerDrawInfo->getTimeInterval();
	painter.drawLine(QLine(QPoint(startPosX, ROW_HEIGHT), QPoint(startPosX, ROW_HEIGHT - HOUR_HEIGHT)));
	painter.drawText(QPoint(startPosX - 5, ROW_HEIGHT - HOUR_HEIGHT - 5), "0");
	painter.restore();
}

void TimeLineWidget::drawTimeLine(QPainter& painter)
{
	painter.save();
	painter.setRenderHint(QPainter::Antialiasing);
	painter.setPen(QPen(Qt::red, 2));
	painter.drawLine(QLine(QPoint(m_layerDrawInfo->getLinePos(), 0), QPoint(m_layerDrawInfo->getLinePos(), this->height())));

	painter.setBrush(Qt::red);
	QPolygon triangle = m_timeLineTriangle.translated(m_layerDrawInfo->getLinePos(), 0);
	painter.drawPolygon(triangle);

	painter.restore();
}

void TimeLineWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.fillRect(this->rect(), QColor(31, 32, 38));

	drawTimeScale(painter);
	//drawTimeLine(painter);
}

void TimeLineWidget::resizeEvent(QResizeEvent *event)
{
	m_layerDrawInfo->setLineWidgetCurrentWidth(this->width());

	return QWidget::resizeEvent(event);
}

LayerDrawWidget::LayerDrawWidget(QWidget *parent)
    : QWidget(parent)
	, m_currentDragLayerIndex(-1)
    , m_isMousePressed(false)
	, m_currentScaleFactor(1)
	, m_currentLayerIndex(0)
{
	m_moveTimer.setInterval(1000);
	connect(&m_moveTimer, &QTimer::timeout, this, &LayerDrawWidget::onTimerMove);
	m_LayerSpeed = 1;
}

void LayerDrawWidget::addLayerItem()
{
	LayerItemInfo layerItem;
	m_layerItemList.insert(0, layerItem);
	updateLayerItem();
}

void LayerDrawWidget::addLayerVideoSegemntData(int layerIndex, QList<VideoSegmentInfo> videoSegmentList)
{
	if (layerIndex > m_layerItemList.count())
	{
		return;
	}

	m_layerItemList[layerIndex].videoSegmentInfoList = videoSegmentList;
    float oneSecondInterval = 1.0 * INTERVAL_DISTANCE * m_currentScaleFactor / 6 / 60;
    for (int j = 0; j < videoSegmentList.count(); j++)
    {
        int startPos = 1.0 * QTime(0, 0).secsTo(videoSegmentList[j].videoStartTime) * oneSecondInterval;
        int endPos = 1.0 * QTime(0, 0).secsTo(videoSegmentList[j].videoEndTime) * oneSecondInterval;
        QRect rect = QRect(startPos, m_layerItemList[layerIndex].layerRect.top(), endPos - startPos, m_layerItemList[layerIndex].layerRect.height());
        if (layerIndex != 0)
        {
            rect.adjust(0, 1, 0, 0);
        }
		videoSegmentList[j].videoDataRect = rect;
    }

	m_layerItemList[layerIndex].videoSegmentInfoList = videoSegmentList;

	update();
}

void LayerDrawWidget::setLayerDrawInfoObject(LayerDrawInfo* object)
{
	m_layerDrawInfo = object;

	connect(m_layerDrawInfo, &LayerDrawInfo::signalNotifyUpdatePaint, this, [=] {
		update();
	});
}

void LayerDrawWidget::updateLayerItem()
{
	for (int i = 0; i < m_layerItemList.count(); i++)
	{
		LayerItemInfo& layerItem = m_layerItemList[i];
		layerItem.layerIndex = i;
		layerItem.layerRect = QRect(0, i * ROW_HEIGHT, LAYER_RECT_WIDTH, ROW_HEIGHT);
	}

	update();
}

void LayerDrawWidget::drawLayerPath(QPainter& painter)
{
	painter.setPen(QPen(QColor(225, 225, 225), 1));

    for (int i = 0; i < m_layerItemList.count(); i++)
    {
        painter.drawRect(m_layerItemList[i].layerRect);
		// 从0点开始绘制;
		for (int j = 1; j <= 24; j ++)
		{
			int startPosX = j * m_layerDrawInfo->getTimeInterval() * 10;
			painter.drawLine(QLine(QPoint(startPosX, m_layerItemList[i].layerRect.top()), QPoint(startPosX, m_layerItemList[i].layerRect.bottom())));
		}
    }
}

void LayerDrawWidget::drawVideoSegmentData(QPainter& painter)
{
	for (int i = 0; i < m_layerItemList.count(); i++)
	{
		float oneSecondInterval = 1.0 * INTERVAL_DISTANCE * m_currentScaleFactor / 6 / 60;
		QList<VideoSegmentInfo> videoSegmentInfoList = m_layerItemList[i].videoSegmentInfoList;
		for (int j = 0; j < videoSegmentInfoList.count(); j++)
		{
			painter.fillRect(videoSegmentInfoList[j].videoDataRect, QColor(100, 175, 55));
		}
	}
}

void LayerDrawWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.fillRect(this->rect(), QColor(60, 65, 85));
	painter.translate(QPoint(-m_layerDrawInfo->getTransformX(), 0));

    drawLayerPath(painter);
 	painter.setPen(QPen(QColor(60, 65, 85)));
	// 绘制最顶端一条线，遮住白色边框;
	int totalWidth = 1.0 * QTime(0, 0).secsTo(m_layerDrawInfo->getTimeLineRealTime()) / 60 * m_layerDrawInfo->getTimeInterval();
	painter.drawLine(QLine(QPoint(1, 0), QPoint(totalWidth, 0)));
	drawVideoSegmentData(painter);

    // 绘制刻度线;
    painter.setPen(QPen(Qt::red, 2));
    float oneSecondInterval = 1.0 * INTERVAL_DISTANCE * m_currentScaleFactor / 6 / 60;
    int startPos = 1.0 * QTime(0, 0).secsTo(m_needleTime) * oneSecondInterval;
    painter.drawLine(QLine(QPoint(startPos, 0), QPoint(startPos, this->height())));
}

void LayerDrawWidget::enterEvent(QEvent *event)
{
	this->setCursor(Qt::IBeamCursor);

	return QWidget::enterEvent(event);
}

void LayerDrawWidget::leaveEvent(QEvent *event)
{
	this->setCursor(Qt::ArrowCursor);

	return QWidget::leaveEvent(event);
}

int LayerDrawWidget::getMoveImagePathPosY(int iMousePosY)
{
    int layerPosY = 0;
    if (iMousePosY <= 0)
    {
        layerPosY = 0;
    }
    else if (iMousePosY >= m_layerItemList.last().layerRect.bottom())
    {
        layerPosY = m_layerItemList.last().layerRect.top();
    }
    else
    {
        int layerIndex = getLayerIndex(QPoint(1, iMousePosY));
        if (layerIndex < 0)
        {
            layerPosY = 0;
        }
        else
        {
            layerPosY = m_layerItemList[layerIndex].layerRect.top();
        }
    }
    
    return layerPosY;
}

int LayerDrawWidget::getLayerIndex(QPoint point)
{
    int layerIndex = -1;
    for (int i = 0; i < m_layerItemList.count(); i++)
    {
        if (m_layerItemList[i].layerRect.contains(point))
        {
            layerIndex = i;
            break;
        }
    }

    return layerIndex;
}

QTime LayerDrawWidget::getCurrentPointTime()
{
	int timeDistance = m_layerDrawInfo->getTransformX() + m_layerDrawInfo->getLinePos();
	int second = 1.0 * timeDistance / m_layerDrawInfo->getTimeInterval() * 60;
	QTime currentTime = QTime(0, 0, 0).addSecs(second);
	return currentTime;
}

void LayerDrawWidget::updateVideoDataAreaRect()
{
	for (int i = 0; i < m_layerItemList.count(); i++)
	{
		QList<VideoSegmentInfo> videoSegmentInfoList = m_layerItemList[i].videoSegmentInfoList;
		float oneSecondInterval = 1.0 * INTERVAL_DISTANCE * m_currentScaleFactor / 6 / 60;
		for (int j = 0; j < videoSegmentInfoList.count(); j++)
		{
			int startPos = 1.0 * QTime(0, 0).secsTo(videoSegmentInfoList[j].videoStartTime) * oneSecondInterval;
			int endPos = 1.0 * QTime(0, 0).secsTo(videoSegmentInfoList[j].videoEndTime) * oneSecondInterval;
			QRect rect = QRect(startPos, m_layerItemList[i].layerRect.top(), endPos - startPos, m_layerItemList[i].layerRect.height());
			if (i != 0)
			{
				rect.adjust(0, 1, 0, 0);
			}
			videoSegmentInfoList[j].videoDataRect = rect;
		}
		m_layerItemList[i].videoSegmentInfoList = videoSegmentInfoList;
	}
}

void LayerDrawWidget::onTimeScaleChanged(int scaleValue)
{
	m_currentScaleFactor = scaleValue;

	QTime currentPointTime = getCurrentPointTime();
	int currentPos = m_layerDrawInfo->getTransformX() + m_layerDrawInfo->getLinePos();

	m_layerDrawInfo->setTimeInterval(m_currentScaleFactor * INTERVAL_DISTANCE);

	qreal fMinute = 1.0 * QTime(0, 0).secsTo(currentPointTime) / 60;
	int afterChangedPos = fMinute * m_layerDrawInfo->getTimeInterval();
	m_layerDrawInfo->setTransformX(afterChangedPos - m_layerDrawInfo->getLinePos());
	
	int totalWidth = 1.0 * QTime(0, 0).secsTo(m_layerDrawInfo->getTimeLineRealTime()) / 60 * m_layerDrawInfo->getTimeInterval();

	// 确保放缩之后零点不会超出左边界;
	if (m_layerDrawInfo->getTransformX() < 0)
	{
		m_layerDrawInfo->setTransformX(0);
		m_layerDrawInfo->setLinePos(afterChangedPos);
	}
	// 确保放缩之后最大值不会超出右边界;
	else if (m_layerDrawInfo->getTransformX() + this->width() > totalWidth)
	{
		m_layerDrawInfo->setTransformX(totalWidth - this->width());
		m_layerDrawInfo->setLinePos(afterChangedPos - m_layerDrawInfo->getTransformX());
	}	

	// 比例更新之后需要更新绿色视频区域Rect;
	updateVideoDataAreaRect();
	update();
}

void LayerDrawWidget::onMoveTimeLine(bool isMoveRight)
{
	int transformXBefore = m_layerDrawInfo->getTransformX();
	// 一次移动一个小时;
	int oneHourOffset = 10 * INTERVAL_DISTANCE * m_currentScaleFactor;
	int totalWidth = oneHourOffset * 23;
	if (isMoveRight)
	{
		transformXBefore += oneHourOffset;
		if (transformXBefore > totalWidth)
		{
			return;
		}
	}
	else
	{
		transformXBefore -= oneHourOffset;
		if (transformXBefore < 0)
		{
			return;
		}
	}

	m_layerDrawInfo->setTransformX(transformXBefore);
}

void LayerDrawWidget::onScrollValueChanged(int value)
{
	int transformXBefore = m_layerDrawInfo->getTransformX();
	m_layerDrawInfo->setTransformX(value * m_currentScaleFactor);
	int totalWidth = 1.0 * QTime(0, 0).secsTo(m_layerDrawInfo->getTimeLineRealTime()) / 60 * m_layerDrawInfo->getTimeInterval();

	update();
}

void LayerDrawWidget::onStartMoveNeedle()
{
	m_moveTimer.start();
}

void LayerDrawWidget::onStartMoveNeedle(VideoSegmentInfo& data)
{
	m_currentLayerInfo = m_layerItemList.at(m_currentLayerIndex);
	// 如果当前层没有数据直接返回;
	if (m_currentLayerInfo.videoSegmentInfoList.count() <= 0)
	{
		return;
	}

	m_currentVideoSegmentInfo = data;
	m_needleTime = m_currentVideoSegmentInfo.videoStartTime;

	m_moveTimer.start();
	

}

void LayerDrawWidget::onStopMoveNeedle()
{
	m_moveTimer.stop();
}

void LayerDrawWidget::onTimerMove()
{
	m_needleTime = m_needleTime.addSecs(m_LayerSpeed);
	emit m_layerDrawInfo->signalUpdateCurrentTime(m_needleTime);
	if (m_needleTime > m_currentVideoSegmentInfo.videoEndTime)
	{
		/*m_currentLayerInfo.videoSegmentInfoList.removeFirst();
		if (m_currentLayerInfo.videoSegmentInfoList.count() > 0)
		{
			m_currentVideoSegmentInfo = m_currentLayerInfo.videoSegmentInfoList.first();
			m_needleTime = m_currentVideoSegmentInfo.videoStartTime;
		}
		else
		{
			m_moveTimer.stop();
			m_needleTime = m_currentVideoSegmentInfo.videoEndTime;
		}*/
		m_moveTimer.stop();
		m_needleTime = m_currentVideoSegmentInfo.videoEndTime;
	}

	update();
}

void LayerDrawWidget::mousePressEvent(QMouseEvent *event)
{
	m_isMousePressed = true;
	QPoint pressPoint = event->pos();

	// 点击右侧触发左侧窗口被选中状态;
	int layerIndex = getLayerIndex(pressPoint);
	emit signalClickedIndex(layerIndex);

	// 更新顶部时间;
	int oneHourOffset = 10 * INTERVAL_DISTANCE * m_currentScaleFactor;
	int totalWidth = oneHourOffset * 24;
	if (event->x() > totalWidth - m_layerDrawInfo->getTransformX())
	{
		return;
	}
	m_layerDrawInfo->setLinePos(event->pos().x());


	// 在没有播放的时候可以通过鼠标点击控制指针移动;
	if (!m_moveTimer.isActive())
	{
		int timeDistance = m_layerDrawInfo->getTransformX() + m_layerDrawInfo->getLinePos();
		int second = 1.0 * timeDistance / m_layerDrawInfo->getTimeInterval() * 60 * 6;
		m_needleTime = QTime(0, 0, 0).addSecs(second);
	}

	return QWidget::mousePressEvent(event);
}

void LayerDrawWidget::mouseMoveEvent(QMouseEvent *event)
{
	QPoint pressPoint = event->pos();

	// 更新顶部时间;
	int oneHourOffset = 10 * INTERVAL_DISTANCE * m_currentScaleFactor;
	int totalWidth = oneHourOffset * 24;
	if (event->x() > totalWidth - m_layerDrawInfo->getTransformX())
	{
		return;
	}
	m_layerDrawInfo->setLinePos(event->pos().x());


	// 在没有播放的时候可以通过鼠标点击控制指针移动;
	if (!m_moveTimer.isActive())
	{
		int timeDistance = m_layerDrawInfo->getTransformX() + m_layerDrawInfo->getLinePos();
		int second = 1.0 * timeDistance / m_layerDrawInfo->getTimeInterval() * 60 * 6;
		m_needleTime = QTime(0, 0, 0).addSecs(second);
		m_layerDrawInfo->setLinePos(event->pos().x());
	}

	update();

	return QWidget::mouseMoveEvent(event);
}

void LayerDrawWidget::mouseReleaseEvent(QMouseEvent *event)
{
	m_isMousePressed = false;
	update();
	return QWidget::mouseReleaseEvent(event);
}