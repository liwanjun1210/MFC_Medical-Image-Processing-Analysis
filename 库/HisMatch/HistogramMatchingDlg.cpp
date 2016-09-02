// HistogramMatchingDlg.cpp : implementation file
//

#include "stdafx.h"
//#include "	\ add additional includes here"
#include "HistogramMatchingDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHistogramMatchingDlg dialog

BYTE *lpBits;
int nByteWidth,nHeight,nWidth,m_nBits,Flag,nBits;
HDC T1;BITMAPINFO *pBIH;
void CHistogramMatchingDlg::getmembers(BITMAPINFO *m_pBIH,HDC t1,int m_nWidth,int m_nHeight,int m_nByteWidth,BYTE *m_lpOut)
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
CHistogramMatchingDlg::CHistogramMatchingDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHistogramMatchingDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHistogramMatchingDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_Point1.x = 60;
	m_Point1.y = 200;
	m_Point2.x = 120;
	m_Point2.y = 50;
	m_Point3.x = 190;
	m_Point3.y = 200;
}


void CHistogramMatchingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHistogramMatchingDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHistogramMatchingDlg, CDialog)
	//{{AFX_MSG_MAP(CHistogramMatchingDlg)
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHistogramMatchingDlg message handlers

BOOL CHistogramMatchingDlg::OnInitDialog() 
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
	
	// 设置接受鼠标事件的有效区域，这个有效区要注意与OnPaint函数中的坐标区吻合！！
	m_MouseRect.top += 25;
	m_MouseRect.left += 10;
	m_MouseRect.bottom = m_MouseRect.top + 255;
	m_MouseRect.right = m_MouseRect.left + 256;
	
	// 初始化拖动状态
	m_IsDragingFlag = 0;

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CHistogramMatchingDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	// 当用户单击鼠标左键开始拖动
	if(m_MouseRect.PtInRect(point)) //Point in rectangle?
	{
		CRect rectTemp;
		
		// 计算点1临近区域
		rectTemp.left = m_MouseRect.left + m_Point1.x - 2;
		rectTemp.right = m_MouseRect.left + m_Point1.x + 2;
		rectTemp.top = 255 + m_MouseRect.top - m_Point1.y - 2;
		rectTemp.bottom = 255 + m_MouseRect.top - m_Point1.y + 2;
		
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
			rectTemp.left = m_MouseRect.left + m_Point2.x - 2;
			rectTemp.right = m_MouseRect.left + m_Point2.x + 2;
			rectTemp.top = 255 + m_MouseRect.top - m_Point2.y - 2;
			rectTemp.bottom = 255 + m_MouseRect.top - m_Point2.y + 2;
			
			// 判断用户是不是想拖动点2
			if (rectTemp.PtInRect(point))
			{
				
				// 设置拖动状态为2，拖动点2
				m_IsDragingFlag = 2;
				
				// 更改光标
				::SetCursor(::LoadCursor(NULL, IDC_SIZEALL));
			}
			else
			{
				// 计算点3临近区域
				rectTemp.left = m_MouseRect.left + m_Point3.x - 2;
				rectTemp.right = m_MouseRect.left + m_Point3.x + 2;
				rectTemp.top = 255 + m_MouseRect.top - m_Point3.y - 2;
				rectTemp.bottom = 255 + m_MouseRect.top - m_Point3.y + 2;
				
				// 判断用户是不是想拖动点3
				if (rectTemp.PtInRect(point))
				{
					
					// 设置拖动状态为2，拖动点3
					m_IsDragingFlag = 3;
					
					// 更改光标
					::SetCursor(::LoadCursor(NULL, IDC_SIZEALL));
				}
			}
		}
	}
	CDialog::OnLButtonDown(nFlags, point);
}

void CHistogramMatchingDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	if (m_IsDragingFlag != 0)
	{
		m_IsDragingFlag = 0;
		HistogramMatching(m_Point1,m_Point2,m_Point3);
		StretchDIBits(T1,0,0,nWidth,nHeight,0,0,nWidth, nHeight,lpOut,pBIH,DIB_RGB_COLORS,SRCCOPY);
	}

	CDialog::OnLButtonUp(nFlags, point);
}

void CHistogramMatchingDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
		if(m_MouseRect.PtInRect(point))		//当前光标在绘制区域
	{
		// 判断是否正在拖动
		if (m_IsDragingFlag != 0)
		{
			// 判断正在拖动点1还是点2还是点3
			if (m_IsDragingFlag == 1)
			{
				// 判断鼠标拖动的点1是否在点2左边
				if (point.x - m_MouseRect.left < m_Point2.x)
				{
					// 更改下限
					m_Point1.x = point.x - m_MouseRect.left;
				}
				else
				{
					// 点1拖过点2下限，设置为点2下限-1
					m_Point1.x = m_Point2.x - 1;
					
					// 重设鼠标位置
					point.x = m_MouseRect.left + m_Point2.x - 1;
				}
				
				// 更改Y坐标
				m_Point1.y = 255 + m_MouseRect.top - point.y;
			}
			else if (m_IsDragingFlag == 2)
			{
				// 正在拖动点2
				
				//判断鼠标拖动的点2是否在点1与点3之间
				if (point.x - m_MouseRect.left > m_Point1.x && point.x - m_MouseRect.left < m_Point3.x)
				{
					// 更改下限
					m_Point2.x = point.x - m_MouseRect.left;
				}
				else if(point.x - m_MouseRect.left <= m_Point1.x)
				{
					// 点2拖过点1的上限，点2设置为点1的上限＋1
					m_Point2.x = m_Point1.x + 1;
					
					// 重设鼠标位置
					point.x = m_MouseRect.left + m_Point1.x + 1;
				}
				else
				{
					// 点2拖过点3的下限，点2设置为点3的下限-1
					m_Point2.x = m_Point3.x - 1;
					
					// 重设鼠标位置
					point.x = m_MouseRect.left + m_Point3.x - 1;
				}
				
				// 更改Y坐标
				m_Point2.y = 255 + m_MouseRect.top - point.y;
			}
			else
			{
				//正在拖动点3
				
				//判断鼠标拖动的点3是否在点2右边
				if (point.x - m_MouseRect.left > m_Point2.x)
				{
					// 更改下限
					m_Point3.x = point.x - m_MouseRect.left;
				}
				else
				{
					// 点3拖过点2的上限，点3设置为点2的上限+1
					m_Point3.x = m_Point2.x + 1;
					
					// 重设鼠标位置
					point.x = m_MouseRect.left + m_Point2.x + 1;
				}
				
				// 更改Y坐标
				m_Point3.y = 255 + m_MouseRect.top - point.y;
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
			CRect   rectTemp3;
			
			// 计算点1临近区域
			rectTemp1.left = m_MouseRect.left + m_Point1.x - 2;
			rectTemp1.right = m_MouseRect.left + m_Point1.x + 2;
			rectTemp1.top = 255 + m_MouseRect.top - m_Point1.y - 2;
			rectTemp1.bottom = 255 + m_MouseRect.top - m_Point1.y + 2;
			
			// 计算点2临近区域
			rectTemp2.left = m_MouseRect.left + m_Point2.x - 2;
			rectTemp2.right = m_MouseRect.left + m_Point2.x + 2;
			rectTemp2.top = 255 + m_MouseRect.top - m_Point2.y - 2;
			rectTemp2.bottom = 255 + m_MouseRect.top - m_Point2.y + 2;

			// 计算点3临近区域
			rectTemp3.left = m_MouseRect.left + m_Point3.x - 2;
			rectTemp3.right = m_MouseRect.left + m_Point3.x + 2;
			rectTemp3.top = 255 + m_MouseRect.top - m_Point3.y - 2;
			rectTemp3.bottom = 255 + m_MouseRect.top - m_Point3.y + 2;
			
			// 判断用户在点1或点2或点3旁边
			if ((rectTemp1.PtInRect(point)) || (rectTemp2.PtInRect(point)) || (rectTemp3.PtInRect(point)))
			{
				// 更改光标
				::SetCursor(::LoadCursor(NULL, IDC_SIZEALL));
			}
		}
	}
	CDialog::OnMouseMove(nFlags, point);
}

