// REGIONGROWTH.cpp : implementation file
//

#include "stdafx.h"
#include "PhotoAnalysis2.h"
#include "REGIONGROWTH.h"
#define BKcolor 127
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CREGIONGROWTH dialog

void CREGIONGROWTH::getmember(BITMAPINFO *m_pBIH,HDC t1,int m_nWidth,int m_nHeight,int m_nByteWidth,BYTE *m_lpBits,BYTE *m_lpOut)
{
	p_Width = m_nWidth;
	p_Height = m_nHeight;
	p_ByteWidth = m_nByteWidth;
	lpbits = m_lpBits;
	lpOut = m_lpOut;
	m_Color = p_ByteWidth/p_Width;
	pBIH=m_pBIH;
	T1=t1;
	m_Color=m_nByteWidth/m_nWidth;
}

CREGIONGROWTH::CREGIONGROWTH(CWnd* pParent /*=NULL*/)
	: CDialog(CREGIONGROWTH::IDD, pParent)
{
	//{{AFX_DATA_INIT(CREGIONGROWTH)
	m_pX = 10;
	m_pY = 10;
	m_th = 2;
	//}}AFX_DATA_INIT
}


void CREGIONGROWTH::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CREGIONGROWTH)
	DDX_Text(pDX, IDC_EDIT_POINTX, m_pX);
	DDX_Text(pDX, IDC_EDIT_POINTY, m_pY);
	DDX_Text(pDX, IDC_EDIT_THRE, m_th);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CREGIONGROWTH, CDialog)
	//{{AFX_MSG_MAP(CREGIONGROWTH)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CREGIONGROWTH message handlers

BOOL CREGIONGROWTH::OnInitDialog() 
{
	CDialog::OnInitDialog();
	// TODO: Add extra initialization here
//	m_th = 1;
//	m_pX = 0;
//	m_pY = 0;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
void CREGIONGROWTH::Growing(BYTE *seedmap,int delta)
{
	int x,y;
	bool loop = false;
	BYTE *nextseedmap = new BYTE[p_Height*p_Width];
	memcpy(nextseedmap,seedmap,p_Height*p_Width);
	for(y=1;y<p_Height-1;y++)
	{
		for(x=1;x<p_Width-1;x++)
		{
			//种子点
			if (seedmap[x+y*p_Width]==BKcolor)
			{
				//检查四方向是否可生长
				if(abs(lpbits[x+y*p_Width]-lpbits[x+(y-1)*p_Width])<delta && seedmap[x+(y-1)*p_Width]!=BKcolor) 
				{
					nextseedmap[x+(y-1)*p_Width] = BKcolor;
					loop = true;
				}
				else if(abs(lpbits[x+y*p_Width]-lpbits[x-1+y*p_Width])<delta && seedmap[x-1+y*p_Width]!=BKcolor)
				{
					nextseedmap[x-1+y*p_Width] = BKcolor;
					loop = true;
				}
				else if(abs(lpbits[x+y*p_Width]-lpbits[x+1+y*p_Width])<delta && seedmap[x+1+y*p_Width]!=BKcolor)
				{
					nextseedmap[x+1+y*p_Width] = BKcolor;
					loop = true;
				}
				else if(abs(lpbits[x+y*p_Width]-lpbits[x+(y+1)*p_Width])<delta && seedmap[x+(y+1)*p_Width]!=BKcolor)
				{
					nextseedmap[x+(y+1)*p_Width] = BKcolor;
					loop = true;
				}
			}
		}
	}
	memcpy(seedmap,nextseedmap,p_Height*p_Width);
	delete[] nextseedmap;
	//迭代生长
	if (loop)
		Growing(seedmap,delta);
}
void CREGIONGROWTH::OnReGrow() 
{
	// TODO: Add your control notification handler code here
	//获取参数
	int seedX = m_pX;
	int seedY = p_Height - m_pY;
	
	int delta = m_th;
//	memcpy(lpbits,lpBits,p_Height*p_Width);
	//建立种子图
	BYTE *SeedMap = new BYTE[p_Height*p_Width];
	memset(SeedMap,255,sizeof(BYTE)*p_Height*p_Width);
	SeedMap[seedX+seedY*p_Width] = BKcolor;
	//区域生长函数
	Growing(SeedMap,delta);
	//将未生长的区域用原图补充
	int x,y;
	for(y=1;y<p_Height-1;y++)
	{
		for(x=1;x<p_Width-1;x++)
		{
			if (SeedMap[x+y*p_Width]!=BKcolor)
			{
				SeedMap[x+y*p_Width] = lpbits[x+y*p_Width];
			}
		}
	}
	//将起始点在图像上显示
	SeedMap[seedX-1+seedY*p_Width] = 0;
	SeedMap[seedX+1+seedY*p_Width] = 0;
	SeedMap[seedX+(seedY+1)*p_Width] = 0;
	SeedMap[seedX+(seedY-1)*p_Width] = 0;
	memcpy(lpbits_trans,SeedMap,p_Height*p_Width);
	delete[] SeedMap;
	StretchDIBits(T1,0,0,p_Width,p_Height,0,0,p_Width, p_Height,lpbits_trans,pBIH,DIB_RGB_COLORS,SRCCOPY);
	
	
}

void CREGIONGROWTH::OnOK() 
{
	// TODO: Add extra validation here
	OnReGrow();
	CDialog::OnOK();
}
