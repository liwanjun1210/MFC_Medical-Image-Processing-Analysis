// HistogramView1.cpp : implementation file
//

#include "stdafx.h"
#include "HistogramView.h"
#include "HistogramView1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHistogramView dialog
int nWidth;
int nHeight;
int nByteWidth;
BYTE *lpBits;
int nBits;
BYTE *lpOut;
BOOL Flag;

CHistogramView::CHistogramView(CWnd* pParent /*=NULL*/)
	: CDialog(CHistogramView::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHistogramView)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CHistogramView::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHistogramView)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHistogramView, CDialog)
	//{{AFX_MSG_MAP(CHistogramView)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHistogramView message handlers
void CHistogramView::getmember(int m_nWidth,int m_nHeight,int m_nByteWidth,BYTE *m_lpBits,int m_nBits,BYTE *m_lpOut,BOOL m_Flag)
{
	nWidth = m_nWidth;
	nHeight = m_nHeight;
	nByteWidth = m_nByteWidth;
	lpBits = m_lpBits;
	nBits = m_nBits;
	Flag = m_Flag;
	lpOut = m_lpOut;

}
BOOL CHistogramView::OnInitDialog() 
{
CDialog::OnInitDialog();

	int nSize = 1<<nBits;
	long* plCount = NULL;
	int x,y,k;
	switch (nBits)
	{
	case 8:
		//根据图像的位置分配相应的内存
		plCount = new long[nSize];
		m_pfDistr = new float[nSize];
		
		if ((m_pfDistr == NULL)||(plCount == NULL))
		{
			return FALSE;
		}
		//请清零
		for(k=0; k<nSize; k++) 
		{
			plCount[k] = 0;
			m_pfDistr[k] = 0;
		}
		break;
	case 16:
		break;
	case 24:
		break;
	default:
		break;
	}
	//
	if(Flag == 0)
	{
		for(y=0;y<nHeight;y++)				
		{
			for(x=0;x<nWidth;x++)
			{
				plCount[lpBits[(nHeight-1-y)*nByteWidth+x]]++;
			}
		}
	}
	else
	{
		for(y=0;y<nHeight;y++)				
		{
			for(x=0;x<nWidth;x++)
			{
				plCount[lpOut[(nHeight-1-y)*nByteWidth+x]]++;
			}
		}
	}
	long lTotalCount = (long)nHeight*nWidth;
	for (k=0;k<nSize;k++)
	{
		
		m_pfDistr[k] = plCount[k]/(float)lTotalCount;
		
	}
	
	delete[] plCount;	//回收分配的一组对象的内存空间
	plCount = NULL;
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CHistogramView::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	// 获取绘制坐标的文本框
	CWnd* pWnd = GetDlgItem(IDC_COORD);
	CDC* pDC = pWnd->GetDC();
	pWnd->Invalidate();
	pWnd->UpdateWindow();
	
	RECT rect;
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
extern "C" __declspec(dllexport) void Show()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CHistogramView test;
	test.DoModal ();
}