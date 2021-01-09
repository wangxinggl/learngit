#pragma once

#include <QDialog>
#include "ui_AnalyseVideoAreaDlg.h"
#include "Configsetting.h"
#include "myhelper.h"
#include "Device/JLNDevice.h"
#include <QRect>
#include <QDebug>
#include <QMouseEvent>
#include <QMouseEventTransition>
#include <QDesktopWidget>

#define  OCX_DRAW_COLOUR_BASIC			RGB(0,255,255)
#define  OCX_DRAW_COLOUR_ARROW			RGB(255,0,0) 
#define  OCX_DRWA_COLOUR_ALARM			RGB(255,0,0) 
#define  OCX_DRAW_COLOUR_ARROW_ALARM	RGB(0,0,255) 

#define PI 3.14159265358979

#define _ARROWANGLE_ 20.0/180 * 3.14159


class AnalyseVideoAreaDlg : public QDialog
{
	Q_OBJECT

public:
	AnalyseVideoAreaDlg(QWidget *parent = Q_NULLPTR);
	~AnalyseVideoAreaDlg();
	void init();
public:
	long OpenPlay(CJLNDevice* pDevObj, long lChannel = 0, long lStreamType = 0);
	long StopPlay(CJLNDevice* pDevObj);
	long OnDraw(LONG nPort, HDC hdc);
	long CheckStartDraw();
	void GetArrowPoint(double val, QPoint InP1, QPoint InP2, QPoint &OutP1, QPoint &OutP2, int nMaxWidth, int nMaxHeight);
	int GetArrowCoordinate(QPoint p1, QPoint p2, QPoint p3);
	double LineSlopeAngle(QPoint ptStart, QPoint ptEnd);
	void ShowLabel(HDC hdc, QPoint ptStart, QPoint ptEnd);
	QPoint NextPointOfLine(double LineAngle, QPoint ThisPt, double DistanceFromThisPt);
	double NormalizeAngle(double Angle);
	void DrawPreMaskIntelligenceOnDraw(HDC hdc, QPoint pt1, QPoint pt2);
	BOOL CheckIsIllegal(long lDrawType, QPoint ptStart, QPoint ptEnd);
	
private:
	Ui::AnalyseVideoAreaDlg ui;
public:
	//long m_lPlayhandle;
	//long m_nPort;
	//long m_lPlaydecHandle;
	long m_lVideoAreaWidth;
	long m_lVdieoAreaHeight;
	//四个矩形
	RECTANGLE_COORDINATE       m_RectangleCoordinate[DRAW_RECTANGLE_COUNT];
	QPoint  m_RectanglePrevPoint;
	BOOL    m_bDrawRectangleStart;

	//四个三角形
	TRIANGLE_COORDINATE        m_TriangleCoordinate[DRAW_TRIANGLE_COUNT];
	QPoint  m_TrianglePrevPoint;

	//四个不规则四边形
	QUADRILATERAL_COORDINATE   m_QuadrilateralCoordinate[DRAW_QUADRILATERA_COUNT];
	QPoint  m_QuadrilateralPrevPoint;

	int m_ImageWidth;
	int m_ImageHeight;
	BOOL m_bDrawLineStart;
	DWORD m_DrawColorrefArrow;
	COLORREF m_dwcolor;
	long m_lMaxRectangele;
	BOOL m_bDraw;
	//一条直线（暂时只开一条直线）
	LINE_COORDINATE				m_LineCoordinate[DRAW_LINE_COUNT];
	long m_nArrowDirection;			//箭头方向 垂直：0 = 右，1 = 左；水平：0 = 上，1 = 下；倾斜：0 = 右，1 = 左;3 = 双向
	long m_nArrowDirectionTwoWay;
	BOOL m_bArrowStart;				//画箭头
	QPoint m_ArrowPrevPoint;
	QPoint m_LineFirstPoint;
	QPoint m_LinePrevPoint;

	QPoint  m_AreaPrevPoint;
	QPoint  m_AreaFirstPoint;

	QPoint point;
protected:
	//鼠标点击事件
	void mousePressEvent(QMouseEvent* event);
	//鼠标移动事件
	void mouseMoveEvent(QMouseEvent *event);
	//鼠标释放事件
	void mouseReleaseEvent(QMouseEvent *event);


	
};
