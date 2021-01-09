#pragma once

#include <QtWidgets/QWidget>
#include <QSplitter>
#include <QDebug>
#include <QTime>
#include <QTimer>
#include <QPainter>
#include <QMouseEvent>
#include <QMutex>

#define WIDGET_WIDTH 1445					// 时间轴宽度;
#define ROW_HEIGHT 40
#define IMAGE_PATH_INIT_WIDTH 50
#define PATH_JUDGE_WIDTH 4

#define HOUR_HEIGHT				10			// 小时刻度线高度;
#define MINUTE_HEIGHT			5			// 分钟刻度线高度;
#define INTERVAL_DISTANCE		4			// 6分钟间隔距离;

#define LAYER_RECT_WIDTH 15000

// 时间轴总共时间;
#define GET_LINE_TIME LayerDrawInfo::getInstance()->getTimeLineRealTime()
#define Set_LINE_TIME(time) LayerDrawInfo::getInstance()->setTimeLineRealTime(time)

// 时间轴时针位置;
#define GET_LINE_POS LayerDrawInfo::getInstance()->getLinePos()
#define SET_LINE_POS(pos) LayerDrawInfo::getInstance()->setLinePos(pos)

// 画笔坐标偏移;
#define GET_TRANSFORM_X LayerDrawInfo::getInstance()->getTransformX()
#define SET_TRANSFORM_X(posX) LayerDrawInfo::getInstance()->setTransformX(posX)

// 当前分钟放缩间隔;
#define GET_TIME_INTERVAL LayerDrawInfo::getInstance()->getTimeInterval()
#define SET_TIME_INTERVAL(timeInterval) LayerDrawInfo::getInstance()->setTimeInterval(timeInterval)

struct VideoSegmentInfo
{
	QTime videoStartTime;
	QTime videoEndTime;
	QRect videoDataRect;
};

struct LayerItemInfo
{
    QRect layerRect;
    int layerIndex;
	QList<VideoSegmentInfo> videoSegmentInfoList;

    LayerItemInfo()
    {
        layerIndex = -1;
        layerRect = QRect(0, 0, 0, 0);
    }
};

class LayerDrawInfo : public QObject
{
    Q_OBJECT

public:
    static LayerDrawInfo* getInstance()
    {
        m_mutex.lock();
        if (m_inst == NULL)
        {
            m_inst = new LayerDrawInfo;
        }
        m_mutex.unlock();

        return m_inst;
    }

    int getLinePos()
    {
        return m_timeLinePos;
    }

    void setLinePos(int pos)
    {
        m_timeLinePos = pos;
        if (m_timeLinePos < 0)
        {
            m_timeLinePos = 0;
        }
        else if (m_timeLinePos > m_currentWidgetWidth)
        {
            m_timeLinePos = m_currentWidgetWidth;
        }
        emit signalUpdateCurrentTime(getCurrentPointTime());
		emit signalNotifyUpdatePaint();
    }

    int getTransformX()
    {
        return m_transformX;
    }

    void setTransformX(int transformX)
    {
        m_transformX = transformX;
		emit signalNotifyUpdatePaint();
    }

	void setTimeInterval(int timeInterval)
	{
		m_timeInterval = timeInterval;
	}

    int getTimeInterval()
    {
        return m_timeInterval;
    }

    QTime getCurrentPointTime()
    {
        int timeDistance = m_transformX + m_timeLinePos;
        int second = 1.0 * timeDistance / m_timeInterval * 60 * 6;
        QTime currentTime = QTime(0, 0, 0).addSecs(second);
        return currentTime;
    }

    void setTimeLineRealTime(QTime time)
    {
        m_time = time;
        int totalWidth = 1.0 * QTime(0, 0).secsTo(m_time) / 60 * INTERVAL_DISTANCE;
        emit signalUpdateScrollWidth(totalWidth);
    }

    QTime getTimeLineRealTime()
    {
        return m_time;
    }

    void setLineWidgetCurrentWidth(int width)
    {
        m_currentWidgetWidth = width;
    }

signals:
    // 更新当前滚动条的范围;
    void signalUpdateScrollWidth(int);
    // 更新当前时间轴时针时间;
    void signalUpdateCurrentTime(QTime);

	// 更新绘制;
	void signalNotifyUpdatePaint();

private:
    LayerDrawInfo(QObject* parent = NULL)
        : QObject(parent)
        , m_currentWidgetWidth(0)
        , m_timeLinePos(0)
        , m_transformX(0)
        , m_currentScaleFactor(1)
        , m_timeInterval(INTERVAL_DISTANCE)
    {

    }

private:
    static LayerDrawInfo* m_inst;
    static QMutex m_mutex;

