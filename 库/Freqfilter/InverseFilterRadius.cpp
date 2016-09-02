// InverseFilterRadius.cpp : implementation file
//

#include "stdafx.h"
//#include "	\ add additional includes here"
#include "InverseFilterRadius.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CInverseFilterRadius dialog


CInverseFilterRadius::CInverseFilterRadius(CWnd* pParent /*=NULL*/)
	: CDialog(CInverseFilterRadius::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInverseFilterRadius)
	m_nInverseFilterRadius = 40;
	//}}AFX_DATA_INIT
}


void CInverseFilterRadius::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInverseFilterRadius)
	DDX_Text(pDX, IDC_EDIT2, m_nInverseFilterRadius);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CInverseFilterRadius, CDialog)
	//{{AFX_MSG_MAP(CInverseFilterRadius)
	ON_BN_CLICKED(IDC_RADIO4, OnRadio4)
	ON_BN_CLICKED(IDC_RADIO2, OnRadio2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInverseFilterRadius message handlers

void CInverseFilterRadius::OnRadio4() 
{
	// TODO: Add your control notification handler code here
	m_nInverseFilterRadius = -1;
}

void CInverseFilterRadius::OnRadio2() 
{
	// TODO: Add your control notification handler code here
	m_nInverseFilterRadius = 0xFFFF;//这句话的作用很重要，为了避免鼠标点了"全滤波"之后，再输入半径的时候DoDataExchange函数失去功能！
}

void CInverseFilterRadius::GetMembers(int nByteWidth,int nHeight,int nBits,int nWidth,BYTE *lpBits,int nFlag)
{
	m_nByteWidth = nByteWidth;
	m_nHeight = nHeight;
	m_nBits = nBits;
	m_nWidth = nWidth;
	m_lpBits = lpBits;
	m_Flag=nFlag;
}

BOOL CInverseFilterRadius::InverseFilterAtmoTurb(double Para_k)
{
//	HCURSOR hcURSOR = SetCursor(LoadCursor(NULL, IDC_WAIT));	//更改光标形状

	//**********获取图像的像素区指针**********
	 if (m_Flag==0)
	 {
		 CString Info;
		 Info="请先进行退化处理";
		 AfxMessageBox(Info);
		 return FALSE;
	 }
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

	COMPLEX* temp  = new COMPLEX[w*h];
	COMPLEX* Model = new COMPLEX[w*h];
	for(j=0; j<h; j++)
	{
		for(i=0; i<w; i++)
		{
			temp[(i<w/2 ? i+w/2 : i-w/2) + (j<h/2 ? j+h/2 : j-h/2)*w] = FD[j + i*h];	//转置,移中。
		}
	}
	
	t.AtmosphTurbuDegeModel(Model, w, h, Para_k);//计算参数为Para_k的大气湍流退化模型
	
	//Restoration
	for (j=0; j<h; j++)
	{
		for(i=0;i<w;i++)
		{
			if (t.Distance(i,j,w/2,h/2) < m_nInverseFilterRadius)
			{
				temp[i + j*w] = Div(temp[i + j*w], Model[i + j*w]);
			}
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

BOOL CInverseFilterRadius::InverseFilterMotion(double Para_a, double Para_b, double Para_T, int FreqRadius)
{
	//add code here
	return TRUE;
}

//大气扰动引起退化的维纳滤波
BOOL CInverseFilterRadius::WienerFilterAtmoTurb()
{
	//add code here
	return TRUE;
}

//运动退化的维纳滤波
BOOL CInverseFilterRadius::WienerFilterMotion()
{
	//add code here
	return TRUE;
}
