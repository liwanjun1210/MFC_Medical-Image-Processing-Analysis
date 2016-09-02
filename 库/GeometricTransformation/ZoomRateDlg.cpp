// ZoomRateDlg.cpp : implementation file
//

#include "stdafx.h"
//#include "	\ add additional includes here"
#include "ZoomRateDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZoomRateDlg dialog
CZoomRateDlg::CZoomRateDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CZoomRateDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CZoomRateDlg)
	m_fZoomRateHeight = 1.0f;
	m_fZoomRateWidth = 1.0f;
	//}}AFX_DATA_INIT
}


void CZoomRateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CZoomRateDlg)
	DDX_Text(pDX, IDC_RATE_H, m_fZoomRateHeight);
	DDV_MinMaxFloat(pDX, m_fZoomRateHeight, 1.e-004f, 10000.f);
	DDX_Text(pDX, IDC_RATE_W, m_fZoomRateWidth);
	DDV_MinMaxFloat(pDX, m_fZoomRateWidth, 1.e-004f, 10000.f);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CZoomRateDlg, CDialog)
	//{{AFX_MSG_MAP(CZoomRateDlg)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZoomRateDlg message handlers
void CZoomRateDlg::Zoom( int m_nWidth,int m_nHeight,int m_nByteWidth,BITMAPINFOHEADER *pNewBIH,BYTE *lpBits)
{

	float RateX = 0;
	float RateY = 0;
	if (DoModal() != IDOK)
	{
		return;
	}
	RateX = m_fZoomRateWidth;
	RateY = m_fZoomRateHeight;
	
	if (RateX == 1 && RateY == 1)	//图像实际上没有变化
	{
		
		return;	
	
	}
	T_Width = (int)(m_nWidth*RateX);
	T_Height = (int)(m_nHeight*RateY);
	BYTE *pOldTemp,*pNewTemp;
	
	newByteWidth=int (m_nByteWidth*RateX);

    pNewBIH->biSizeImage = newByteWidth * T_Height;
    pNewBIH->biWidth =T_Width;
    pNewBIH->biHeight = T_Height;
	lpOut=new BYTE[newByteWidth*T_Height];
	
	for (int i=0;i<T_Height; i++)
	{ 
		int ii = ( m_nHeight * i ) / T_Height;
		pOldTemp = lpBits;
		pOldTemp +=  ( m_nHeight - 1 - ii ) * m_nByteWidth ;
		pNewTemp = lpOut;
		pNewTemp += ( T_Height - 1 - i ) * newByteWidth;
		for( int j=0; j<T_Width; j++ )
		{
			int jj = ( m_nWidth * j ) / T_Width;
			pNewTemp[j] = pOldTemp[jj];
		} 
	}

}
