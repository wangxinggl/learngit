#pragma once

#include <QWidget>
#include <QScrollArea>
#include <QPushButton>
#include <QWheelEvent>
#include <QScrollBar>
#include <QTimeEdit>
#include "LayerDrawWidget.h"

class TimeHeaderWidget;
class LayerControlWidget;
class TimeLineWidget;
class LayerDrawWidget;
class TimeScaleControlWidget;

class MyScrollArea : public QScrollArea
{
	Q_OBJECT
public:
	MyScrollArea(QWidget* parent = NULL)
		: QScrollArea(parent)
	{

	}

private:
	// 屏蔽滚轮事件，将滚轮用于放大缩小功能;
	void wheelEvent(QWheelEvent *event)
	{
		if (event->delta() > 0)
		{
			emit signalScaleChanged(true);
		}
		else
		{
			emit signalScaleChanged(false);
		}
		return;
	}

signals:
	// 滚轮事件，通知放缩比例更改;
	void signalScaleChanged(bool isAdd);

public:
	// 用于图层上下移动;
	void scrollBarMove(bool isMoveUp)
	{
		if (isMoveUp)
		{
			QScrollBar* vScrollBar = this->verticalScrollBar();
			vScrollBar->setValue(vScrollBar->value() - 40);
		}
		else
		{
			QScrollBar* vScrollBar = this->verticalScrollBar();
			vScrollBar->setValue(vScrollBar->value() + 40);
		}
	}
};

// 节目编排窗口父类;
class VideoTimeLine : public QWidget
{
    Q_OBJECT

public:
    VideoTimeLine(QWidget* parent = NULL);
    // 设置时间轴的时间周期;
    void setTimeLineLength(QTime time);

	// 添加视频段数据;
	void addLayerVideoSegemntData(int layerIndex, QList<VideoSegmentInfo> videoSegmentList);
	QColor color;
private:
    void initTimeBackWidget();
    void initWidget();

    // 节目编排各个模块之间的信号通知;
    void initConnections();
	// 更新当前图层总高度;
    void  updateLayerHeight();

    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
    void showEvent(QShowEvent *event);

public:
    QWidget* m_timeBackWidget;
    
	TimeHeaderWidget * m_timeHeaderWidget;
    LayerControlWidget* m_layerControlWidget;

    TimeLineWidget* m_timeLineWidget;
    LayerDrawWidget* m_layerDrawWidget;

	MyScrollArea* m_scrollArea;
    QWidget* m_layerBackWidget;

    TimeScaleControlWidget* m_timeScaleControlWidget;

	QPushButton* m_pButtonScrollUp;
	QPushButton* m_pButtonScrollDown;
};