#include "AnalyseVideoAreaDlg.h"


extern AnalyseVideoAreaDlg* g_pAnalyseDlg;

AnalyseVideoAreaDlg::AnalyseVideoAreaDlg(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	init();
	setWindowFlags(Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
}

AnalyseVideoAreaDlg::~AnalyseVideoAreaDlg()
{
}

void AnalyseVideoAreaDlg::init()
{
	m_bDrawRectangleStart = FALSE;
	m_RectanglePrevPoint.setX(0);
	m_RectanglePrevPoint.setY(0);
	m_ImageWidth = 0;
	m_ImageHeight = 0;
	m_bDrawLineStart = FALSE;
	m_DrawColorrefArrow = OCX_DRAW_COLOUR_ARROW;

	m_dwcolor = OCX_DRAW_COLOUR_BASIC;

	m_lMaxRectangele = DRAW_RECTANGLE_COUNT;

	m_bDraw = TRUE;
}

long AnalyseVideoAreaDlg::OpenPlay(CJLNDevice* pDevObj, long lChannel, long lStreamType)
{
	if (pDevObj->m_lUserLoginID > 0)
	{
		if (pDevObj->OpenChannel(lChannel + 1, lStreamType, (HWND)this->winId(), 0, (void*)this))
		{
			g_pAnalyseDlg = this;
		}
		else
		{
			g_pAnalyseDlg = NULL;
		}
	}
	
	return 0;
}

long AnalyseVideoAreaDlg::OnDraw(LONG nPort, HDC hdc)
{
	double dbWScale = 1;
	double dbHScale = 1;

	//	TRACE("nWidth = %d,nHeight = %d,g_ImageWidth = %d,g_ImageHeight = %d,比例:dbWScale = %lf,dbHScale = %lf\n",nWidth,nHeight,g_ImageWidth,g_ImageHeight,dbWScale,dbHScale,g_nArrowDirectionTwoWay);
	long lDrawType = CheckStartDraw();
	if (-1 == lDrawType)
	{
		return 0;
	}

	LOGBRUSH	brushlog;
	HPEN   m_pen;
	m_pen = CreatePen(PS_SOLID, 3, m_dwcolor);
	HGDIOBJ pen = SelectObject(hdc, m_pen);

	HBRUSH		hBrush;
	brushlog.lbColor = OCX_SELECT_COLOR;
	brushlog.lbHatch = HS_CROSS;
	brushlog.lbStyle = BS_NULL;

	hBrush = CreateBrushIndirect(&brushlog);
	HGDIOBJ  hOldBrush = SelectObject(hdc, hBrush);


	if (lDrawType == DRAW_PEN_Line)
	{
		for (int i = 0; i < DRAW_LINE_COUNT; i++)
		{
			if (m_LineCoordinate[i].bDrawFinish)
			{
				QPoint rpt1, rpt2;

				QPoint ptStart, ptEnd;
				double dbX, dbY;
				dbX = double(m_LineCoordinate[i].LinePoint[0].x()) * dbWScale;
				ptStart.rx() = int(dbX);
				dbY = double(m_LineCoordinate[i].LinePoint[0].y()) * dbHScale;
				ptStart.ry() = int(dbY);

				dbX = double(m_LineCoordinate[i].LinePoint[1].x()) * dbWScale;
				ptEnd.rx() = int(dbX);
				dbY = double(m_LineCoordinate[i].LinePoint[1].y()) * dbHScale;
				ptEnd.ry() = int(dbY);

				MoveToEx(hdc, ptStart.x() + 1, ptStart.y() + 1, NULL);
				LineTo(hdc, ptEnd.x() + 1, ptEnd.y() + 1);

				if (m_bArrowStart)
				{
					QPoint OutP1, OutP2;		//OutP1 左或下；OutP2右或上


					QPoint ArrowPrevPoint;
					dbX = double(m_ArrowPrevPoint.x()) * dbWScale;
					ArrowPrevPoint.rx() = int(dbX);
					dbY = double(m_ArrowPrevPoint.y()) * dbHScale;
					ArrowPrevPoint.ry() = int(dbY);

					if (ptStart.x() < ptEnd.x())
					{
						GetArrowPoint(_ARROWANGLE_, ptStart, ptEnd, OutP1, OutP2, m_lVideoAreaWidth, m_lVdieoAreaHeight);
						if (m_ArrowPrevPoint.x() == -1 && m_ArrowPrevPoint.y() == -1)
						{
						}
						else
						{
							m_nArrowDirection = GetArrowCoordinate(ptStart, ptEnd, ArrowPrevPoint);
						}

					}
					else
					{
						GetArrowPoint(_ARROWANGLE_, ptEnd, ptStart, OutP1, OutP2, m_lVideoAreaWidth, m_lVdieoAreaHeight);
						if (m_ArrowPrevPoint.x() == -1 && m_ArrowPrevPoint.y() == -1)
						{
						}
						else
						{
							m_nArrowDirection = GetArrowCoordinate(ptEnd, ptStart, ArrowPrevPoint);
						}

					}

					HPEN   m_pen1;
					m_pen1 = CreatePen(PS_SOLID, 5, m_DrawColorrefArrow/*RGB( 255,0,0)*/);
					HGDIOBJ pen1 = SelectObject(hdc, m_pen1);

					MoveToEx(hdc, OutP1.x(), OutP1.y(), NULL);
					LineTo(hdc, OutP2.x(), OutP2.y());

					if (m_nArrowDirectionTwoWay == 1)
					{
						m_nArrowDirection = 3;
					}


					if (m_nArrowDirection == 0)		//箭头方向 垂直：0 = 右，1 = 左；水平：0 = 上，1 = 下；倾斜：0 = 右，1 = 左 ; 3= 双向
					{
						ShowLabel(hdc, OutP1, OutP2);
					}
					else if (m_nArrowDirection == 1)
					{
						ShowLabel(hdc, OutP2, OutP1);
					}
					else if (m_nArrowDirection == 3)
					{
						ShowLabel(hdc, OutP1, OutP2);
						ShowLabel(hdc, OutP2, OutP1);
					}
					HFONT hFont, hOldFont;
					hFont = CreateFont(25, 25, 0, 0, FW_THIN, false, false, false,
						CHINESEBIG5_CHARSET, OUT_CHARACTER_PRECIS,
						CLIP_CHARACTER_PRECIS, DEFAULT_QUALITY,
						FF_MODERN, "宋体");
					hOldFont = (HFONT)SelectObject(hdc, (HFONT)hFont);

					SetTextColor(hdc, RGB(0, 0, 0));
					TextOut(hdc, OutP1.x() - 40, OutP1.y(), "A", 1);
					TextOut(hdc, OutP2.x() + 20, OutP2.y(), "B", 1);

					SelectObject(hdc, hOldFont);
					DeleteObject(hFont);


					SelectObject(hdc, pen1);
					DeleteObject(m_pen1);
					qDebug()<<"*******************画图\n";
				}

			}
		}
	}
	else if (lDrawType == DRAW_PEN_Rectangle)	//矩形
	{
		QRect r;
		for (int i = 0; i < DRAW_RECTANGLE_COUNT; i++)
		{
			if (m_RectangleCoordinate[i].bDrawFinish)
			{
				QPoint rpt1, rpt2;

				rpt1.rx() = int(m_RectangleCoordinate[i].RectanglePoint[0].x());
				rpt1.ry() = int(m_RectangleCoordinate[i].RectanglePoint[0].y());

				rpt2.rx() = int(m_RectangleCoordinate[i].RectanglePoint[1].x());
				rpt2.ry() = int(m_RectangleCoordinate[i].RectanglePoint[1].y());

				Rectangle(hdc, rpt1.x(), rpt1.y(), rpt2.x(), rpt2.y());
			}
		}
	}
	else if (lDrawType == DRAW_PEN_Triangle)	//三角形
	{
		for (int i = 0; i < DRAW_TRIANGLE_COUNT; i++)
		{
			if (m_TriangleCoordinate[i].bDrawFinish)
			{
				MoveToEx(hdc, m_TriangleCoordinate[i].TrianglePoint[0].x() + 1, m_TriangleCoordinate[i].TrianglePoint[0].y() + 1, NULL);
				LineTo(hdc, m_TriangleCoordinate[i].TrianglePoint[1].x() + 1, m_TriangleCoordinate[i].TrianglePoint[1].y() + 1);

				MoveToEx(hdc, m_TriangleCoordinate[i].TrianglePoint[1].x() + 1, m_TriangleCoordinate[i].TrianglePoint[1].y() + 1, NULL);
				LineTo(hdc, m_TriangleCoordinate[i].TrianglePoint[2].x() + 1, m_TriangleCoordinate[i].TrianglePoint[2].y() + 1);

				MoveToEx(hdc, m_TriangleCoordinate[i].TrianglePoint[2].x() + 1, m_TriangleCoordinate[i].TrianglePoint[2].y() + 1, NULL);
				LineTo(hdc, m_TriangleCoordinate[i].TrianglePoint[0].x() + 1, m_TriangleCoordinate[i].TrianglePoint[0].y() + 1);
			}
		}
	}
	else if (lDrawType == DRAW_PEN_Quadrilateral)  //四边形
	{
		for (int i = 0; i < DRAW_QUADRILATERA_COUNT; i++)
		{
			if (m_QuadrilateralCoordinate[i].bDrawFinish)
			{

				MoveToEx(hdc, m_QuadrilateralCoordinate[i].QuadrilateralPoint[0].x() + 1, m_QuadrilateralCoordinate[i].QuadrilateralPoint[0].y() + 1, NULL);
				LineTo(hdc, m_QuadrilateralCoordinate[i].QuadrilateralPoint[1].x() + 1, m_QuadrilateralCoordinate[i].QuadrilateralPoint[1].y() + 1);

				MoveToEx(hdc, m_QuadrilateralCoordinate[i].QuadrilateralPoint[1].x() + 1, m_QuadrilateralCoordinate[i].QuadrilateralPoint[1].y() + 1, NULL);
				LineTo(hdc, m_QuadrilateralCoordinate[i].QuadrilateralPoint[2].x() + 1, m_QuadrilateralCoordinate[i].QuadrilateralPoint[2].y() + 1);

				MoveToEx(hdc, m_QuadrilateralCoordinate[i].QuadrilateralPoint[2].x() + 1, m_QuadrilateralCoordinate[i].QuadrilateralPoint[2].y() + 1, NULL);
				LineTo(hdc, m_QuadrilateralCoordinate[i].QuadrilateralPoint[3].x() + 1, m_QuadrilateralCoordinate[i].QuadrilateralPoint[3].y() + 1);

				MoveToEx(hdc, m_QuadrilateralCoordinate[i].QuadrilateralPoint[3].x() + 1, m_QuadrilateralCoordinate[i].QuadrilateralPoint[3].y() + 1, NULL);
				LineTo(hdc, m_QuadrilateralCoordinate[i].QuadrilateralPoint[0].x() + 1, m_QuadrilateralCoordinate[i].QuadrilateralPoint[0].y() + 1);
			}
		}

	}

	SelectObject(hdc, hOldBrush);
	SelectObject(hdc, pen);
	DeleteObject(hBrush);
	DeleteObject(m_pen);
	hBrush = NULL;
	DrawPreMaskIntelligenceOnDraw(hdc, m_AreaFirstPoint, m_AreaPrevPoint);
	return 0;
}

//画带箭头的线段
void AnalyseVideoAreaDlg::ShowLabel(HDC hdc, QPoint ptStart, QPoint ptEnd)
{
	double Angle = LineSlopeAngle(ptStart, ptEnd);
	POINT* pp = new POINT[6];
	/*pp[0] = ptEnd;
	pp[1] = NextPointOfLine(Angle + PI / 9, ptEnd, 50);
	pp[2] = NextPointOfLine(Angle, ptEnd, 50);
	pp[3] = NextPointOfLine(Angle - PI / 9, ptEnd, 50);*/
	Polygon(hdc, pp, 4);
	delete pp;
}

//求点，该点与ThisPt距离为DistanceFromThisPt，倾角为LineAngle
QPoint AnalyseVideoAreaDlg::NextPointOfLine(double LineAngle, QPoint ThisPt, double DistanceFromThisPt)
{
	double X, Y, M;
	double Angle;
	QPoint Result;

	Angle = NormalizeAngle(LineAngle);
	if (fabs(Angle) != PI / 2)
	{
		M = tan(LineAngle);
		if (fabs(Angle) < PI / 2)
			X = ThisPt.x() - DistanceFromThisPt / sqrt(1 + M*M);
		else
			X = ThisPt.x() + DistanceFromThisPt / sqrt(1 + M*M);
		Y = ThisPt.y() + M * (X - ThisPt.x());
		Result.rx() = round(X);
		Result.ry() = round(Y);
	}
	else
	{
		Result.rx() = ThisPt.rx();
		if (Angle > 0)
			Result.ry() = ThisPt.ry() - round(DistanceFromThisPt);
		else
			Result.ry() = ThisPt.ry() + round(DistanceFromThisPt);
	}
	return Result;
}

//角度范围[-PI，+PI]
double AnalyseVideoAreaDlg::NormalizeAngle(double Angle)
{
	double Result;

	Result = Angle;
	while (Result > PI)
		Result = Result - 2 * PI;
	while (Result < -PI)
		Result = Result + 2 * PI;
	return Result;
}

long AnalyseVideoAreaDlg::CheckStartDraw()
{
	long lDrawType = DRAW_PEN_Rectangle;
	if (!m_bDraw)
	{
		return lDrawType;
	}

	return lDrawType;
}

void AnalyseVideoAreaDlg::GetArrowPoint(double val, QPoint InP1, QPoint InP2, QPoint &OutP1, QPoint &OutP2, int nMaxWidth, int nMaxHeight)
{
	char strlog[128] = { 0 };
	if (InP1.x() == InP2.x())     //垂直
	{
		if (InP1.x() - 250 < 0)
			OutP1.rx() = 0;
		else
			OutP1.rx() = InP1.x() - 250;

		OutP1.ry() = (InP1.y() + InP2.y()) / 2;
		if (InP1.x() + 250 > nMaxWidth)
			OutP2.rx() = nMaxWidth;
		else
			OutP2.rx() = InP1.x() + 250;
		OutP2.ry() = (InP1.y() + InP2.y()) / 2;
		return;
	}
	if (InP1.y() == InP2.y())     //水平
	{
		OutP1.rx() = (InP1.x() + InP2.x()) / 2;
		if (InP1.y() + 150 > nMaxHeight)
			OutP1.ry() = nMaxHeight;
		else
			OutP1.ry() = InP1.y() + 250;

		OutP2.rx() = (InP1.x() + InP2.x()) / 2;
		if (InP1.ry() - 150 < 0)
			OutP2.ry() = 0;
		else
			OutP2.ry() = InP1.y() - 250;
		return;
	}
	double m1, m2, n1, n2;
	double xmid, ymid;
	double k = ((double)(InP1.y() - InP2.y())) / ((double)(InP1.x() - InP2.x()));
	ymid = (InP1.y() + InP2.y()) / 2.0;
	xmid = (InP1.x() + InP2.x()) / 2.0;
	double d = sqrt((double)((InP1.y() - InP2.y())*(InP1.y() - InP2.y()) + (InP1.x() - InP2.x())*(InP1.x() - InP2.x()))) / 2.0;  //by zjh
	double s = d * tan(val) * d / 2;
	double x1 = (double)InP1.x();
	double y1 = (double)InP1.y();

	if (1)
	{
		m1 = (2 * k * s + x1 * xmid - xmid*xmid + k * xmid*y1 - k*xmid*ymid) / (x1 - xmid + k*y1 - k*ymid);
		n1 = -(2 * s - x1*ymid + xmid*ymid + k*ymid*ymid - k*y1*ymid) / (x1 - xmid + k*y1 - k*ymid);
		m2 = -(2 * k*s - x1*xmid + xmid*xmid - k*xmid*y1 + k*xmid*ymid) / (x1 - xmid + k*y1 - k*ymid);
		n2 = (2 * s + x1*ymid - xmid*ymid - k*ymid*ymid + k*y1*ymid) / (x1 - xmid + k*y1 - k*ymid);
	}
	else
	{
		m1 = xmid + k*ymid - k*(ymid - (d*sqrt(4 / (3 * (k*k + 1)))) / 2);
		m2 = xmid + k*ymid - k*(ymid + (d*sqrt(4 / (3 * (k*k + 1)))) / 2);

		n1 = ymid - (d*sqrt(4 / (3 * (k*k + 1)))) / 2;
		n2 = ymid + (d*sqrt(4 / (3 * (k*k + 1)))) / 2;
	}

	if (m1 < m2)
	{
		OutP1.rx() = int(m1);
		OutP1.ry() = int(n1);
		OutP2.rx() = int(m2);
		OutP2.ry() = int(n2);
	}
	else
	{
		OutP1.rx() = int(m2);
		OutP1.ry() = int(n2);
		OutP2.rx() = int(m1);
		OutP2.ry() = int(n1);
	}
}

//获取箭头方向 p1 起点，p2 终点，p3鼠标点
int AnalyseVideoAreaDlg::GetArrowCoordinate(QPoint p1, QPoint p2, QPoint p3)			//箭头方向，垂直：0 = 右，1 = 左；水平：0 = 上，1 = 下；倾斜：0 = 右，1 = 左
{
	char strlog[128] = { 0 };
	int nRest = 0;


	if (p1.x() == p2.x())     //垂直
	{
		if (p3.x() > p1.x())	//箭头在右
		{
			nRest = 0;
		}
		else				//箭头在左
		{
			nRest = 1;
		}
		return nRest;
	}
	if (p1.y() == p2.y())     //水平
	{
		if (p3.y() > p1.y())	//箭头在下
		{
			nRest = 1;
		}
		else
		{
			nRest = 0;
		}
		return nRest;
	}


	double dwAngle1, dwAngle2;
	if (p1.x() < p2.x())							//已最左边的点为起点
	{
		dwAngle1 = LineSlopeAngle(p1, p2);
		dwAngle2 = LineSlopeAngle(p1, p3);
	}
	else
	{
		dwAngle1 = LineSlopeAngle(p2, p1);
		dwAngle2 = LineSlopeAngle(p2, p3);
	}

	if (dwAngle1 < 0)
	{
		if (dwAngle2 > dwAngle1 && dwAngle2 < PI + dwAngle1)
		{
			nRest = 0;
		}
		else
		{
			nRest = 1;
		}
	}
	else if (dwAngle1 > 0)
	{
		if (dwAngle2 > dwAngle1 - PI && dwAngle2 < dwAngle1)
		{
			nRest = 0;
		}
		else
		{
			nRest = 1;
		}
	}

	return nRest;
}

//两点，求线段倾角
double AnalyseVideoAreaDlg::LineSlopeAngle(QPoint ptStart, QPoint ptEnd)
{
	double Result;

	if (ptStart.x() != ptEnd.x())
		Result = atan2((double)(ptEnd.y() - ptStart.y()), (double)(ptEnd.x() - ptStart.x()));
	else if (ptStart.y() > ptEnd.y())
		Result = -PI / 2;
	else if (ptStart.y() < ptEnd.y())
		Result = +PI / 2;
	else
		Result = 0;
	return Result;
}

void AnalyseVideoAreaDlg::DrawPreMaskIntelligenceOnDraw(HDC hdc, QPoint pt1, QPoint pt2)
{
	double dbWScale = 1;//double(m_lVideoAreaWidth) / g_ImageWidth; 
	double dbHScale = 1;//double(m_lVdieoAreaHeight)/ g_ImageHeight; 

	HPEN   m_pen;
	m_pen = CreatePen(PS_SOLID, 5, OCX_SELECT_COLOR);
	HGDIOBJ pen = SelectObject(hdc, m_pen);
	LOGBRUSH	brushlog;
	HGDIOBJ		brush;
	HBRUSH		m_brush;
	brushlog.lbColor = RGB(0, 255, 208);
	brushlog.lbHatch = HS_CROSS;
	brushlog.lbStyle = BS_NULL;
	m_brush = CreateBrushIndirect(&brushlog);
	brush = SelectObject(hdc, m_brush);

	int drawmode = SetROP2(hdc, R2_XORPEN);
	int bkmode = SetBkMode(hdc, TRANSPARENT);

	long lDrawType = CheckStartDraw();
	if (-1 == lDrawType)
	{
		return;
	}


	int i = 0;

	if (lDrawType == DRAW_PEN_Line)
	{
		if (m_bDrawLineStart)
		{
			for (i = 0; i < DRAW_LINE_COUNT; i++)
			{
				if (!m_LineCoordinate[i].bDrawFinish)
				{
					MoveToEx(hdc, m_LineFirstPoint.x() * dbWScale + 1, m_LineFirstPoint.y() * dbHScale + 1, NULL);
					LineTo(hdc, m_LinePrevPoint.x() * dbWScale + 1, m_LinePrevPoint.y() * dbHScale + 1);
				}
			}
		}
	}
	else if (lDrawType == DRAW_PEN_Rectangle)
	{
		QRect r;
		if (m_bDrawRectangleStart)
		{
			for (i = 0; i < DRAW_RECTANGLE_COUNT; i++)
			{
				if (!m_RectangleCoordinate[i].bDrawFinish)
				{

					QPoint rpt1, rpt2;
					double dbX, dbY;
					dbX = double(m_RectangleCoordinate[i].RectanglePoint[0].x()) * dbWScale;
					rpt1.rx() = int(dbX);
					dbY = double(m_RectangleCoordinate[i].RectanglePoint[0].y()) * dbHScale;
					rpt1.ry() = int(dbY);

					dbX = double(m_RectanglePrevPoint.x()) * dbWScale;
					rpt2.rx() = int(dbX);
					dbY = double(m_RectanglePrevPoint.y()) * dbHScale;
					rpt2.ry() = int(dbY);

					if (rpt1.x() > rpt2.x())
					{
						int nX = rpt1.x();
						rpt1.rx() = rpt2.x();
						rpt2.rx() = nX;
					}
					if (rpt1.y() > rpt2.y())
					{
						int nY = rpt1.y();
						rpt1.ry() = rpt2.y();
						rpt2.ry() = nY;
					}
					Rectangle(hdc, rpt1.x(), rpt1.y(), rpt2.x(), rpt2.y());
					break;
				}
			}
		}
	}
	else if (lDrawType == DRAW_PEN_Triangle)	//三角形
	{
		for (i = 0; i < DRAW_TRIANGLE_COUNT; i++)
		{
			if (!m_TriangleCoordinate[i].bDrawFinish)
			{
				if (m_TriangleCoordinate[i].nPointNumber == 1)
				{
					MoveToEx(hdc, m_TriangleCoordinate[i].TrianglePoint[0].x() * dbWScale + 1, m_TriangleCoordinate[i].TrianglePoint[0].y() * dbHScale + 1, NULL);
					LineTo(hdc, m_TrianglePrevPoint.x() * dbWScale + 1, m_TrianglePrevPoint.y() * dbHScale + 1);
				}
				else if (m_TriangleCoordinate[i].nPointNumber == 2)
				{
					MoveToEx(hdc, m_TriangleCoordinate[i].TrianglePoint[0].x() * dbWScale + 1, m_TriangleCoordinate[i].TrianglePoint[0].y() * dbHScale + 1, NULL);
					LineTo(hdc, m_TriangleCoordinate[i].TrianglePoint[1].x() * dbWScale + 1, m_TriangleCoordinate[i].TrianglePoint[1].y() * dbHScale + 1);
					MoveToEx(hdc, m_TriangleCoordinate[i].TrianglePoint[1].x() * dbWScale + 1, m_TriangleCoordinate[i].TrianglePoint[1].y() * dbHScale + 1, NULL);
					LineTo(hdc, m_TrianglePrevPoint.x() * dbWScale + 1, m_TrianglePrevPoint.y() * dbHScale + 1);
				}

			}
		}
	}
	else if (lDrawType == DRAW_PEN_Quadrilateral)
	{
		for (i = 0; i < DRAW_QUADRILATERA_COUNT; i++)
		{
			if (!m_QuadrilateralCoordinate[i].bDrawFinish)
			{
				if (m_QuadrilateralCoordinate[i].nPointNumber == 1)
				{
					MoveToEx(hdc, m_QuadrilateralCoordinate[i].QuadrilateralPoint[0].x() * dbWScale + 1, m_QuadrilateralCoordinate[i].QuadrilateralPoint[0].y() * dbHScale + 1, NULL);
					LineTo(hdc, m_QuadrilateralPrevPoint.x() * dbWScale + 1, m_QuadrilateralPrevPoint.y() * dbHScale + 1);
				}
				else if (m_QuadrilateralCoordinate[i].nPointNumber == 2)
				{
					MoveToEx(hdc, m_QuadrilateralCoordinate[i].QuadrilateralPoint[0].x() * dbWScale + 1, m_QuadrilateralCoordinate[i].QuadrilateralPoint[0].y() * dbHScale + 1, NULL);
					LineTo(hdc, m_QuadrilateralCoordinate[i].QuadrilateralPoint[1].x() * dbWScale + 1, m_QuadrilateralCoordinate[i].QuadrilateralPoint[1].y() * dbHScale + 1);
					MoveToEx(hdc, m_QuadrilateralCoordinate[i].QuadrilateralPoint[1].x() * dbWScale + 1, m_QuadrilateralCoordinate[i].QuadrilateralPoint[1].y() * dbHScale + 1, NULL);
					LineTo(hdc, m_QuadrilateralPrevPoint.x() * dbWScale + 1, m_QuadrilateralPrevPoint.y() * dbHScale + 1);
				}
				else if (m_QuadrilateralCoordinate[i].nPointNumber == 3)
				{
					MoveToEx(hdc, m_QuadrilateralCoordinate[i].QuadrilateralPoint[0].x() * dbWScale + 1, m_QuadrilateralCoordinate[i].QuadrilateralPoint[0].y() * dbHScale + 1, NULL);
					LineTo(hdc, m_QuadrilateralCoordinate[i].QuadrilateralPoint[1].x() * dbWScale + 1, m_QuadrilateralCoordinate[i].QuadrilateralPoint[1].y() * dbHScale + 1);

					MoveToEx(hdc, m_QuadrilateralCoordinate[i].QuadrilateralPoint[1].x() * dbWScale + 1, m_QuadrilateralCoordinate[i].QuadrilateralPoint[1].y() * dbHScale + 1, NULL);
					LineTo(hdc, m_QuadrilateralCoordinate[i].QuadrilateralPoint[2].x() * dbWScale + 1, m_QuadrilateralCoordinate[i].QuadrilateralPoint[2].y() * dbHScale + 1);

					MoveToEx(hdc, m_QuadrilateralCoordinate[i].QuadrilateralPoint[2].x() * dbWScale + 1, m_QuadrilateralCoordinate[i].QuadrilateralPoint[2].y() * dbHScale + 1, NULL);
					LineTo(hdc, m_QuadrilateralPrevPoint.x() * dbWScale + 1, m_QuadrilateralPrevPoint.y() * dbHScale + 1);
				}
			}
		}

	}
	SelectObject(hdc, pen);
	SelectObject(hdc, brush);
	SetROP2(hdc, drawmode);
	SetBkMode(hdc, bkmode);

	DeleteObject(m_pen);
	DeleteObject(m_brush);
}

long AnalyseVideoAreaDlg::StopPlay(CJLNDevice* pDevObj)
{
	pDevObj->CloseChannel((HWND)this->winId());	
	g_pAnalyseDlg = NULL;
	return 0;
}

//鼠标点击事件
void AnalyseVideoAreaDlg::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::LeftButton)
	{
		long lDrawType = CheckStartDraw();
		if (-1 == lDrawType)
		{
			//return;
		}


		QDesktopWidget* desktopWidget = QApplication::desktop();
		QRect rc = desktopWidget->screenGeometry();
		//QRect(rc.x(), rc.y(), rc.width(), rc.height());
		m_ImageWidth = rc.width();
		m_ImageHeight = rc.height();

		m_AreaFirstPoint = event->pos();
		m_AreaPrevPoint = event->pos();

		double dbWScale = 1;
		double dbHScale = 1;
		int x1, y1, x2, y2, x3, y3, x4, y4;
		int i = 0;


		if (lDrawType == DRAW_PEN_Line)		//直线
		{
			m_bDrawLineStart = TRUE;
			for (i = 0; i < DRAW_LINE_COUNT; i++)
			{
				if (!m_LineCoordinate[i].bDrawFinish)
				{
					m_LineFirstPoint = event->pos();
					m_LinePrevPoint = event->pos();
					m_bArrowStart = FALSE;
					break;

				}
				else
				{
					m_bArrowStart = TRUE;
					m_ArrowPrevPoint = event->pos();

					x1 = m_ArrowPrevPoint.x();
					y1 = m_ArrowPrevPoint.y();


					double  dbX1 = double(x1) * dbWScale;
					x1 = int(dbX1);
					double  dbY1 = double(y1) * dbHScale;
					y1 = int(dbY1);
					m_ArrowPrevPoint.rx() = x1;
					m_ArrowPrevPoint.ry() = y1;
				}
			}
			m_nArrowDirectionTwoWay = 0;

		}
		else if (lDrawType == DRAW_PEN_Rectangle)
		{
			for (i = 0; i < DRAW_RECTANGLE_COUNT; i++)
			{
				if (!m_RectangleCoordinate[i].bDrawFinish)
				{
					m_RectangleCoordinate[i].RectanglePoint[0] = event->pos();
					m_RectanglePrevPoint = event->pos();
					m_bDrawRectangleStart = TRUE;
					break;
				}
			}

		}
		else if (lDrawType == DRAW_PEN_Triangle)   //三角形
		{
			for (i = 0; i < DRAW_TRIANGLE_COUNT; i++)
			{
				if (!m_TriangleCoordinate[i].bDrawFinish)
				{
					if (m_TriangleCoordinate[i].nPointNumber == 0)
					{
						m_TriangleCoordinate[i].TrianglePoint[0] = event->pos();
						m_TriangleCoordinate[i].nPointNumber = 1;
					}
					else if (m_TriangleCoordinate[i].nPointNumber == 1)
					{
						m_TriangleCoordinate[i].TrianglePoint[1] = event->pos();
						m_TriangleCoordinate[i].nPointNumber = 2;
					}
					else if (m_TriangleCoordinate[i].nPointNumber == 2)
					{
						m_TriangleCoordinate[i].TrianglePoint[2] = event->pos();
						m_TriangleCoordinate[i].nPointNumber = 3;
						m_TriangleCoordinate[i].bDrawFinish = TRUE;

						x1 = m_TriangleCoordinate[i].TrianglePoint[0].x();
						y1 = m_TriangleCoordinate[i].TrianglePoint[0].y();
						x2 = m_TriangleCoordinate[i].TrianglePoint[1].x();
						y2 = m_TriangleCoordinate[i].TrianglePoint[1].y();
						x3 = m_TriangleCoordinate[i].TrianglePoint[2].x();
						y3 = m_TriangleCoordinate[i].TrianglePoint[2].y();

						double  dbX1 = double(x1) * dbWScale;
						x1 = int(dbX1);
						double  dbY1 = double(y1) * dbHScale;
						y1 = int(dbY1);

						double  dbX2 = double(x2) * dbWScale;
						x2 = int(dbX2);
						double  dbY2 = double(y2) * dbHScale;
						y2 = int(dbY2);

						double  dbX3 = double(x3) * dbWScale;
						x3 = int(dbX3);
						double  dbY3 = double(y3) * dbHScale;
						y3 = int(dbY3);

						m_TriangleCoordinate[i].TrianglePoint[0].rx() = x1;
						m_TriangleCoordinate[i].TrianglePoint[0].ry() = y1;
						m_TriangleCoordinate[i].TrianglePoint[1].rx() = x2;
						m_TriangleCoordinate[i].TrianglePoint[1].ry() = y2;
						m_TriangleCoordinate[i].TrianglePoint[2].rx() = x3;
						m_TriangleCoordinate[i].TrianglePoint[2].ry() = y3;

					}
					m_TrianglePrevPoint = event->pos();
					break;
				}
			}
		}
		else if (lDrawType == DRAW_PEN_Quadrilateral)		//不规则四边形
		{
			for (i = 0; i < DRAW_QUADRILATERA_COUNT; i++)
			{
				if (!m_QuadrilateralCoordinate[i].bDrawFinish)
				{
					if (m_QuadrilateralCoordinate[i].nPointNumber == 0)
					{
						m_QuadrilateralCoordinate[i].QuadrilateralPoint[0] = event->pos();
						m_QuadrilateralCoordinate[i].nPointNumber = 1;
					}
					else if (m_QuadrilateralCoordinate[i].nPointNumber == 1)
					{
						m_QuadrilateralCoordinate[i].QuadrilateralPoint[1] = event->pos();
						m_QuadrilateralCoordinate[i].nPointNumber = 2;
					}
					else if (m_QuadrilateralCoordinate[i].nPointNumber == 2)
					{
						m_QuadrilateralCoordinate[i].QuadrilateralPoint[2] = event->pos();
						m_QuadrilateralCoordinate[i].nPointNumber = 3;
					}
					else if (m_QuadrilateralCoordinate[i].nPointNumber == 3)
					{
						m_QuadrilateralCoordinate[i].QuadrilateralPoint[3] = event->pos();
						m_QuadrilateralCoordinate[i].nPointNumber = 4;
						m_QuadrilateralCoordinate[i].bDrawFinish = TRUE;


						x1 = m_QuadrilateralCoordinate[i].QuadrilateralPoint[0].x();
						y1 = m_QuadrilateralCoordinate[i].QuadrilateralPoint[0].y();
						x2 = m_QuadrilateralCoordinate[i].QuadrilateralPoint[1].x();
						y2 = m_QuadrilateralCoordinate[i].QuadrilateralPoint[1].y();
						x3 = m_QuadrilateralCoordinate[i].QuadrilateralPoint[2].x();
						y3 = m_QuadrilateralCoordinate[i].QuadrilateralPoint[2].y();
						x4 = m_QuadrilateralCoordinate[i].QuadrilateralPoint[3].x();
						y4 = m_QuadrilateralCoordinate[i].QuadrilateralPoint[3].y();


						double  dbX1 = double(x1) * dbWScale;
						x1 = int(dbX1);
						double  dbY1 = double(y1) * dbHScale;
						y1 = int(dbY1);

						double  dbX2 = double(x2) * dbWScale;
						x2 = int(dbX2);
						double  dbY2 = double(y2) * dbHScale;
						y2 = int(dbY2);

						double  dbX3 = double(x3) * dbWScale;
						x3 = int(dbX3);
						double  dbY3 = double(y3) * dbHScale;
						y3 = int(dbY3);

						double  dbX4 = double(x4) * dbWScale;
						x4 = int(dbX4);
						double  dbY4 = double(y4) * dbHScale;
						y4 = int(dbY4);

						m_QuadrilateralCoordinate[i].QuadrilateralPoint[0].rx() = x1;
						m_QuadrilateralCoordinate[i].QuadrilateralPoint[0].ry() = y1;
						m_QuadrilateralCoordinate[i].QuadrilateralPoint[1].rx() = x2;
						m_QuadrilateralCoordinate[i].QuadrilateralPoint[1].ry() = y2;
						m_QuadrilateralCoordinate[i].QuadrilateralPoint[2].rx() = x3;
						m_QuadrilateralCoordinate[i].QuadrilateralPoint[2].ry() = y3;
						m_QuadrilateralCoordinate[i].QuadrilateralPoint[3].rx() = x4;
						m_QuadrilateralCoordinate[i].QuadrilateralPoint[3].ry() = y4;

					}
					m_QuadrilateralPrevPoint = event->pos();
					break;
				}
			}
		}

	}
}
//鼠标移动事件
void AnalyseVideoAreaDlg::mouseMoveEvent(QMouseEvent *event)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	long lDrawType = CheckStartDraw();
	if (-1 == lDrawType)
	{
		return;
	}


	if (lDrawType == DRAW_PEN_Line)
	{
		m_LinePrevPoint = event->pos();
	}
	else if (lDrawType == DRAW_PEN_Rectangle)
	{
		m_RectanglePrevPoint = event->pos();
	}
	else if (lDrawType == DRAW_PEN_Triangle)
	{
		m_TrianglePrevPoint = event->pos();
	}
	else if (lDrawType == DRAW_PEN_Quadrilateral)
	{
		m_QuadrilateralPrevPoint = event->pos();
	}


}
//鼠标释放事件
void AnalyseVideoAreaDlg::mouseReleaseEvent(QMouseEvent *event)
{
	if (event->button() == Qt::LeftButton)
	{
		// TODO: 在此添加消息处理程序代码和/或调用默认值
		long lDrawType = CheckStartDraw();
		if (-1 == lDrawType)
		{
			return;
		}

		/*if (NULL != m_pFaceShelterDlg)//
		{

			if (m_lMaxRectangele == 1)//限制画一条
			{
				if (m_RectangleCoordinate[0].bDrawFinish)
				{
					return;
				}
			}
		}*/

		int i = 0;

		if (m_ImageWidth == 0)
			m_ImageWidth = 1;
		if (m_ImageHeight == 0)
			m_ImageHeight = 1;

		double dbWScale = 1;
		double dbHScale = 1;

		int x1, y1, x2, y2;


		if (lDrawType == DRAW_PEN_Line)
		{
			m_bDrawLineStart = FALSE;

			for (i = 0; i < DRAW_LINE_COUNT; i++)
			{
				if (!m_LineCoordinate[i].bDrawFinish)
				{
					m_LinePrevPoint = event->pos();

					x1 = m_LineFirstPoint.x();
					y1 = m_LineFirstPoint.y();
					x2 = m_LinePrevPoint.x();
					y2 = m_LinePrevPoint.y();

					double  dbX1 = double(x1) * dbWScale;
					x1 = int(dbX1);
					double  dbY1 = double(y1) * dbHScale;
					y1 = int(dbY1);

					double  dbX2 = double(x2) * dbWScale;
					x2 = int(dbX2);
					double  dbY2 = double(y2) * dbHScale;
					y2 = int(dbY2);


					m_LineCoordinate[i].LinePoint[0].rx() = x1;
					m_LineCoordinate[i].LinePoint[0].ry() = y1;

					m_LineCoordinate[i].LinePoint[1].rx() = x2;
					m_LineCoordinate[i].LinePoint[1].ry() = y2;

					m_LineCoordinate[i].bDrawFinish = TRUE;
					break;
				}
			}
		}
		else if (lDrawType == DRAW_PEN_Rectangle)
		{
			for (i = 0; i < DRAW_RECTANGLE_COUNT; i++)
			{
				if (!m_RectangleCoordinate[i].bDrawFinish)
				{
					m_RectanglePrevPoint = event->pos();

					x1 = m_RectangleCoordinate[i].RectanglePoint[0].x();
					y1 = m_RectangleCoordinate[i].RectanglePoint[0].y();
					x2 = m_RectanglePrevPoint.x();
					y2 = m_RectanglePrevPoint.y();

					double  dbX1 = double(x1) * dbWScale;
					x1 = int(dbX1);
					double  dbY1 = double(y1) * dbHScale;
					y1 = int(dbY1);

					double  dbX2 = double(x2) * dbWScale;
					x2 = int(dbX2);
					double  dbY2 = double(y2) * dbHScale;
					y2 = int(dbY2);

					m_RectangleCoordinate[i].RectanglePoint[0].rx() = x1;
					m_RectangleCoordinate[i].RectanglePoint[0].ry() = y1;
					m_RectangleCoordinate[i].RectanglePoint[1].rx() = x2;
					m_RectangleCoordinate[i].RectanglePoint[1].ry() = y2;

					if (!CheckIsIllegal(DRAW_PEN_Rectangle, m_RectangleCoordinate[i].RectanglePoint[0], m_RectangleCoordinate[i].RectanglePoint[1]))
					{
						m_RectangleCoordinate[i].bDrawFinish = TRUE;
					}


					m_bDrawRectangleStart = FALSE;

					break;
				}
			}
		}
	}
}

BOOL AnalyseVideoAreaDlg::CheckIsIllegal(long lDrawType, QPoint ptStart, QPoint ptEnd)
{
	if (lDrawType == DRAW_PEN_Rectangle)	//矩形
	{
		if (ptStart.x() == ptEnd.x() && ptStart.y() == ptEnd.y())
		{
			return TRUE;
		}
		for (int i = 0; i < DRAW_RECTANGLE_COUNT; i++)
		{
			if (m_RectangleCoordinate[i].bDrawFinish)
			{
				QRect rc(m_RectangleCoordinate[i].RectanglePoint[0].x(), m_RectangleCoordinate[i].RectanglePoint[0].y(), m_RectangleCoordinate[i].RectanglePoint[1].x(), m_RectangleCoordinate[i].RectanglePoint[1].y());
				if (rc.contains(ptStart) && rc.contains(ptEnd))
				{
					return TRUE;
				}
			}
		}
	}


	return FALSE;
}
