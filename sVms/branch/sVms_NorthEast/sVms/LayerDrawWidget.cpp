#include "LayerDrawWidget.h"
#include <QHBoxLayout>
#include <QPainter>
#include <QDebug>
#include <QMouseEvent>
#include <QMessageBox>

#pragma execution_character_set("utf-8")

LayerDrawInfo* LayerDrawInfo::m_inst = NULL;
QMutex LayerDrawInfo::m_mutex;

TimeLineWidget::TimeLineWidget(QWidget* parent)
	: QWidget(parent)	
{
	this->setFixedSize(QSize(WIDGET_WIDTH, ROW_HEIGHT));

	connect(LayerDrawInfo::getInstance(), &LayerDrawInfo::signalNotifyUpdatePaint, this, [=]{
		update();
	});


	
}

LayerDrawWidget::LayerDrawWidget(QWidget *parent)
    : QWidget(parent)
	, m_currentDragLayerIndex(-1)
    , m_isMousePressed(false)
	, m_currentScaleFactor(1)
	, m_currentLayerIndex(0)
{
	connect(LayerDrawInfo::getInstance(), &LayerDrawInfo::signalNotifyUpdatePaint, this, [=]{
		update();
	});

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
			int startPosX = j * GET_TIME_INTERVAL * 10;
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
	painter.translate(QPoint(-GET_TRANSFORM_X, 0));

    drawLayerPath(painter);
 	painter.setPen(QPen(QColor(60, 65, 85)));
	// 绘制最顶端一条线，遮住白色边框;
	int totalWidth = 1.0 * QTime(0, 0).secsTo(GET_LINE_TIME) / 60 * GET_TIME_INTERVAL;
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
	int timeDistance = GET_TRANSFORM_X + GET_LINE_POS;
	int second = 1.0 * timeDistance / GET_TIME_INTERVAL * 60;
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
	int currentPos = GET_TRANSFORM_X + GET_LINE_POS;

	SET_TIME_INTERVAL(m_currentScaleFactor * INTERVAL_DISTANCE);

	qreal fMinute = 1.0 * QTime(0, 0).secsTo(currentPointTime) / 60;
	int afterChangedPos = fMinute * GET_TIME_INTERVAL;
	SET_TRANSFORM_X(afterChangedPos - GET_LINE_POS);
	
	int totalWidth = 1.0 * QTime(0, 0).secsTo(GET_LINE_TIME) / 60 * GET_TIME_INTERVAL;

	// 确保放缩之后零点不会超出左边界;
	if (GET_TRANSFORM_X < 0)
	{
		SET_TRANSFORM_X(0);
		SET_LINE_POS(afterChangedPos);
	}
	// 确保放缩之后最大值不会超出右边界;
	else if (GET_TRANSFORM_X + this->width() > totalWidth)
	{
		SET_TRANSFORM_X(totalWidth - this->width());
		SET_LINE_POS(afterChangedPos - GET_TRANSFORM_X);
	}	

	// 比例更新之后需要更新绿色视频区域Rect;
	updateVideoDataAreaRect();
	update();
}

void LayerDrawWidget::onMoveTimeLine(bool isMoveRight)
{
	int transformXBefore = GET_TRANSFORM_X;
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

	SET_TRANSFORM_X(transformXBefore);
}

void LayerDrawWidget::onScrollValueChanged(int value)
{
	int transformXBefore = GET_TRANSFORM_X;
	SET_TRANSFORM_X(value * m_currentScaleFactor);
	int totalWidth = 1.0 * QTime(0, 0).secsTo(GET_LINE_TIME) / 60 * GET_TIME_INTERVAL;

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
	emit LayerDrawInfo::getInstance()->signalUpdateCurrentTime(m_needleTime);
	if (m_needleTime > m_currentVideoSegmentInfo.videoEndTime)
	{
		//m_currentLayerInfo.videoSegmentInfoList.removeFirst();
		//if (m_currentLayerInfo.videoSegmentInfoList.count() > 0)
		//{
		//	m_currentVideoSegmentInfo = m_currentLayerInfo.videoSegmentInfoList.first();
		//	m_needleTime = m_currentVideoSegmentInfo.videoStartTime;
		//	m_moveTimer.stop();
		//}
		//else
		//{
		m_moveTimer.stop();
		m_needleTime = m_currentVideoSegmentInfo.videoEndTime;
		//}
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
	if (event->x() > totalWidth - GET_TRANSFORM_X)
	{
		return;
	}
	SET_LINE_POS(event->pos().x());


	// 在没有播放的时候可以通过鼠标点击控制指针移动;
	if (!m_moveTimer.isActive())
	{
		int timeDistance = GET_TRANSFORM_X + GET_LINE_POS;
		int second = 1.0 * timeDistance / GET_TIME_INTERVAL * 60 * 6;
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
	if (event->x() > totalWidth - GET_TRANSFORM_X)
	{
		return;
	}
	SET_LINE_POS(event->pos().x());


	// 在没有播放的时候可以通过鼠标点击控制指针移动;
	if (!m_moveTimer.isActive())
	{
		int timeDistance = GET_TRANSFORM_X + GET_LINE_POS;
		int second = 1.0 * timeDistance / GET_TIME_INTERVAL * 60 * 6;
		m_needleTime = QTime(0, 0, 0).addSecs(second);
	}

	return QWidget::mouseMoveEvent(event);
}

void LayerDrawWidget::mouseReleaseEvent(QMouseEvent *event)
{
	m_isMousePressed = false;

	return QWidget::mouseReleaseEvent(event);
}