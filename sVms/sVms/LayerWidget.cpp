#include "LayerWidget.h"

LayerControlWidget::LayerControlWidget(QWidget *parent)
	: QWidget(parent)
{
	m_mainLayout = new QBoxLayout(QBoxLayout::TopToBottom, this);
	m_mainLayout->addStretch();
	m_mainLayout->setSpacing(0);
	m_mainLayout->setMargin(0);

	this->setFixedWidth(150);
	
}

LayerControlWidget::~LayerControlWidget()
{
}

void LayerControlWidget::addLayerItem()
{
    LayerItemWidget* itemWidget = createLayerItem();
    itemWidget->setLayerName(QObject::tr("%1").arg(m_layerItemWidgetList.size() + 1));
    itemWidget->setLayerIndex(m_layerItemWidgetList.size() + 1);
	m_mainLayout->addWidget(itemWidget);
    m_layerItemWidgetList.append(itemWidget);
}

void LayerControlWidget::insertLayerItem(int layerIndex)
{
    if (layerIndex > m_layerItemWidgetList.size() + 1)
    {
        layerIndex = m_layerItemWidgetList.size() + 1;
    }
    else if (layerIndex < 0)
    {
        layerIndex = 1;
    }

    LayerItemWidget* itemWidget = createLayerItem();
    itemWidget->setLayerName(QObject::tr("图层%1").arg(layerIndex + 1));
    itemWidget->setLayerIndex(layerIndex + 1);

    m_mainLayout->insertWidget(layerIndex + 1, itemWidget);
    m_layerItemWidgetList.insert(layerIndex, itemWidget);

    // 更新后面图层名称;
    for (int i = layerIndex + 1; i < m_layerItemWidgetList.size(); i++)
    {
        m_layerItemWidgetList[i]->setLayerIndex(i + 1);
        m_layerItemWidgetList[i]->setLayerName(QObject::tr("图层%1").arg(i + 1));
    }
}

void LayerControlWidget::deleteLayerItem(int layerIndex)
{
    if (layerIndex > m_layerItemWidgetList.size() + 1)
    {
        layerIndex = m_layerItemWidgetList.size() + 1;
    }
    else if (layerIndex < 0)
    {
        layerIndex = 1;
    }

    m_mainLayout->removeWidget(m_layerItemWidgetList[layerIndex - 1]);
    // 这里需要调用deleteLater,(不能直接delete,测试使用delete会中断);
    // 否在该widget还是会残留在界面中;
    m_layerItemWidgetList[layerIndex - 1]->deleteLater();
    m_layerItemWidgetList.removeAt(layerIndex - 1);

    // 更新后面图层名称;
    for (int i = layerIndex - 1; i < m_layerItemWidgetList.size(); i++)
    {
        m_layerItemWidgetList[i]->setLayerIndex(i + 1);
        m_layerItemWidgetList[i]->setLayerName(QObject::tr("图层%1").arg(i + 1));
    }
}

int LayerControlWidget::getLayerItemCount()
{
	return m_layerItemWidgetList.count();
}

void LayerControlWidget::onClickedLayer(int layerIndex)
{
	for (int i = 0; i < m_layerItemWidgetList.count(); i++)
	{
		m_layerItemWidgetList[i]->setIsChecked(false);
		QRect itemWidgetRect = m_layerItemWidgetList[i]->rect().translated(m_layerItemWidgetList[i]->pos());
		if (layerIndex == i)
		{
			m_layerItemWidgetList[i]->setIsChecked(true);
		}
	}
}

LayerItemWidget* LayerControlWidget::createLayerItem()
{
    LayerItemWidget* layerItemWidget = new LayerItemWidget;
    return layerItemWidget;
}

void LayerControlWidget::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.fillRect(this->rect(), Qt::black);

    return __super::paintEvent(event);
}

void LayerControlWidget::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		QPoint mousePoint = event->pos();
		for (int i = 0; i < m_layerItemWidgetList.count(); i ++)
		{
			m_layerItemWidgetList[i]->setIsChecked(false);
			QRect itemWidgetRect = m_layerItemWidgetList[i]->rect().translated(m_layerItemWidgetList[i]->pos());
			if (itemWidgetRect.contains(mousePoint))
			{
				m_layerItemWidgetList[i]->setIsChecked(true);
			}
		}
	}
}
