// LinerParaDlg.cpp : implementation file
//

#include "stdafx.h"
//#include "	\ add additional includes here"
#include "LinerParaDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLinerParaDlg dialog
BITMAPINFO *pBIH1;
HDC T11;int nWidth,nHeight;int nByteWidth,nBits;
unsigned char* m_pTempBits;
void CLinerParaDlg::getmembers(BITMAPINFO *m_pBIH,HDC t1,int m_nWidth,int m_nHeight,int m_nByteWidth,BYTE *m_lpOut)
{
	nWidth = m_nWidth;
	nHeight = m_nHeight;
	nByteWidth = m_nByteWidth;
	nBits = m_nByteWidth/m_nWidth*8;
	lpBits = m_lpOut;
	T11=t1;
	pBIH1=m_pBIH;
}

CLinerParaDlg::CLinerParaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLinerParaDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLinerParaDlg)
	m_fA = 0.0f;
	m_fB = 0.0f;
	//}}AFX_DATA_INIT
}


void CLinerParaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLinerParaDlg)
	DDX_Text(pDX, IDC_EDIT_A, m_fA);
	DDX_Text(pDX, IDC_EDIT_B, m_fB);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLinerParaDlg, CDialog)
	//{{AFX_MSG_MAP(CLinerParaDlg)
	ON_EN_KILLFOCUS(IDC_EDIT_A, OnKillfocusEditA)
	ON_EN_KILLFOCUS(IDC_EDIT_B, OnKillfocusEditB)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLinerParaDlg message handlers

BOOL CLinerParaDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CWnd* pWnd = GetDlgItem(IDC_COORD);	
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
	
	m_bIsDraging = FALSE;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CLinerParaDlg::OnKillfocusEditA() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	InvalidateRect(m_MouseRect, TRUE);
}

void CLinerParaDlg::OnKillfocusEditB() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	InvalidateRect(m_MouseRect, TRUE);
}

void CLinerParaDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	// 当用户单击鼠标左键开始拖动
	if(m_MouseRect.PtInRect(point))
	{
		m_p1 = point;		
		// 转换坐标系
		m_p1.x = m_p1.x - m_MouseRect.left + 10;
		m_p1.y = m_p1.y - m_MouseRect.top + 25;
		
		m_bIsDraging = TRUE;
		m_bDrawed = FALSE;
		::SetCursor(::LoadCursor(NULL, IDC_CROSS));
		
		// 开始跟踪鼠标事件（保证当鼠标移动到窗体外时也可以接收到鼠标释放事件）
		SetCapture();
	}
	CDialog::OnLButtonDown(nFlags, point);
}

void CLinerParaDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	// 当用户释放鼠标左键停止拖动
	if (m_bIsDraging)
	{
		// 判断当前光标是否在绘制区域
		if(m_MouseRect.PtInRect(point))
		{
			m_p2 = point;			
			// 转换坐标系
			m_p2.x = m_p2.x - m_MouseRect.left + 10;
			m_p2.y = m_p2.y - m_MouseRect.top + 25;
			
			if ((m_p1 != m_p2) && (m_p1.x != m_p2.x))
			{
				// 转换坐标系
				m_p1.x = m_p1.x - 10;
				m_p1.y = 280 - m_p1.y;
				m_p2.x = m_p2.x - 10;
				m_p2.y = 280 - m_p2.y;				
				// 计算斜率和截距
				m_fA = (float) (m_p2.y - m_p1.y) / (m_p2.x - m_p1.x);
				m_fB = m_p1.y - m_fA * m_p1.x;
				
				LinerTrans();
                StretchDIBits(T11,0,0,nWidth,nHeight,0,0,nWidth, nHeight,lpOut,pBIH1,DIB_RGB_COLORS,SRCCOPY);
				UpdateData(FALSE);
			}
			
			InvalidateRect(m_MouseRect, TRUE);
		}
		else
		{
			// 用户在绘制区域外放开鼠标左键
			
			CWnd* pWnd = GetDlgItem(IDC_COORD);			// 获取绘图的标签						
			CDC* pDC = pWnd->GetDC();					// 获取设备上下文						
			int nOldDrawMode = pDC->SetROP2(R2_XORPEN);	// 设置绘制方式为异或模式
			
			CPen* pPen = new CPen;
			pPen->CreatePen(PS_DOT,1,RGB(0,0,0));
			CGdiObject* pOldPen = pDC->SelectObject(pPen);
			
			// 判断是否已经画过橡皮筋线
			if (m_bDrawed)
			{
				pDC->MoveTo(m_p1);
				pDC->LineTo(m_p2);
			}
			
			pDC->SelectObject(pOldPen);			// 选回以前的画笔			
			pDC->SetROP2(nOldDrawMode);			// 恢复成以前的绘制模式
			
			delete pPen;
			ReleaseDC(pDC);			
		}		
		
		::ReleaseCapture();						// 解除对鼠标事件的跟踪		
		m_bIsDraging = FALSE;					// 重置拖动状态
		
	}
	CDialog::OnLButtonUp(nFlags, point);
}

void CLinerParaDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	// 判断当前光标是否在绘制区域
	if(m_MouseRect.PtInRect(point))
	{
		::SetCursor(::LoadCursor(NULL, IDC_CROSS));
		
		if (m_bIsDraging)
		{
			CWnd* pWnd = GetDlgItem(IDC_COORD);
			CDC* pDC = pWnd->GetDC();			
			// 设置绘制方式为异或模式
			int nOldDrawMode = pDC->SetROP2(R2_XORPEN);
			
			CPen* pPen = new CPen;
			pPen->CreatePen(PS_DOT,1,RGB(0,0,0));
			CGdiObject* pOldPen = pDC->SelectObject(pPen);
			
			// 判断是否已经画过橡皮筋线
			if (m_bDrawed)
			{
				pDC->MoveTo(m_p1);
				pDC->LineTo(m_p2);
			}
			
			m_p2 = point;		
			
			// 转换坐标系
			m_p2.x = m_p2.x - m_MouseRect.left + 10;
			m_p2.y = m_p2.y - m_MouseRect.top + 25;	
			
			// 绘制一条新橡皮筋线
			pDC->MoveTo(m_p1);
			pDC->LineTo(m_p2);
			
			m_bDrawed = TRUE;			
			pDC->SelectObject(pOldPen);	// 选回以前的画笔		
			pDC->SetROP2(nOldDrawMode);	// 恢复成以前的绘制模式
			
			delete pPen;
			ReleaseDC(pDC);
		}
	}
	else
	{
		if (m_bIsDraging)
		{
			::SetCursor(::LoadCursor(NULL, IDC_NO));
		}
	}
	CDialog::OnMouseMove(nFlags, point);
}

void CLinerParaDlg::OnPaint() 
{
	CString str;	
	int x1, y1, x2, y2;			// 直线和坐标轴二个交点
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
		CWnd* pWnd = GetDlgItem(IDC_COORD);
	CDC* pDC = pWnd->GetDC();
	pWnd->Invalidate();
	pWnd->UpdateWindow();
	pDC->Rectangle(0,0,330,300);
	
	CPen* pPenRed = new CPen;		// 红色画笔
	pPenRed->CreatePen(PS_SOLID,2,RGB(255,0,0));
	CPen* pPenBlue = new CPen;		// 蓝色画笔
	pPenBlue->CreatePen(PS_SOLID,2,RGB(0,0, 255));
	
	// 选中当前红色画笔，并保存以前的画笔
	CGdiObject* pOldPen = pDC->SelectObject(pPenRed);
		
	pDC->MoveTo(10,10);				// 绘制坐标轴	
	pDC->LineTo(10,280);			// 垂直轴	
	pDC->LineTo(320,280);			// 水平轴
	str.Format("0");
	pDC->TextOut(10, 281, str);		// 写坐标	
	str.Format("255");
	pDC->TextOut(265, 281, str);
	pDC->TextOut(11, 25, str);
	
	// 绘制X轴箭头
	pDC->LineTo(315,275);
	pDC->MoveTo(320,280);
	pDC->LineTo(315,285);
	
	// 绘制X轴箭头
	pDC->MoveTo(10,10);
	pDC->LineTo(5,15);
	pDC->MoveTo(10,10);
	pDC->LineTo(15,15);
	
	// 更改成蓝色画笔
	pDC->SelectObject(pPenBlue);	
	
	// 计算直线和坐标轴二个交点坐标
	if (m_fA >= 0)
	{
		if (((m_fA * 255 + m_fB) >= 0) && (m_fB < 255))
		{
			if (m_fB < 0)
			{
				x1 = (int) (- m_fB/m_fA + 0.5);
				y1 = 0;
			}
			else
			{
				x1 = 0;
				y1 = (int) (m_fB + 0.5);
			}
			
			if ((m_fA * 255 + m_fB) > 255)
			{
				x2 = (int) ((255- m_fB)/m_fA + 0.5);
				y2 = 255;
			}
			else
			{
				x2 = 255;
				y2 = (int) (255* m_fA + m_fB + 0.5);
			}
		}
		else if(((m_fA * 255 + m_fB) < 0))
		{
			x1 = 0;
			y1 = 0;
			x2 = 255;
			y2 = 0;
		}
		else
		{
			x1 = 0;
			y1 = 255;
			x2 = 255;
			y2 = 255;
		}
	}
	else  // 斜率小于0
	{
		if ((m_fB > 0) && (255* m_fA + m_fB < 255))
		{
			if (m_fB > 255)
			{
				x1 = (int) ((255- m_fB)/m_fA + 0.5);
				y1 = 255;
			}
			else
			{
				x1 = 0;
				y1 = (int) (m_fB + 0.5);
			}
			
			if ((m_fA * 255 + m_fB) < 0)
			{
				x2 = (int) (- m_fB/m_fA + 0.5);
				y2 = 0;
			}
			else
			{
				x2 = 255;
				y2 = (int) (255* m_fA + m_fB + 0.5);
			}
		}
		else if (m_fB <=0)
		{
			x1 = 0;
			y1 = 0;
			x2 = 255;
			y2 = 0;
		}
		else
		{
			x1 = 0;
			y1 = 255;
			x2 = 255;
			y2 = 255;
		}
	}
	
	// 绘制坐标值
	str.Format("(%d, %d)", x1, y1);
	pDC->TextOut(x1 + 10, 280 - y1 + 1, str);
	str.Format("(%d, %d)", x2, y2);
	pDC->TextOut(x2 + 10, 280 - y2 + 1, str);
	
	// 绘制用户指定的线性变换直线（注意转换坐标系）
	pDC->MoveTo(x1 + 10, 280 - y1);
	pDC->LineTo(x2 + 10, 280 - y2);
	
	// 恢复以前的画笔
	pDC->SelectObject(pOldPen);	
	
	// 绘制边缘
	pDC->MoveTo(10,25);
	pDC->LineTo(265,25);
	pDC->LineTo(265,280);
	
	delete pPenRed;
	delete pPenBlue;
	// Do not call CDialog::OnPaint() for painting messages
}

