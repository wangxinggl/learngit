#pragma once

#include <QtWidgets/QWidget>
#include <QSplitter>
#include <QDebug>
#include <QTime>
#include <QTimer>
#include <QPainter>
#include <QMouseEvent>
#include <QMutex>

#define WIDGET_WIDTH 1445					// ʱ������;
#define ROW_HEIGHT 40
#define IMAGE_PATH_INIT_WIDTH 50
#define PATH_JUDGE_WIDTH 4

#define HOUR_HEIGHT				10			// Сʱ�̶��߸߶�;
#define MINUTE_HEIGHT			5			// ���ӿ̶��߸߶�;
#define INTERVAL_DISTANCE		6			// 6���Ӽ������;

#define LAYER_RECT_WIDTH 15000

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
	LayerDrawInfo(QObject* parent = NULL)
		: QObject(parent)
		, m_currentWidgetWidth(0)
		, m_timeLinePos(0)
		, m_transformX(0)
		, m_currentScaleFactor(1)
		, m_timeInterval(INTERVAL_DISTANCE)
	{

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
    // ���µ�ǰ�������ķ�Χ;
    void signalUpdateScrollWidth(int);
    // ���µ�ǰʱ����ʱ��ʱ��;
    void signalUpdateCurrentTime(QTime);

	// ���»���;
	void signalNotifyUpdatePaint();

private:
    static LayerDrawInfo* m_inst;
    static QMutex m_mutex;

    QTime m_time;
    // ʱ��̶���λ��;
    int m_timeLinePos;
    // ��ǰ�ؼ��Ŀ��;
    int m_currentWidgetWidth;

    // ��ǰ���ӿ̶ȳ���;
    int m_timeInterval;
    // ��ǰ����X��ƫ��;
    int m_transformX;
    // ��ǰ��������;
    int m_currentScaleFactor;
};

// ʱ���������;
class TimeLineWidget : public QWidget
{
    Q_OBJECT

public:
	TimeLineWidget(QWidget* parent = NULL);

	// ���û�����Ϣ����;
	void setLayerDrawInfoObject(LayerDrawInfo* object);

private:

	// ����ʱ��̶���;
	void drawTimeScale(QPainter& painter);    

	void drawTimeLine(QPainter& painter);

	void paintEvent(QPaintEvent *event);

	// ��С����Ӧ;
	void resizeEvent(QResizeEvent *event);
    
private:
	LayerDrawInfo* m_layerDrawInfo;
	QPolygon m_timeLineTriangle;
};

// ͼ�㡢ͼԪ������;
class LayerDrawWidget : public QWidget
{
    Q_OBJECT

public:
	LayerDrawWidget(QWidget *parent = Q_NULLPTR);

	// �����µ�ͼ��;
    void addLayerItem();

	// �����Ƶ������;
	void addLayerVideoSegemntData(int layerIndex, QList<VideoSegmentInfo> videoSegmentList);
	int m_LayerSpeed;
	// ���û�����Ϣ����;
	void setLayerDrawInfoObject(LayerDrawInfo* object);

private:
	// ����ͼ��Rect��Ϣ;
	void updateLayerItem();
	// ����ÿһ��ͼ��߿�;
    void drawLayerPath(QPainter& painter);
	// ����ÿһ��ͼ����Ƶ����;
	void drawVideoSegmentData(QPainter& painter);

	void paintEvent(QPaintEvent *event);
	// ����������¼��������л������ʽ״̬;
	void enterEvent(QEvent *event);
	void leaveEvent(QEvent *event);

	// ������¼������ڸ��¶���ʱ�䣬ͬʱ�жϵ�ǰ������Ƿ������ɫ��Ƶ��������;
    void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);

    // ���ݵ�ǰ���Y�����ȡ��ǰImage���ڲ�����;
    int getMoveImagePathPosY(int iMousePosY);

    // ���ݵ�ǰ����ȡ���ڵ�ͼ��index;
    int getLayerIndex(QPoint point);
    
	// ��ȡ��ǰʱ��ָ���ʱ��;
	QTime getCurrentPointTime();

	// ����������С������Ƶ��������Rect����;
	void updateVideoDataAreaRect();

signals:
	// ֪ͨ���»�������Χ;
	void signalUpdateScrollWidth(int width);
	// ֪ͨ���»�������ǰֵ;
	void signalUpdateScrollCurrentValue(int value);

	// ���ĳһ��ʹ�Ҳ�ѡ��;
	void signalClickedIndex(int);

    // ��ǰ������Ƿ�����ɫ����;
    void signalMouseClickeInVideoArea();

public slots:
	// ����ʱ�������ű���;
	void onTimeScaleChanged(int scaleValue);
	// �ƶ�ʱ����;
	void onMoveTimeLine(bool isMoveRight);

	// ���黬������λ��;
	void onScrollValueChanged(int value);

	// ��ʼ�ƶ�ָ��;
	void onStartMoveNeedle(VideoSegmentInfo& data);
	void onStartMoveNeedle();
	// ֹͣ�ƶ�ָ��;
	void onStopMoveNeedle();

	// ��ʼ��ʱ;
	void onTimerMove();


private:
    QSplitter* m_splitter;
	bool m_isMousePressed;

    QList<LayerItemInfo> m_layerItemList;

    // ��ǰ��ק��ͼ��index;
	int m_currentDragLayerIndex;

	QPoint m_endPoint;

	// ��ǰʱ����ʱ�䳤��;
	QTime m_time;

	// ��ǰ���ӿ̶ȳ���;
	int m_timeInterval;

	// ��ǰ��������;
	int m_currentScaleFactor;

    // ��ǰ�̶���ָ��ʱ��;
    QTime m_needleTime;

	// ��ǰ����Ĳ�Index;
	int m_currentLayerIndex;

	LayerItemInfo m_currentLayerInfo;

	VideoSegmentInfo m_currentVideoSegmentInfo;

	QTimer m_moveTimer;

	// ������Ϣ����;
	LayerDrawInfo* m_layerDrawInfo;
};
