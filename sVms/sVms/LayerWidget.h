#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QToolButton>
#include <QPainter>
#include <QTime>
#include <QMouseEvent>
#include <QMenu>
#include <QScrollArea>
#include <QPushButton>
#include <QComboBox>

#pragma execution_character_set("utf-8") 

class TimeHeaderWidget : public QWidget
{
    Q_OBJECT
public:
	TimeHeaderWidget(QWidget* parent = NULL)
        : QWidget(parent)
    {
		m_dateTime.setDate(QDate::currentDate());
		m_currentTimeLabel = new QLabel(m_dateTime.toString("yyyy-MM-dd ") + "00:00:00");
        m_currentTimeLabel->setStyleSheet("color:rgb(255, 250, 250);");

		m_leftButton = new QPushButton("<");
		m_leftButton->setFixedSize(QSize(30, 20));
		connect(m_leftButton, &QPushButton::clicked, this, [=]{
			emit signalTimeLineMove(false);
		});

		m_rightButton = new QPushButton(">");
		m_rightButton->setFixedSize(QSize(30, 20));
		connect(m_rightButton, &QPushButton::clicked, this, [=]{
			emit signalTimeLineMove(true);
		});

        QHBoxLayout* hLayout = new QHBoxLayout(this);
		hLayout->addWidget(m_leftButton);
		hLayout->addStretch();
        hLayout->addWidget(m_currentTimeLabel);
		hLayout->addStretch();
		hLayout->addWidget(m_rightButton);

		this->setFixedHeight(35);

		this->setStyleSheet("QPushButton{border-radius:10px;border:1px solid gray;}");
    }

	// 设置当前显示日期;
	void setDate(QString& data)
	{
		//m_dateTime.setDate(data);
		m_currentTimeLabel->setText(data);
	}

signals:
	// 点击左右按钮移动时间轴;
	void signalTimeLineMove(bool isMoveRight);

public slots:
	// 更新当前显示时间;
	void onUpdateCurrentTime(QTime time)
	{
		m_dateTime.setTime(time);
		m_currentTimeLabel->setText(m_dateTime.toString("yyyy-MM-dd hh:mm:ss"));
	}

private:
    void paintEvent(QPaintEvent *event)
    {
        QPainter painter(this);
		painter.fillRect(this->rect(), QColor(31, 32, 38));
    }

private:
	QDateTime m_dateTime;
	QPushButton* m_leftButton;
	QPushButton* m_rightButton;
    QLabel * m_currentTimeLabel;
};

class LayerItemWidget : public QWidget
{
	Q_OBJECT

public:
	LayerItemWidget(QWidget* parent = NULL)
		: QWidget(parent)
		, m_layerIndex(-1)
		, m_isChecked(false)
	{
		m_layerNameLabel = new QLabel();
		m_layerNameLabel->setStyleSheet("color::black;font-size:15px;");

		m_comboBox = new QComboBox;
		m_comboBox->setFixedSize(QSize(40, 40));

		QHBoxLayout* hLayout = new QHBoxLayout(this);
		hLayout->addWidget(m_layerNameLabel);
		hLayout->addStretch();
//		hLayout->addWidget(m_comboBox);
		hLayout->setSpacing(10);
		hLayout->setContentsMargins(10, 0, 0, 0);

		this->setFixedHeight(40);
		this->setStyleSheet("QToolButton{background:transparent;border:none;}");
	}

	// 设置图层名称;
	void setLayerName(QString strName)
	{
		m_layerNameLabel->setText(strName);
		m_layerNameLabel->setScaledContents(true);
	}

	// 设置当前图层层数;
	void setLayerIndex(int layerIndex)
	{
		m_layerIndex = layerIndex;
	}

	// 设置当前是否选中状态;
	void setIsChecked(bool isChecked)
	{
		m_isChecked = isChecked;
		update();
	}

private:
	void paintEvent(QPaintEvent *event)
	{
		QPainter painter(this);
		if (m_isChecked)
		{
			painter.fillRect(this->rect(), QColor(40, 123, 213));
		}
		else
		{
			painter.fillRect(this->rect(), QColor(60, 65, 85));
		}
		painter.fillRect(this->rect(), QColor(60, 65, 85));
		painter.setPen(QPen(QColor(225, 225, 225), 1));
		painter.drawRect(this->rect().adjusted(0, 0, -1, -1));
	}

private:
	QLabel* m_layerNameLabel;
	QComboBox* m_comboBox;

	int m_layerIndex;
	bool m_isChecked;
};

class LayerControlWidget : public QWidget
{
	Q_OBJECT

public:
    LayerControlWidget(QWidget *parent = NULL);
	~LayerControlWidget();

    // 增加新的图层;
	void addLayerItem();
    // 插入图层;
    void insertLayerItem(int layerIndex);
    // 删除图层;
    void deleteLayerItem(int layerIndex);
    // 获取当前图层数目;
	int getLayerItemCount();
	// 当前点击了某个图层，用于切换背景色;
	void onClickedLayer(int layerIndex);

private:
    LayerItemWidget* createLayerItem();

	// 自绘事件;
	void paintEvent(QPaintEvent *event);

	void mousePressEvent(QMouseEvent *event);

private:
	QBoxLayout* m_mainLayout;
	QList<LayerItemWidget*> m_layerItemWidgetList;
};