void CHistogramMatchingDlg::OnPaint() 
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
	str.Format("(%d, %d)", m_Point1.x, m_Point1.y);
	pDC->TextOut(m_Point1.x + 10, 281 - m_Point1.y, str);
	str.Format("(%d, %d)", m_Point2.x, m_Point2.y);
	pDC->TextOut(m_Point2.x + 10, 281 - m_Point2.y, str);
	str.Format("(%d, %d)", m_Point3.x, m_Point3.y);
	pDC->TextOut(m_Point3.x + 10, 281 - m_Point3.y, str);
	
	// 绘制用户指定的变换直线
	pDC->MoveTo(10, 280);
	pDC->LineTo(m_Point1.x + 10, 280 - m_Point1.y);
	pDC->LineTo(m_Point2.x + 10, 280 - m_Point2.y);
	pDC->LineTo(m_Point3.x + 10, 280 - m_Point3.y);
	pDC->LineTo(265, 280);
	
	// 绘制点边缘的小矩形
	CBrush  brush;
	brush.CreateSolidBrush(RGB(0,255,0));
	
	// 选中刷子
	CGdiObject* pOldBrush = pDC->SelectObject(&brush);
	
	// 绘制小矩形
	pDC->Rectangle(m_Point1.x + 10 - 2, 280 - m_Point1.y - 2, m_Point1.x + 12, 280 - m_Point1.y + 2);
	pDC->Rectangle(m_Point2.x + 10 - 2, 280 - m_Point2.y - 2, m_Point2.x + 12, 280 - m_Point2.y + 2);
	pDC->Rectangle(m_Point3.x + 10 - 2, 280 - m_Point3.y - 2, m_Point3.x + 12, 280 - m_Point3.y + 2);
	
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
BOOL CHistogramMatchingDlg::HistogramMatching(CPoint point1, CPoint point2, CPoint point3)
{
	//**********分配内存************
	lpOut=new BYTE[nByteWidth*nHeight];
	int nSize = 1<<nBits;
	int k = 0;
	long * plOldGrayNum = NULL;
	BYTE* pbOldGrayMap = NULL;	//待处理图像到均衡化的灰度映射表

	BYTE* pbDigitizedFunction = NULL;	//将规定化函数数字化,即保存规定化函数

	BYTE* pbNewGrayMap = NULL;	//将规定灰度直方图进行均衡化的映射表

	BYTE* pbFinalMap = NULL;	//最终我们求的从源图像到规定直方图的映射表
	
	switch (nBits)
	{
		case 8:
			//根据图像的位数分配相应的内存
			plOldGrayNum = new long[nSize];
			pbOldGrayMap = new BYTE[nSize];
			pbDigitizedFunction = new BYTE[nSize];
			pbNewGrayMap = new BYTE[nSize];
			pbFinalMap = new BYTE[nSize];
			
			if ((plOldGrayNum == NULL)||(pbOldGrayMap == NULL)||(pbNewGrayMap == NULL)||(pbDigitizedFunction == NULL)||(pbFinalMap == NULL))
				return FALSE;

			//清零
			for(k=0; k<nSize; k++) 
			{
				plOldGrayNum[k] = 0;
				pbOldGrayMap[k] = 0;
				pbDigitizedFunction[k] = 0;
				pbNewGrayMap[k] = 0;
				pbFinalMap[k] = 0;
			}
			break;
		case 16:
			break;
		case 24:
			break;
		default:
			break;
	}
	
	int i,j;
	//**********处理原始图像，即计算其均衡化的映射表***********	
	for (j=0; j<nHeight; j++)	//计算各灰度值有多少个像素点。
	{
		for (i=0; i<nWidth; i++)
		{
			plOldGrayNum[lpBits[(nHeight-1-j)*nByteWidth+i]]++;
					// 注意取图像中（i,j）点像素的方式！！！
		}
	}
	long lTempVar;
	for (i = 0; i < nSize; i++)
	{
		lTempVar = 0;
		for (j = 0; j <= i; j++)
		{
			lTempVar += plOldGrayNum[j];	//计算累加
		}
		pbOldGrayMap[i] = (BYTE)(lTempVar*(nSize-1)/nHeight/nWidth);	//映射图(递增)
	}


	//**********将规定的函数数字化（如果规定化函数改变了，主要对这个地方做处理！！）***********
	for (i = 0; i <= point1.x; i++)
	{
		// 判断point1.x是否大于0（防止分母为0）
		if (point1.x > 0)
			pbDigitizedFunction[i] = (BYTE)(point1.y*i/point1.x);
		else
			pbDigitizedFunction[i] = (BYTE)point1.y;
	}
	for (; i <= point2.x; i++)
	{
		if (point2.x != point1.x)
			pbDigitizedFunction[i] = (BYTE)(point1.y + (point2.y-point1.y) * (i-point1.x) / (point2.x-point1.x));
		else
			pbDigitizedFunction[i] = (BYTE)point1.y;
	}
	for (; i <= point3.x; i++)
	{
		if (point3.x != point2.x)
			pbDigitizedFunction[i] = (BYTE)(point2.y + (point3.y-point2.y) * (i-point2.x) / (point3.x-point2.x));
		else
			pbDigitizedFunction[i] = (BYTE)point2.y;
	}
	for (; i < 256; i++)
	{
		// 判断bX2是否等于255（防止分母为0）
		if (point3.x != 255)
			pbDigitizedFunction[i] = (BYTE)(point3.y + (-point3.y) * (i-point3.x) / (255-point3.x));
		else
			pbDigitizedFunction[i] = (BYTE)point3.y;
	}

	//计算对规定函数进行直方图均衡化需要的映射表
	long lTotalTemp = 0;
	for (i = 0; i < 256; i++)
	{
		lTotalTemp += pbDigitizedFunction[i];
	}
	for (i = 0; i < 256; i++)
	{
		lTempVar = 0;	//前面有定义的一个临时变量
		for (j = 0; j <= i; j++)
		{
			lTempVar += pbDigitizedFunction[j];
		}
		pbNewGrayMap[i] = (BYTE)(lTempVar * 255 * 1.0 / lTotalTemp);	//递增
	}


	//**********利用枚举迭代的方法确定原图像与规格化函数之间的映射关系******
	float min_value;	//最小差值
	float now_value;	//当前差值
	int IndexTemp = 0;	//下标临时值
	for (i = 0; i < 256; i++)
	{
		min_value = 1.0;
		for (j = 0; j < 256; j++)	//枚举迭代，其实该算法有其他方法可以改进，这里比较的次数太多
		{
			now_value = 0;
			if (pbOldGrayMap[i] - pbNewGrayMap[j] >= now_value)
				now_value = (float)pbOldGrayMap[i] - pbNewGrayMap[j];
			else
				now_value = (float)pbNewGrayMap[j] - pbOldGrayMap[i];
			if (now_value < min_value)
			{
				IndexTemp = j;
				min_value = now_value;
			}
		}
		pbFinalMap[i] = IndexTemp;
	}
	for (j=0; j<nHeight; j++)	//通过映射表对图像进行处理
	{
		for (i=0; i<nWidth; i++)
			lpOut[(nHeight-1-i)*nWidth+j] = pbFinalMap[lpBits[(nHeight-1-i)*nWidth+j]];
	}

	delete[] plOldGrayNum;	//回收分配的一组对象的内存空间
	delete[] pbOldGrayMap;
	delete[] pbDigitizedFunction;
	delete[] pbNewGrayMap;
	delete[] pbFinalMap;
	plOldGrayNum = NULL;
	pbOldGrayMap = NULL;
	pbDigitizedFunction = NULL;
	pbNewGrayMap = NULL;
	pbFinalMap = NULL;

	return TRUE;
}
