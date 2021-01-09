#include "TimeScaleControlWidget.h"
#include <QHBoxLayout>

TimeScaleControlWidget::TimeScaleControlWidget(QWidget *parent)
	: QWidget(parent)
{
	initWidget();
	this->setFixedSize(QSize(160, 75));
}

TimeScaleControlWidget::~TimeScaleControlWidget()
{
}

void TimeScaleControlWidget::initWidget()
{
	QWidget* pButtonBackWidget = new QWidget;
	pButtonBackWidget->setFixedSize(QSize(160, 30));
	pButtonBackWidget->setStyleSheet("QToolButton{border:none;margin-top:5px;}");

	m_scaleSlider = new QSlider(Qt::Horizontal);
	m_scaleSlider->setFixedSize(QSize(100, 30));
	m_scaleSlider->setStyleSheet("QSlider::groove:horizontal{border:1px solid white;height:3px;left:6px; right:6px;}\
											QSlider::handle:horizontal{border:0px;border-image:url(:/Resources/SliderButton.png);width:15px;height:15px;margin:-6px -6px -6px -6px;}\
											QSlider::add-page:horizontal{background:gray;}QSlider::sub-page:horizontal{background:rgb(33, 150, 243);}");

	m_scaleSlider->setPageStep(1);
	// 设置放大缩小范围;
	m_scaleSlider->setRange(1, 8);
	connect(m_scaleSlider, &QSlider::valueChanged, this, [=](int value){
		emit signalTimeScaleChanged(m_scaleSlider->value());
	});

	m_pButtonSub = new QToolButton;
	m_pButtonSub->setIcon(QIcon(":/res/SoftIcon/subButton.png"));
	m_pButtonSub->setIconSize(QSize(20, 20));
	m_pButtonSub->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	connect(m_pButtonSub, &QToolButton::clicked, this, [=]{
		if (m_scaleSlider->value() == m_scaleSlider->minimum())
		{
			return;
		}

		m_scaleSlider->setValue(m_scaleSlider->value() - 1);
	});

	m_pButtonAdd = new QToolButton;
	m_pButtonAdd->setIcon(QIcon(":/res/SoftIcon/addButton.png"));
	m_pButtonAdd->setIconSize(QSize(20, 20));
	m_pButtonAdd->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
	connect(m_pButtonAdd, &QToolButton::clicked, this, [=]{
		if (m_scaleSlider->value() == m_scaleSlider->maximum())
		{
			return;
		}

		m_scaleSlider->setValue(m_scaleSlider->value() + 1);
	});

	QHBoxLayout* hButtonLayout = new QHBoxLayout(pButtonBackWidget);
	hButtonLayout->addWidget(m_pButtonSub);
	hButtonLayout->addWidget(m_scaleSlider);
	hButtonLayout->addSpacing(6);
	hButtonLayout->addWidget(m_pButtonAdd);
	hButtonLayout->setSpacing(4);
	hButtonLayout->setMargin(3);

	QVBoxLayout* vMainLayout = new QVBoxLayout(this);
	vMainLayout->addWidget(pButtonBackWidget);
	vMainLayout->addStretch();
	vMainLayout->setSpacing(0);
	vMainLayout->setMargin(0);
}

void TimeScaleControlWidget::onScaleChanged(bool isAdd)
{
	if (isAdd)
	{
		m_pButtonAdd->clicked();
	}
	else
	{
		m_pButtonSub->clicked();
	}
}
