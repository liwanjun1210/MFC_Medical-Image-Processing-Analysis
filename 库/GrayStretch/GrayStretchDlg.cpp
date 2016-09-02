// GrayStretchDlg.cpp : implementation file
//

#include "stdafx.h"
//#include "	\ add additional includes here"
#include "GrayStretchDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGrayStretchDlg dialog

int m_nPointY2,m_nPointX2,m_nPointY1,m_nPointX1;
int m_IsDragingFlag;
CRect m_MouseRect;

BITMAPINFO *pBIH;
HDC T1;
void CGrayStretchDlg::getmembers(BITMAPINFO *m_pBIH,HDC t1,int m_nWidth,int m_nHeight,int m_nByteWidth,BYTE *m_lpOut)
{
	nWidth = m_nWidth;
	nHeight = m_nHeight;
	nByteWidth = m_nByteWidth;
	nBits = m_nByteWidth/m_nWidth*8;
	lpBits = m_lpOut;
    lpOut = m_lpOut;
	T1=t1;
	pBIH=m_pBIH;
}

CGrayStretchDlg::CGrayStretchDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CGrayStretchDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGrayStretchDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_nPointX1 = 50;
	m_nPointY1 = 50;
	m_nPointX2 = 200;
	m_nPointY2 = 200;
}


void CGrayStretchDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGrayStretchDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGrayStretchDlg, CDialog)
	//{{AFX_MSG_MAP(CGrayStretchDlg)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGrayStretchDlg message handlers

BOOL CGrayStretchDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CWnd* pWnd = GetDlgItem(IDC_COORD);
	
	// 计算接受鼠标事件的有效区域
	pWnd->GetClientRect(m_MouseRect);
	pWnd->ClientToScreen(&m_MouseRect);
	
	CRect rect;
	GetClientRect(rect);  
	ClientToScreen(&rect);
	
	m_MouseRect.top -= rect.top;
	m_MouseRect.left -= rect.left;
	
	// 设置接受鼠标事件的有效区域
	m_MouseRect.top += 25;
	m_MouseRect.left += 10;
	m_MouseRect.bottom = m_MouseRect.top + 255;
	m_MouseRect.right = m_MouseRect.left + 256;
	
	// 初始化拖动状态
	m_IsDragingFlag = 0;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CGrayStretchDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_MouseRect.PtInRect(point)) //Point in rectangle?
	{
		CRect rectTemp;
		
		// 计算点1临近区域
		rectTemp.left = m_MouseRect.left + m_nPointX1 - 2;
		rectTemp.right = m_MouseRect.left + m_nPointX1 + 2;
		rectTemp.top = 255 + m_MouseRect.top - m_nPointY1 - 2;
		rectTemp.bottom = 255 + m_MouseRect.top - m_nPointY1 + 2;
		
		// 判断用户是不是想拖动点1
		if (rectTemp.PtInRect(point))
		{
			
			// 设置拖动状态1，拖动点1
			m_IsDragingFlag = 1;
			
			// 更改光标
			::SetCursor(::LoadCursor(NULL, IDC_SIZEALL));
		}
		else
		{
			// 计算点2临近区域
			rectTemp.left = m_MouseRect.left + m_nPointX2 - 2;
			rectTemp.right = m_MouseRect.left + m_nPointX2 + 2;
			rectTemp.top = 255 + m_MouseRect.top - m_nPointY2 - 2;
			rectTemp.bottom = 255 + m_MouseRect.top - m_nPointY2 + 2;
			
			// 判断用户是不是想拖动点2
			if (rectTemp.PtInRect(point))
			{
				
				// 设置拖动状态为2，拖动点2
				m_IsDragingFlag = 2;
				
				// 更改光标
				::SetCursor(::LoadCursor(NULL, IDC_SIZEALL));
			}
		}
	}
	CDialog::OnLButtonDown(nFlags, point);
}

void CGrayStretchDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_IsDragingFlag != 0)
	{
		m_IsDragingFlag = 0;
		GrayStrentch();
		StretchDIBits(T1,0,0,nWidth,nHeight,0,0,nWidth, nHeight,lpOut,pBIH,DIB_RGB_COLORS,SRCCOPY);
	}
	CDialog::OnLButtonUp(nFlags, point);
}

void CGrayStretchDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if(m_MouseRect.PtInRect(point))		//当前光标在绘制区域
	{
		// 判断是否正在拖动
		if (m_IsDragingFlag != 0)
		{
			// 判断正在拖动点1还是点2
			if (m_IsDragingFlag == 1)
			{
				// 判断是否下限<上限
				if (point.x - m_MouseRect.left < m_nPointX2)
				{
					// 更改下限
					m_nPointX1 = point.x - m_MouseRect.left;
				}
				else
				{
					// 下限拖过上限，设置为上限-1
					m_nPointX1 = m_nPointX2 - 1;
					
					// 重设鼠标位置
					point.x = m_MouseRect.left + m_nPointX2 - 1;
				}
				
				// 更改Y坐标
				m_nPointY1 = 255 + m_MouseRect.top - point.y;
			}
			else
			{
				// 正在拖动点2
				
				// 判断是否上限>下限
				if (point.x - m_MouseRect.left > m_nPointX1)
				{
					// 更改下限
					m_nPointX2 = point.x - m_MouseRect.left;
				}
				else
				{
					// 下限拖过上限，设置为下限＋1
					m_nPointX2 = m_nPointX1 + 1;
					
					// 重设鼠标位置
					point.x = m_MouseRect.left + m_nPointX1 + 1;
				}
				
				// 更改Y坐标
				m_nPointY2 = 255 + m_MouseRect.top - point.y;
			}
			
			// 更改光标
			::SetCursor(::LoadCursor(NULL, IDC_SIZEALL));
			
			// 更新
			UpdateData(FALSE);
			
			// 重绘
			InvalidateRect(m_MouseRect, TRUE);
		}
		else
		{
			CRect	rectTemp1;
			CRect	rectTemp2;
			
			// 计算点1临近区域
			rectTemp1.left = m_MouseRect.left + m_nPointX1 - 2;
			rectTemp1.right = m_MouseRect.left + m_nPointX1 + 2;
			rectTemp1.top = 255 + m_MouseRect.top - m_nPointY1 - 2;
			rectTemp1.bottom = 255 + m_MouseRect.top - m_nPointY1 + 2;
			
			// 计算点2临近区域
			rectTemp2.left = m_MouseRect.left + m_nPointX2 - 2;
			rectTemp2.right = m_MouseRect.left + m_nPointX2 + 2;
			rectTemp2.top = 255 + m_MouseRect.top - m_nPointY2 - 2;
			rectTemp2.bottom = 255 + m_MouseRect.top - m_nPointY2 + 2;
			
			// 判断用户在点1或点2旁边
			if ((rectTemp1.PtInRect(point)) || (rectTemp2.PtInRect(point)))
			{
				// 更改光标
				::SetCursor(::LoadCursor(NULL, IDC_SIZEALL));
			}
		}
}
	CDialog::OnMouseMove(nFlags, point);
}

void CGrayStretchDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CWnd* pWnd = GetDlgItem(IDC_COORD);
	CDC* pDC = pWnd->GetDC();
	
	pWnd->Invalidate();
	pWnd->UpdateWindow();
	
	pDC->Rectangle(0,0,330,300);
	
	//创建笔画对象
	CPen* pPenRed = new CPen;	//红笔
	pPenRed->CreatePen(PS_SOLID,2,RGB(255,0,0));
	CPen* pPenBlue = new CPen;	//蓝笔
	pPenBlue->CreatePen(PS_SOLID,1,RGB(0,0,255));
	CPen* pPenGreen = new CPen;	//绿笔
	pPenGreen->CreatePen(PS_DOT,1,RGB(0,255,0));
	
	// 选中当前红色画笔，并保存以前的画笔
	CGdiObject* pOldPen = pDC->SelectObject(pPenRed);
	
	// 绘制坐标轴
	pDC->MoveTo(10,10);
	pDC->LineTo(10,280);
	pDC->LineTo(320,280);
	
	CString str;
	// 写坐标
	str.Format("0");
	pDC->TextOut(10, 281, str);
	str.Format("255");
	pDC->TextOut(265, 281, str);
	pDC->TextOut(11, 25, str);
	
	// 绘制X轴箭头
	pDC->LineTo(315,275);
	pDC->MoveTo(320,280);
	pDC->LineTo(315,285);
	pDC->MoveTo(10,10);
	pDC->LineTo(5,15);
	pDC->MoveTo(10,10);
	pDC->LineTo(15,15);
	
	// 更改成蓝色画笔
	pDC->SelectObject(pPenBlue);	
	
	// 绘制坐标值
	str.Format("(%d, %d)", m_nPointX1, m_nPointY1);
	pDC->TextOut(m_nPointX1 + 10, 281 - m_nPointY1, str);
	str.Format("(%d, %d)", m_nPointX2, m_nPointY2);
	pDC->TextOut(m_nPointX2 + 10, 281 - m_nPointY2, str);
	
	// 绘制用户指定的变换直线
	pDC->MoveTo(10, 280);
	pDC->LineTo(m_nPointX1 + 10, 280 - m_nPointY1);
	pDC->LineTo(m_nPointX2 + 10, 280 - m_nPointY2);
	pDC->LineTo(265, 25);
	
	// 绘制点边缘的小矩形
	CBrush  brush;
	brush.CreateSolidBrush(RGB(0,255,0));
	
	// 选中刷子
	CGdiObject* pOldBrush = pDC->SelectObject(&brush);
	
	// 绘制小矩形
	pDC->Rectangle(m_nPointX1 + 10 - 2, 280 - m_nPointY1 - 2, m_nPointX1 + 12, 280 - m_nPointY1 + 2);
	pDC->Rectangle(m_nPointX2 + 10 - 2, 280 - m_nPointY2 - 2, m_nPointX2 + 12, 280 - m_nPointY2 + 2);
	
	// 恢复以前的画笔
	pDC->SelectObject(pOldPen);	
	
	// 绘制边缘
	pDC->MoveTo(10,25);
	pDC->LineTo(265,25);
	pDC->LineTo(265,280);
	
	// 删除新的画笔
	delete pPenRed;
	delete pPenBlue;
	delete pPenGreen;
	// Do not call CDialog::OnPaint() for painting messages
}
BOOL CGrayStretchDlg::GrayStrentch()
{
	lpOut=new BYTE[nByteWidth*nHeight];
	int i,j;
	
	int nMap[256];
	for (i = 0; i <= m_nPointX1; i++)
	{
		if (m_nPointX1 > 0)
			nMap[i] = m_nPointY1*i/m_nPointX1;
		else
			nMap[i] = 0;
	}
	for ( ; i<=m_nPointX2; i++)
	{
		if (m_nPointX2 != m_nPointX1)
			nMap[i] = m_nPointY1 + (m_nPointY2 - m_nPointY1)*(i - m_nPointX1)/(m_nPointX2 - m_nPointX1);
		else
			nMap[i] = m_nPointY1;
	}
	for ( ; i < 256; i++)
	{
		if(m_nPointX2 != 255)
			nMap[i] = m_nPointY2 + (255 - m_nPointY2)*(i - m_nPointX2)/(255 - m_nPointX2);
		else
			nMap[i] = 255;
	}
	
	for (i = 0; i < nHeight; i++)
	{
		for (j = 0; j < nWidth; j++)
		{
				lpOut[(nHeight-1-i)*nByteWidth+j]=nMap[lpBits[(nHeight-1-i)*nByteWidth+j]];
	
		}
	}	
	
	return TRUE;
}
