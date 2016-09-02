// Threshold.cpp : implementation file
//

#include "stdafx.h"
//#include "	\ add additional includes here"
#include "Threshold.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CThreshold dialog


BYTE *lpBits;HDC T1;BITMAPINFO *pBIH;
int nByteWidth,nHeight,m_Color,nWidth,m_nBits;
void CThreshold::getmember(BITMAPINFO *m_pBIH,HDC t1,int m_nWidth,int m_nHeight,int m_nByteWidth,BYTE *m_lpBits,BYTE *m_lpOut)
{
	nWidth = m_nWidth;
	nHeight = m_nHeight;
	nByteWidth = m_nByteWidth;
	lpBits = m_lpBits;
	lpOut = m_lpOut;
	m_Color = m_nByteWidth/nWidth;
	pBIH=m_pBIH;
	T1=t1;
}
CThreshold::CThreshold(CWnd* pParent /*=NULL*/)
	: CDialog(CThreshold::IDD, pParent)
	, m_Threshold(128)
{
	//{{AFX_DATA_INIT(CThreshold)
	//}}AFX_DATA_INIT
}


void CThreshold::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CThreshold)
	DDX_Control(pDX, IDC_COMBO_THSHOLD, m_Method);
	DDX_Text(pDX, IDC_EDIT_Threshold, m_Threshold);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CThreshold, CDialog)
	//{{AFX_MSG_MAP(CThreshold)
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CThreshold message handlers
int CThreshold::GetThreshold()
{
	return m_Threshold;
}
void CThreshold::RGB2Gray()
{
	if(m_Color == 3)
	{
		for(int i=0;i<nHeight;i++)
		{
			for(int j=0;j<nWidth;j++)
			{
				lpOut[i*nWidth*3+3*j+2] = min(255,max(0,0.299*lpBits[i*nWidth*3+3*j+2]+0.587*lpBits[i*nWidth*3+3*j+1]+0.114*lpBits[i*nWidth*3+3*j]));	
				lpOut[i*nWidth*3+3*j+1] = min(255,max(0,0.299*lpBits[i*nWidth*3+3*j+2]+0.587*lpBits[i*nWidth*3+3*j+1]+0.114*lpBits[i*nWidth*3+3*j]));
				lpOut[i*nWidth*3+3*j] = min(255,max(0,0.299*lpBits[i*nWidth*3+3*j+2]+0.587*lpBits[i*nWidth*3+3*j+1]+0.114*lpBits[i*nWidth*3+3*j]));
				
			}
		}
	}
}
void CThreshold::ThresholdProcess(int Threshold)
{
	lpOut = new BYTE [nByteWidth*nHeight];
	if(m_Color == 3)
	{
       RGB2Gray();
	}
	else
		for(int i=0;i<nByteWidth*nHeight;i++)
		{
			lpOut[i]=lpBits[i];
		}

	for(int k=0;k<nByteWidth*nHeight;k++)
	{
			lpOut[k]>=Threshold?lpOut[k]=255:lpOut[k]=0;//大于等于阈值就是255，否则就是0
	}
}
int CThreshold::OtsuThreshold()//大津法求阈值
{
	lpOut = new BYTE [nByteWidth*nHeight];
	if(m_Color == 3)
	{
	RGB2Gray();
	}//先将图片转换为灰度图
	else
		for(int i=0;i<nByteWidth*nHeight;i++)
		{
			lpOut[i]=lpBits[i];
		}
	
	double p[256],u=0,w0=0,w1=0,u0=0,u1=0,g=0,gtmp,Threshold;
	int i,j;
	long HistogramMax=nHeight*nWidth;
	
	if(!m_pfDistr)
	{
		GetHistogram();
	}//获得直方图
	
	for(i=0;i<256;i++)//接下来就是按照大津法的算法计算了
	{
		p[i]=double(m_pfDistr[i])/HistogramMax;
	}
	for(i=0;i<256;i++)
	{
		u+=i*p[i];
	}
	
	for(i=0;i<256;i++)
	{
		w0=0;
		for(j=0;j<=i;j++)
		{
			w0+=p[j];
		}
		w1=0;
		for(j=i+1;j<256;j++)
		{
			w1+=p[j];
		}
		
		u0=0;
		if(w0!=0)
		{
			for(j=0;j<=i;j++)
			{
				u0+=j*p[j]/w0;
			}
		}
		u1=0;
		if(w1!=0)
		{
			for(j=i+1;j<256;j++)
			{
				u1+=j*p[j]/w1;
			}
		}
		
		gtmp=w0*(u0-u)*(u0-u)+w1*(u1-u)*(u1-u);
		if(g<gtmp)
		{
			g=gtmp;
			Threshold=i;
		}
	}
	return Threshold;//最后返回得到的阈值
}
void CThreshold::GetHistogram()//计算图片的直方图，非归一化直方图
{
	int nSize = 1<<(m_Color*8);
	long* plCount = NULL;
	plCount = new long[nSize];
	m_pfDistr = new float[nSize];
	int x,y,k;
	for(k=0; k<nSize; k++) 
	{
		plCount[k] = 0;
		m_pfDistr[k] = 0;
	}
	switch(m_Color)
	{
	case 1:	for(y=0;y<nHeight;y++)				
			{
				for(x=0;x<nWidth;x++)
				{
					plCount[lpBits[(nHeight-1-y)*nByteWidth+x]]++;
				}
			}
		break;
	case 3: 
		  RGB2Gray();
		  for(y=0;y<nHeight;y++)				
		   {
			   for(x=0;x<nWidth;x++)
			   {
				   plCount[lpOut[(nHeight-1-y)*nByteWidth+3*x]]++;
			   }
			}
		  break;

	}
	long lTotalCount = (long)nHeight*nWidth;
	for (k=0;k<nSize;k++)
	{
		
		m_pfDistr[k] = plCount[k]/(float)lTotalCount;
		
	}
	
	delete[] plCount;	//回收分配的一组对象的内存空间
	plCount = NULL;
}
RECT rect;
void CThreshold::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	// 获取绘制坐标的文本框
	CWnd* pWnd = GetDlgItem(IDC_COORD);
	CDC* pDC = pWnd->GetDC();
	pWnd->Invalidate();
	pWnd->UpdateWindow();
	pWnd->GetClientRect(&rect);
	pDC->Rectangle(rect.left,rect.top,rect.right,rect.bottom);	//画矩形
	int rcWidth = rect.right-rect.left;
	int rcHeight = rect.bottom-rect.top;
	
	//创建笔画对象
	CPen* pPenRed = new CPen;	//红笔
	pPenRed->CreatePen(PS_SOLID,1,RGB(255,0,0));
	CPen* pPenBlue = new CPen;	//蓝笔
	pPenBlue->CreatePen(PS_SOLID,1,RGB(0,0,255));
	CPen* pPenGreen = new CPen;	//绿笔
	pPenGreen->CreatePen(PS_DOT,1,RGB(0,255,0));

	//选中当前红色画笔，并保存以前的画笔
	CGdiObject* pOldPen = pDC->SelectObject(pPenRed);
	
	//绘制坐标轴
	pDC->MoveTo(15,15);
	pDC->LineTo(15,rcHeight-15);
	pDC->LineTo(rcWidth-15,rcHeight-15);
	
	//绘制纵轴箭头
	pDC->MoveTo(15,15);
	pDC->LineTo(15,5);
	pDC->LineTo(13,10);
	pDC->MoveTo(15,5);
	pDC->LineTo(17,10);
	
	//绘制横向箭头
	pDC->MoveTo(rcWidth-15,rcHeight-15);
	pDC->LineTo(rcWidth-5,rcHeight-15);
	pDC->LineTo(rcWidth-10,rcHeight-13);
	pDC->MoveTo(rcWidth-5,rcHeight-15);
	pDC->LineTo(rcWidth-10,rcHeight-17);
	
	//写X轴刻度值
	pDC->SetBkMode(TRANSPARENT);
	CString str = _T("");
	str.Format("0");
	pDC->TextOut(5,rcHeight-17,str);
	str.Format("Gray level");
	pDC->TextOut((int)(rcWidth/2-20),rcHeight-15,str);
	pDC->MoveTo(rcWidth-15,rcHeight-15);
	pDC->LineTo(rcWidth-15,rcHeight-20);
	str.Format("255");
	pDC->TextOut(rcWidth-25,rcHeight-15,str);
	
	//计算最大概率密度值
	float fMaxDistr = 0;
	for (int i=0; i<256; i++)
	{
		//判断是否大于当前最大值
		if (m_pfDistr[i] > fMaxDistr)
		{
			fMaxDistr = m_pfDistr[i];
		}
	}
	
	//写Y轴刻度
	pDC->MoveTo(15,15);
    pDC->LineTo(20,15);
	str.Format("%f",fMaxDistr);
	pDC->TextOut(20,8,str);
	
	//恢复以前的画笔
	pDC->SelectObject(pOldPen);
	
	//绘制直方图
	for (i=0; i<256; i++)
	{
		pDC->MoveTo((int)((rcWidth-30)/255.0*i)+15,rcHeight-15);
		pDC->LineTo((int)((rcWidth-30)/255.0*i)+15,rcHeight-15-(int)(m_pfDistr[i]/fMaxDistr*(rcHeight-30)));		
	}
	
	//删除画笔
	delete pPenRed;
	delete pPenBlue;
	delete pPenGreen;
	// Do not call CDialog::OnPaint() for painting messages
}
void CThreshold::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CWnd* pWnd = GetDlgItem(IDC_COORD);
	CRect rect1;
	rect1.SetRect(rect.left,rect.bottom,rect.right,rect.top);
	int nIndex = m_Method.GetCurSel();
	if(nIndex==0&&nFlags&VK_LBUTTON&&PtInRect(rect1,point))
	{
		Threshold=min(255,max(0,point.x-1-rect.left));
		DoThreshold();
		m_Threshold=Threshold;
		UpdateData(0);	
	}
	CDialog::OnMouseMove(nFlags, point);
}

BOOL CThreshold::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_Method.AddString("手动阈值");
	m_Method.AddString("大津阈值");
	m_Method.SetCurSel(0);//初始化为手动阈值
	GetHistogram();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CThreshold::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
//		OnMouseMove(nFlags,point);
	CDialog::OnLButtonDown(nFlags, point);
}


void CThreshold::DoThreshold()
{
	int nIndex = m_Method.GetCurSel();
	if(nIndex==0)
	{
		Threshold=GetThreshold();
		ThresholdProcess(Threshold);
	}
	else if(nIndex==1)
	{
		Threshold=OtsuThreshold();
		m_Threshold=Threshold;
		UpdateData(0);
		ThresholdProcess(Threshold);
	}
}

void CThreshold::OnOK() 
{
	// TODO: Add extra validation here
	DoThreshold();
	StretchDIBits(T1,0,0,nWidth,nHeight,0,0,nWidth, nHeight,lpOut,pBIH,DIB_RGB_COLORS,SRCCOPY);
//	CDialog::OnOK();
}