    QTime m_time;
    // 时间刻度线位置;
    int m_timeLinePos;
    // 当前控件的宽度;
    int m_currentWidgetWidth;

    // 当前分钟刻度长度;
    int m_timeInterval;
    // 当前画笔X轴偏移;
    int m_transformX;
    // 当前放缩比例;
    int m_currentScaleFactor;
};

// 时间轴绘制类;
class TimeLineWidget : public QWidget
{
    Q_OBJECT

public:
	TimeLineWidget(QWidget* parent = NULL);

private:

	// 绘制时间刻度轴;
    void drawTimeScale(QPainter& painter)
    {
        painter.save();
		painter.fillRect(this->rect(), QColor(31, 32, 38));
        painter.setPen(QPen(Qt::white));

        painter.translate(QPoint(-GET_TRANSFORM_X, 0));
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
			startPosX = iCurrentMinuteIndex * GET_TIME_INTERVAL;
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
		startPosX = iCurrentMinuteIndex * GET_TIME_INTERVAL;
		painter.drawLine(QLine(QPoint(startPosX, ROW_HEIGHT), QPoint(startPosX, ROW_HEIGHT - HOUR_HEIGHT)));
		painter.drawText(QPoint(startPosX - 5, ROW_HEIGHT - HOUR_HEIGHT - 5), "0");
        painter.restore();
    }

    void paintEvent(QPaintEvent *event)
    {
        QPainter painter(this);
        painter.fillRect(this->rect(), QColor(225, 225, 225));

        drawTimeScale(painter);
    }

	// 大小自适应;
    void resizeEvent(QResizeEvent *event)
    {
        LayerDrawInfo::getInstance()->setLineWidgetCurrentWidth(this->width());

        return QWidget::resizeEvent(event);
    }
};

// 图层、图元绘制类;
class LayerDrawWidget : public QWidget
{
    Q_OBJECT

public:
	LayerDrawWidget(QWidget *parent = Q_NULLPTR);

	// 增加新的图层;
    void addLayerItem();

	// 添加视频段数据;
	void addLayerVideoSegemntData(int layerIndex, QList<VideoSegmentInfo> videoSegmentList);
	int m_LayerSpeed;
private:
	// 更新图层Rect信息;
	void updateLayerItem();
	// 绘制每一层图层边框;
    void drawLayerPath(QPainter& painter);
	// 绘制每一层图层视频数据;
	void drawVideoSegmentData(QPainter& painter);

	void paintEvent(QPaintEvent *event);
	// 鼠标进入进出事件，用于切换鼠标样式状态;
	void enterEvent(QEvent *event);
	void leaveEvent(QEvent *event);

	// 鼠标点击事件，用于更新顶部时间，同时判断当前鼠标点击是否进入绿色视频数据区域;
    void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

    // 根据当前鼠标Y坐标获取当前Image所在层坐标;
    int getMoveImagePathPosY(int iMousePosY);

    // 根据当前鼠标获取所在的图层index;
    int getLayerIndex(QPoint point);
    
	// 获取当前时针指向的时间;
	QTime getCurrentPointTime();

	// 放缩比例大小更改视频数据区域Rect更新;
	void updateVideoDataAreaRect();

signals:
	// 通知更新滑动条范围;
	void signalUpdateScrollWidth(int width);
	// 通知更新滑动条当前值;
	void signalUpdateScrollCurrentValue(int value);

	// 点击某一行使右侧选中;
	void signalClickedIndex(int);

    // 当前鼠标点击是否在绿色区域;
    void signalMouseClickeInVideoArea();

public slots:
	// 更新时间轴缩放比例;
	void onTimeScaleChanged(int scaleValue);
	// 移动时间轴;
	void onMoveTimeLine(bool isMoveRight);

	// 滑块滑动更新位置;
	void onScrollValueChanged(int value);

	// 开始移动指针;
	void onStartMoveNeedle();
	void onStartMoveNeedle(VideoSegmentInfo& data);
	// 停止移动指针;
	void onStopMoveNeedle();

	// 开始计时;
	void onTimerMove();


private:
    QSplitter* m_splitter;
	bool m_isMousePressed;

    QList<LayerItemInfo> m_layerItemList;

    // 当前拖拽的图层index;
	int m_currentDragLayerIndex;

	QPoint m_endPoint;

	// 当前时间轴时间长度;
	QTime m_time;

	// 当前分钟刻度长度;
	int m_timeInterval;

	// 当前放缩比例;
	int m_currentScaleFactor;

    // 当前刻度针指向时间;
    QTime m_needleTime;

	// 当前点击的层Index;
	int m_currentLayerIndex;

	LayerItemInfo m_currentLayerInfo;

	VideoSegmentInfo m_currentVideoSegmentInfo;

	QTimer m_moveTimer;

	//设置时间速度
	
};
