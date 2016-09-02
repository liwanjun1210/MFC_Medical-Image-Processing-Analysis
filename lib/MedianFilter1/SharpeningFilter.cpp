// SharpeningFilter.cpp : implementation file
//

#include "stdafx.h"
//#include "	\ add additional includes here"
#include "SharpeningFilter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SharpeningFilter dialog


void CSharpeningFilterDlg::getmember(int nWidth,int nHeight,int nByteWidth,int nBits,BYTE *m_lpOut)
{
	m_nWidth = nWidth;
	m_nHeight = nHeight;
	m_nByteWidth = nByteWidth;
	m_nBits = nBits;
	lpBits = m_lpOut;
	lpOut = m_lpOut;
}

CSharpeningFilterDlg::CSharpeningFilterDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSharpeningFilterDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(SharpeningFilter)
	m_nSharpCoef00 = 0;
	m_nSharpCoef01 = 1;
	m_nSharpCoef02 = 0;
	m_nSharpCoef03 = 1;
	m_nSharpCoef04 = -4;
	m_nSharpCoef05 = 1;
	m_nSharpCoef06 = 0;
	m_nSharpCoef07 = 1;
	m_nSharpCoef08 = 0;
	//}}AFX_DATA_INIT
}


void CSharpeningFilterDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SharpeningFilter)
	DDX_Text(pDX, IDC_SHARP_COEF_00, m_nSharpCoef00);
	DDX_Text(pDX, IDC_SHARP_COEF_01, m_nSharpCoef01);
	DDX_Text(pDX, IDC_SHARP_COEF_02, m_nSharpCoef02);
	DDX_Text(pDX, IDC_SHARP_COEF_03, m_nSharpCoef03);
	DDX_Text(pDX, IDC_SHARP_COEF_04, m_nSharpCoef04);
	DDX_Text(pDX, IDC_SHARP_COEF_05, m_nSharpCoef05);
	DDX_Text(pDX, IDC_SHARP_COEF_06, m_nSharpCoef06);
	DDX_Text(pDX, IDC_SHARP_COEF_07, m_nSharpCoef07);
	DDX_Text(pDX, IDC_SHARP_COEF_08, m_nSharpCoef08);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSharpeningFilterDlg, CDialog)
	//{{AFX_MSG_MAP(SharpeningFilter)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SharpeningFilter message handlers
//*****************************
//
//**********锐化空间滤波*******
//
//*****************************
BOOL CSharpeningFilterDlg::SharpeningFilter(int* piSharpCoef)
{
	lpOut=new BYTE[m_nByteWidth*m_nHeight];
	if (lpBits == NULL)
	{
		return FALSE;
	}
	HCURSOR hcURSOR = SetCursor(LoadCursor(NULL, IDC_WAIT));	//更改光标形状
	m_iWinSize=3;
	int iX = m_iWinSize / 2;
	int iY = m_iWinSize / 2;
	int PixelTemp = 0;
	int i, j, ii, jj;
	int yy;
	for (int kk=0;kk<m_iWinSize*m_iWinSize;kk++)
	{
		yy=piSharpCoef[kk];
	}
	
	switch(m_nBits)
	{
	case 8:
		for (j=iY; j < m_nHeight-iY; j++)
		{
			for (i=iX; i < m_nWidth-iX; i++)
			{
				//前面两个for是图像循环，下面两个for是模板循环
				for (jj=0; jj<m_iWinSize; jj++)
				{
					for (ii=0; ii<m_iWinSize; ii++)
					{
						PixelTemp += piSharpCoef[jj*m_iWinSize + ii] * lpBits[(m_nHeight-1-(j-iY+jj))*m_nByteWidth+(i-iX+ii)];
					}
				}
				
				PixelTemp = (PixelTemp+255) / 2;	//因为锐化图像中可能存在负值，因此需要标定。详细介绍见<冈萨雷斯>P88
				lpOut[(m_nHeight-1-j)*m_nByteWidth+i] = PixelTemp;
				//pNewBits[(iHeight-1-j)*nWidthBytes+i] =pOldBits[(iHeight-1-j)*nWidthBytes+i]-PixelTemp;
				PixelTemp = 0;
			}
		}
		break;
	case 16:
		break;
	case 24:
		break;
	case 32:
		break;
	default:
		break;
	}
	
	SetCursor(hcURSOR);		//恢复光标形状
	
	return TRUE;
}
