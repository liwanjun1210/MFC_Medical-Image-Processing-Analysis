// DegenerateModel.cpp : implementation file
//

#include "stdafx.h"
//#include "	\ add additional includes here"
#include "DegenerateModel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDegenerateModel dialog


CDegenerateModel::CDegenerateModel(CWnd* pParent /*=NULL*/)
	: CDialog(CDegenerateModel::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDegenerateModel)
	DegenerateModelFlag =0;
	m_fAtmosTurbPara_k = 0.0025;
	m_fMotionDegePara_a = 0.1;
	m_fMotionDegePara_b = 0.1;
	m_fMotionDegePara_T = 1.0;
	//}}AFX_DATA_INIT
}


void CDegenerateModel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDegenerateModel)
	DDX_Text(pDX, IDC_EDIT1_k, m_fAtmosTurbPara_k);
	DDV_MinMaxDouble(pDX, m_fAtmosTurbPara_k, 1.e-012, 1.);
	DDX_Text(pDX, IDC_EDIT2_a, m_fMotionDegePara_a);
	DDX_Text(pDX, IDC_EDIT2_b, m_fMotionDegePara_b);
	DDX_Text(pDX, IDC_EDIT2_T, m_fMotionDegePara_T);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDegenerateModel, CDialog)
	//{{AFX_MSG_MAP(CDegenerateModel)
	ON_BN_CLICKED(IDC_ATMOSPHERIC_TURBULENCE, OnAtmosphericTurbulence)
	ON_BN_CLICKED(IDC_MOTION_DEGENERATE, OnMotionDegenerate)
	ON_BN_CLICKED(IDC_REGENETATED_IMAGE, OnRegenetatedImage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDegenerateModel message handlers

void CDegenerateModel::OnAtmosphericTurbulence() 
{
	// TODO: Add your control notification handler code here
	DegenerateModelFlag = 1;
}

void CDegenerateModel::OnMotionDegenerate() 
{
	// TODO: Add your control notification handler code here
	DegenerateModelFlag = 2;
}

void CDegenerateModel::OnRegenetatedImage() 
{
	// TODO: Add your control notification handler code here
	DegenerateModelFlag = 3;
}

void CDegenerateModel::GetMembers(int nByteWidth,int nHeight,int nBits,int nWidth,BYTE *lpBits)
{
	m_nByteWidth = nByteWidth;
	m_nHeight = nHeight;
	m_nBits = nBits;
	m_nWidth = nWidth;
	m_lpBits = lpBits;
}

BOOL CDegenerateModel::Degenerate()
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

	COMPLEX* temp  = new COMPLEX[w*h];
	COMPLEX* Model = new COMPLEX[w*h];
	for(j=0; j<h; j++)
	{
		for(i=0; i<w; i++)
		{
			temp[(i<w/2 ? i+w/2 : i-w/2) + (j<h/2 ? j+h/2 : j-h/2)*w] = FD[j + i*h];	//转置,移中。
		}
	}
	
	if (DegenerateModelFlag == 1)
	{
		t.AtmosphTurbuDegeModel(Model, w, h, m_fAtmosTurbPara_k);//计算参数为Para_k的大气湍流退化模型
	}
	else if (DegenerateModelFlag == 2)
	{
		t.MotionDegenerateModel(Model, w, h, m_fMotionDegePara_a, m_fMotionDegePara_b, m_fMotionDegePara_T);
	}
	else
		return FALSE;
	
	//Calculate(Model, 50, 1,  w,  h,BWLOWPASS);//测试函数执行过程是否正确，事实证明，函数执行过程没有问题！2010.12.13

	//Degenerate
	for (j=0; j<h; j++)
	{
		for(i=0;i<w;i++)
		{
 			temp[i + j*w] = Mul(Model[i + j*w], temp[i + j*w]); 
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