void CLinerParaDlg::LinerTrans()
{
	//lpOut=lpOut;
	lpOut=new BYTE[nByteWidth*nHeight];
	float fTemp,fTemp1,fTemp2;
	int i,j;

			switch(nBits)
			{
			case 8:	
				for(i = 0; i < nHeight; i++)			// 每行
				{		
					for(j = 0; j < nWidth; j++)			// 每列
					{
						fTemp = m_fA * (lpBits[i*nByteWidth+j]) + m_fB;		// 线性变换
			        	if (fTemp > 255)				// 判断是否超出范围
						{
					 lpOut[i*nByteWidth+j] = 255;
						}
			    	else if (fTemp < 0)
					{
					lpOut[i*nByteWidth+j] = 0;
					}
				else
				{				
					lpOut[i*nByteWidth+j] = (unsigned char) (fTemp + 0.5);	// 四舍五入
				}
				}
				}
				break;
			case 24:
				for(i = 0; i < nHeight; i++)			// 每行
				{		
					for(int j = 0; j < nWidth; j++)			// 每列
		{fTemp = m_fA * (lpBits[i*nByteWidth+3*j]) + m_fB;		// 线性变换
				fTemp1 = m_fA * (lpBits[i*nByteWidth+3*j+1]) + m_fB;
				fTemp2 = m_fA * (lpBits[i*nByteWidth+3*j]+2) + m_fB;
				if (fTemp > 255)				// 判断是否超出范围
				{
					lpOut[i*nByteWidth+3*j] = 255;
				}
				else if (fTemp < 0)
				{
					lpOut[i*nByteWidth+3*j] = 0;
				}
				else 
				{				
					lpOut[i*nByteWidth+3*j] = (unsigned char) (fTemp + 0.5);	// 四舍五入
				}
				 if (fTemp1 > 255)				// 判断是否超出范围
				{
					lpOut[i*nByteWidth+3*j+1] = 255;
				}
				else if (fTemp1 < 0)
				{
					lpOut[i*nByteWidth+3*j+1] = 0;
				}
				else 
				{				
					lpOut[i*nByteWidth+3*j+1] = (unsigned char) (fTemp + 0.5);	// 四舍五入
				}
				 if (fTemp2 > 255)				// 判断是否超出范围
				{
					lpOut[i*nByteWidth+j*3+2] = 255;
				}
				else if (fTemp2 < 0)
				{
					lpOut[i*nByteWidth+3*j+2] = 0;
				}
				else
				{				
					lpOut[i*nByteWidth+3*j+2] = (unsigned char) (fTemp + 0.5);	// 四舍五入
				}

			}

		}
				break;
	}
}
