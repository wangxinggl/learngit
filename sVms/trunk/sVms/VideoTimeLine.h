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
	// ���ι����¼������������ڷŴ���С����;
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
	// �����¼���֪ͨ������������;
	void signalScaleChanged(bool isAdd);

public:
	// ����ͼ�������ƶ�;
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

// ��Ŀ���Ŵ��ڸ���;
class VideoTimeLine : public QWidget
{
    Q_OBJECT

public:
    VideoTimeLine(QWidget* parent = NULL);
    // ����ʱ�����ʱ������;
    void setTimeLineLength(QTime time);

	// �����Ƶ������;
	void addLayerVideoSegemntData(int layerIndex, QList<VideoSegmentInfo> videoSegmentList);
	QColor color;
private:
    void initTimeBackWidget();
    void initWidget();

    // ��Ŀ���Ÿ���ģ��֮����ź�֪ͨ;
    void initConnections();
	// ���µ�ǰͼ���ܸ߶�;
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