// HomomorphicFilter.cpp : implementation file
//

#include "stdafx.h"
//#include "	\ add additional includes here"
#include "HomomorphicFilter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHomomorphicFilter dialog


CHomomorphicFilter::CHomomorphicFilter(CWnd* pParent /*=NULL*/)
	: CDialog(CHomomorphicFilter::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHomomorphicFilter)
	m_nCutoffFreq = 50;
	m_fGammaH = 2.0f;
	m_fGammaL = 0.5f;
	//}}AFX_DATA_INIT
}


void CHomomorphicFilter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHomomorphicFilter)
	DDX_Text(pDX, IDC_CUTOFF_FREQ, m_nCutoffFreq);
	DDX_Text(pDX, IDC_GAMMAH, m_fGammaH);
	DDX_Text(pDX, IDC_GAMMAL, m_fGammaL);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHomomorphicFilter, CDialog)
	//{{AFX_MSG_MAP(CHomomorphicFilter)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHomomorphicFilter message handlers

void CHomomorphicFilter::GetMembers(int nByteWidth,int nHeight,int nBits,int nWidth,BYTE *lpBits)
{
	m_nByteWidth = nByteWidth;
	m_nHeight = nHeight;
	m_nBits = nBits;
	m_nWidth = nWidth;
	m_lpBits = lpBits;
}

BOOL CHomomorphicFilter::HomomorphicFilter()
{
//	HCURSOR hcURSOR = SetCursor(LoadCursor(NULL, IDC_WAIT));	//更改光标形状

	//**********获取图像的像素区指针**********
	 
	//开辟频域、时域新空间
	int w=1, h=1, wp=0, hp=0;
	while(w < m_nWidth)
	{
		w *= 2;
		wp++;
	}
	while(h < m_nHeight)
	{
		h *= 2;
		hp++;
	}
	COMPLEX *TD = new COMPLEX[w*h];
	COMPLEX *FD = new COMPLEX[w*h];

	//赋初值
	int i,j;
	for(j=0; j<h; j++)
	{
		for(i=0; i<w; i++)
		{
			TD[i+w*j].re = 0;	
			TD[i+w*j].im = 0;
		}
	}
	for(j=0; j<m_nHeight; j++)
	{
		for(i=0; i<m_nWidth; i++)
		{
			TD[i + j*m_nByteWidth].re = m_lpBits[i + j*m_nByteWidth];
		}
	}

	CCOMPLEX t;
	//FFT
	for(j=0;j<h;j++)
	{
		t.FFT(&TD[w*j],&FD[w*j],wp);
	}
	for(j=0;j<h;j++)
	{
		for(i=0;i<w;i++)
		{
			TD[j+h*i]=FD[i+w*j];	//转置	
//			TD[i+w*j]=FD[i*h+j];
		}
	}
	for(i=0;i<w;i++)
	{
		t.FFT(&TD[i*h],&FD[i*h],hp);
	}

	COMPLEX* temp   = new COMPLEX[w*h];
	COMPLEX* FILTER = new COMPLEX[w*h];
	for(j=0; j<h; j++)
	{
		for(i=0; i<w; i++)
		{
			temp[(i<w/2 ? i+w/2 : i-w/2) + (j<h/2 ? j+h/2 : j-h/2)*w] = FD[j + i*h];	//转置,移中。
		}
	}
	t.Calculate(FILTER, m_fGammaH, m_fGammaL, m_nCutoffFreq, w, h);//计算同态滤波器的滤波函数

	//Homomorphic Filter
	for (j=0; j<h; j++)
	{
		for(i=0;i<w;i++)
		{
 			temp[i + j*w] = Mul(FILTER[i + j*w], temp[i + j*w]); 
		}
	}
	for(j=0; j<h; j++)
	{
		for(i=0; i<w; i++)
		{
			FD[(i<w/2 ? i+w/2 : i-w/2) + (j<h/2 ? j+h/2 : j-h/2)*w] = temp[j + i*h];	//复原频谱图。
		}
	}	
	
	//IFFT
	for(j=0;j<h;j++)
	{
		t.IFFT(&FD[w*j],&TD[w*j],wp);
	}
	for(j=0;j<h;j++)
	{
		for(i=0;i<w;i++)
		{
			FD[j+h*i]=TD[i+w*j];
		}
	}
	for(i=0;i<w;i++)
	{
		t.IFFT(&FD[i*h],&TD[i*h],hp);
	}

	int len=m_nByteWidth*m_nHeight;
	m_lpOut=new BYTE[len];
	//将变换结果写入图像中
	for(j=0; j<h; j++)
	{
		for(i=0; i<w; i++)
		{
			m_lpOut[i + j*m_nByteWidth] = (unsigned char)(TD[i+w*j].re);
		}
	}

	delete [] TD;
	delete [] FD;

//	SetCursor(hcURSOR);		//恢复光标形状
	return TRUE;
}
