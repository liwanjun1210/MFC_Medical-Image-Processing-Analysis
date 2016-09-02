// Get_RGB.cpp : implementation file
//

#include "stdafx.h"
#include "ShowRGB.h"
#include "Get_RGB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CGet_RGB dialog

int m_nWidth;
int m_nHeight;
int m_nBits;
int nByteWidth;
BYTE *lpBits;
int xx,yy;
CGet_RGB::CGet_RGB(CWnd* pParent /*=NULL*/)
	: CDialog(CGet_RGB::IDD, pParent)
{
	//{{AFX_DATA_INIT(CGet_RGB)
	m_PointX = xx;
	m_PointY = yy;
	m_Red = red;
	m_Green = green;
	m_Blue = blue;
	//}}AFX_DATA_INIT
}


void CGet_RGB::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CGet_RGB)
	DDX_Text(pDX, IDC_EDIT_BLUE, m_Blue);
	DDV_MinMaxInt(pDX, m_Blue, 0, 255);
	DDX_Text(pDX, IDC_EDIT_GREEN, m_Green);
	DDV_MinMaxInt(pDX, m_Green, 0, 255);
	DDX_Text(pDX, IDC_EDIT_POINTX, m_PointX);
	DDX_Text(pDX, IDC_EDIT_POINTY, m_PointY);
	DDX_Text(pDX, IDC_EDIT_RED, m_Red);
	DDV_MinMaxInt(pDX, m_Red, 0, 255);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CGet_RGB, CDialog)
	//{{AFX_MSG_MAP(CGet_RGB)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGet_RGB message handlers

void CGet_RGB::GetRGBValue(int x,int y)
	//	unsigned char& red,unsigned char& green,unsigned char& blue/*,int nByteWidth,char *lpBits*/)
{
	if(x<0 ||x>=m_nWidth) return;
	if(y<0 ||y>=m_nHeight) return;
	switch( m_nBits )
	{
	case 8:
		red=lpBits[(m_nHeight-1-y)*nByteWidth+x];
		green=lpBits[(m_nHeight-1-y)*nByteWidth+x];
		blue=lpBits[(m_nHeight-1-y)*nByteWidth+x];
		break;
	case 16:
		GETRGB555(red,green,blue,(lpBits+(m_nHeight-1-y)*nByteWidth+x*2));
		break;
	case 24:
		red=lpBits[(m_nHeight-1-y)*nByteWidth+x*3+2];
		green=lpBits[(m_nHeight-1-y)*nByteWidth+x*3+1];
		blue=lpBits[(m_nHeight-1-y)*nByteWidth+x*3];//第一字节为蓝色
		//即RGB图象存放时是以bgr的格式存放的
		break;
	case 32:
		GETRGB888(red,green,blue,(lpBits+(m_nHeight-1-y)*nByteWidth+x*4));
		break;
	}
	xx = x;
	yy = y;
}
void CGet_RGB::GetMembers(int nWidth,int nHeight,int nBits,int mByteWidth,BYTE *m_lpOut)
{
	m_nWidth = nWidth;
	m_nHeight = nHeight;
	m_nBits = nBits;
	lpBits = m_lpOut;
	nByteWidth=mByteWidth;
}
extern "C" __declspec(dllexport) void Show()
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	CGet_RGB Dlg;
	Dlg.DoModal();
}
