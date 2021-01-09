#include "VideoTimeLine.h"
#include "LayerWidget.h"
#include "TimeScaleControlWidget.h"

VideoTimeLine::VideoTimeLine(QWidget* parent /*= NULL*/)
	: QWidget(parent)
{
    initWidget();
    initConnections();
	setTimeLineLength(QTime(23, 59, 59));
	this->setStyleSheet("font-family:Microsoft YaHei;");

	this->setFixedHeight(140);
 //   this->setFixedWidth(1200);
	
}

void VideoTimeLine::setTimeLineLength(QTime time)
{
    Set_LINE_TIME(time);
}

void VideoTimeLine::addLayerVideoSegemntData(int layerIndex, QList<VideoSegmentInfo> videoSegmentList)
{
	m_layerDrawWidget->addLayerVideoSegemntData(layerIndex, videoSegmentList);
}

void VideoTimeLine::initTimeBackWidget()
{
    m_timeBackWidget = new QWidget;
 

    QHBoxLayout* hTimeChooseLayout = new QHBoxLayout(m_timeBackWidget);
    hTimeChooseLayout->addStretch();
    hTimeChooseLayout->setSpacing(10);
    hTimeChooseLayout->setMargin(0);
}

void VideoTimeLine::initWidget()
{
    initTimeBackWidget();

	m_timeHeaderWidget = new TimeHeaderWidget;
	m_layerControlWidget = new LayerControlWidget;
	m_timeLineWidget = new TimeLineWidget;
	m_layerDrawWidget = new LayerDrawWidget;

	m_timeScaleControlWidget = new TimeScaleControlWidget;

	// 初始化默认添加6个图层;
	
	
	m_layerControlWidget->addLayerItem();
	m_layerDrawWidget->addLayerItem();
	

	QVBoxLayout* vHeadLayout = new QVBoxLayout;
    vHeadLayout->addWidget(m_timeBackWidget);
	vHeadLayout->addWidget(m_timeHeaderWidget);
	vHeadLayout->addWidget(m_timeLineWidget);
	vHeadLayout->setSpacing(0);
	vHeadLayout->setMargin(0);

	QHBoxLayout* hHeadLayout = new QHBoxLayout;
	hHeadLayout->addWidget(m_timeScaleControlWidget);
	hHeadLayout->addLayout(vHeadLayout);
	hHeadLayout->setSpacing(0);
	hHeadLayout->setMargin(0);

	m_layerBackWidget = new QWidget;
	m_layerBackWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	m_layerBackWidget->setStyleSheet(".QWidget{background:black;}");

	QHBoxLayout* hScrollArea = new QHBoxLayout(m_layerBackWidget);
	hScrollArea->addWidget(m_layerControlWidget);
	hScrollArea->addWidget(m_layerDrawWidget);
	hScrollArea->addStretch();
	hScrollArea->setSpacing(0);
	hScrollArea->setMargin(0);

	m_scrollArea = new MyScrollArea;
	m_scrollArea->setFixedHeight(42);
	m_scrollArea->setWidget(m_layerBackWidget);
	m_scrollArea->setWidgetResizable(true);
	m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	m_scrollArea->setStyleSheet("QScrollArea{border:none;background:black;}");
	m_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

	connect(m_scrollArea, &MyScrollArea::signalScaleChanged, m_timeScaleControlWidget, &TimeScaleControlWidget::onScaleChanged);

    QVBoxLayout* vMainLayout = new QVBoxLayout();
	vMainLayout->addLayout(hHeadLayout);
	vMainLayout->addWidget(m_scrollArea);
    vMainLayout->addStretch();
	vMainLayout->setMargin(0);
	vMainLayout->setSpacing(0);

	QHBoxLayout* hMainLayout = new QHBoxLayout(this);
	hMainLayout->addLayout(vMainLayout);
	
	hMainLayout->addSpacing(0);
	hMainLayout->setMargin(0);
	hMainLayout->setSpacing(0);
}

void VideoTimeLine::initConnections()
{
	connect(LayerDrawInfo::getInstance(), &LayerDrawInfo::signalUpdateCurrentTime, m_timeHeaderWidget, &TimeHeaderWidget::onUpdateCurrentTime);

    connect(m_timeScaleControlWidget, &TimeScaleControlWidget::signalTimeScaleChanged, m_layerDrawWidget, &LayerDrawWidget::onTimeScaleChanged);

	connect(m_timeHeaderWidget, &TimeHeaderWidget::signalTimeLineMove, m_layerDrawWidget, &LayerDrawWidget::onMoveTimeLine);

	connect(m_layerDrawWidget, &LayerDrawWidget::signalClickedIndex, m_layerControlWidget, &LayerControlWidget::onClickedLayer);
}

void VideoTimeLine::updateLayerHeight()
{
    m_layerBackWidget->setFixedHeight((m_layerControlWidget->getLayerItemCount() + 1) * 40);
}

void VideoTimeLine::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.fillRect(this->rect(), QColor(31, 32, 38));

    return __super::paintEvent(event);
}

void VideoTimeLine::resizeEvent(QResizeEvent *event)
{
    // 防止 LayerDrawWidget 未铺满窗口;
    int scrollWidth = m_scrollArea->width();
    int layerWidth = m_layerControlWidget->width();
    int programWidth = scrollWidth - layerWidth;
    m_layerDrawWidget->setFixedWidth(programWidth);

    return QWidget::resizeEvent(event);
}

void VideoTimeLine::showEvent(QShowEvent *event)
{
    // 防止 LayerDrawWidget 未铺满窗口;
    int scrollWidth = m_scrollArea->width();
    int layerWidth = m_layerControlWidget->width();
    int programWidth = scrollWidth - layerWidth;
    m_layerDrawWidget->setFixedWidth(programWidth);

    return QWidget::showEvent(event);
}
