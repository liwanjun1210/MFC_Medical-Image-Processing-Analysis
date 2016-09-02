// LOGIC_CAL.cpp : implementation file
//

#include "stdafx.h"
#include "PhotoAnalysis2.h"
#include "LOGIC_CAL.h"
#include "PhotoAnalysis2.h"
#include "imageload.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLOGIC_CAL dialog
int p_ByteWidth,p_Bits;
BYTE *lpBits;	BITMAPINFO *pBIH;
HDC T1;
int p_Width,p_Height;int m_Color;
void CLOGIC_CAL::getmembers(BITMAPINFO *m_pBIH,HDC t1,int m_nWidth,int m_nHeight,int m_nByteWidth,BYTE* m_lpOut)
{
	p_Width = m_nWidth;
	p_Height = m_nHeight;
	p_ByteWidth = m_nByteWidth;
	p_Bits = m_nByteWidth/m_nWidth*8;
	lpBits = m_lpOut;
	T1=t1;
	pBIH=m_pBIH;
	m_Color=p_Bits/8;
}

CLOGIC_CAL::CLOGIC_CAL(CWnd* pParent /*=NULL*/)
	: CDialog(CLOGIC_CAL::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLOGIC_CAL)
	m_radio = -1;
	//}}AFX_DATA_INIT
}


void CLOGIC_CAL::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLOGIC_CAL)
	DDX_Radio(pDX, IDC_RADIO_ADD, m_radio);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLOGIC_CAL, CDialog)
	//{{AFX_MSG_MAP(CLOGIC_CAL)
	ON_BN_CLICKED(IDC_RADIO_ADD, OnRadioAdd)
	ON_BN_CLICKED(IDC_RADIO_DIV, OnRadioDiv)
	ON_BN_CLICKED(IDC_RADIO_MUL, OnRadioMul)
	ON_BN_CLICKED(IDC_RADIO_SUB, OnRadioSub)
	ON_BN_CLICKED(IDC_RADIO_AND, OnRadioAnd)
	ON_BN_CLICKED(IDC_RADIO_OR, OnRadioOr)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLOGIC_CAL message handlers
void CLOGIC_CAL::Processing()
{
	lpOut = new BYTE[p_ByteWidth*p_Height];
	switch (m_radio)
	{
	case 1:
		{
			//图像加法
			int x,y;
			for(y=0;y<p_Height;y++)
			{
				for(x=0;x<p_Width;x++)
				{
					BYTE result = BYTE(0.5*double(lpBits[y*p_ByteWidth+3*x]) + 0.5*double(lpbits_temp[y*p_ByteWidth+3*x]));
					BYTE result1 = BYTE(0.5*double(lpBits[y*p_ByteWidth+3*x+1]) + 0.5*double(lpbits_temp[y*p_ByteWidth+3*x+1]));
					BYTE result2 = BYTE(0.5*double(lpBits[y*p_ByteWidth+3*x+2]) + 0.5*double(lpbits_temp[y*p_ByteWidth+3*x+2]));
					lpOut[y*p_ByteWidth+3*x] = result;
					lpOut[y*p_ByteWidth+3*x+1] = result1;
					lpOut[y*p_ByteWidth+3*x+2] = result2;
					//融合加法
				}
			}
			break;
		}
	case 2:
		{
			//图像减法
			int x,y;
			for(y=0;y<p_Height;y++)
			{
				for(x=0;x<p_Width;x++)
				{
					//如果结果小于零取反
					double temp = double(lpBits[y*p_Width+x]) - double(lpbits_temp[y*p_Width+x]);
					BYTE result;
					if (temp<0)
						result = BYTE(-temp);
					else
						result = BYTE(temp);
					lpOut[y*p_Width+x] = result;
				}
			}
			break;
		}
	case 3:
		{
			//图像乘法
			int x,y;
			double *temp = new double[p_Height*p_ByteWidth];
			double result,max = 0;
			//除以最大值
			for(y=0;y<p_Height;y++)
			{
				for(x=0;x<p_Width;x++)
				{
					result = double(lpBits[y*p_Width+x]) * double(lpbits_temp[y*p_Width+x]);
					temp[y*p_Width+x] = result;
					if (result>max)
					{
						max = result;
					}
				}
			}
			for(y=0;y<p_Height;y++)
			{
				for(x=0;x<p_Width;x++)
				{
					lpOut[y*p_Width+x] = BYTE(temp[y*p_Width+x]*255/max);
				}
			}
			delete[] temp;
			break;
		}
	case 4:
		{
			//图像除法
			double *temp = new double[p_Height*p_ByteWidth];
			int x,y;
			double result,max = 0;
			for(y=0;y<p_Height;y++)
			{
				for(x=0;x<p_Width;x++)
				{
					double sub = double(lpbits_temp[y*p_Width+x]);
					//被除数等于零则置1
					if(sub==0)
					{
						sub = 1;
					}
				
					result = double(lpBits[y*p_Width+x]) / sub;
					temp[y*p_Width+x] = result;
					if (result>max)
					{
						max = result;
					}
				}
			}
			for(y=0;y<p_Height;y++)
			{
				for(x=0;x<p_Width;x++)
				{
					lpOut[y*p_Width+x] = BYTE(temp[y*p_Width+x]*255/max);
				}
			}
			delete[] temp;
			break;
		}
	case 5:
		{
			//图像与运算
			int x,y;
			int gray1,gray2;
			for(y=0;y<p_Height;y++)
			{
				for(x=0;x<p_Width;x++)
				{
					gray1 = int(lpBits[y*p_Width+x]);
					gray2 = int(lpbits_temp[y*p_Width+x]);
					if (gray1<128 && gray2<128)
						lpOut[y*p_Width+x] = 0;
					else
						lpOut[y*p_Width+x] = 255;
					
				}
			}
			break;
		}
	case 6:
		{
			//图像或运算
			int x,y;
			int gray1,gray2;
			for(y=0;y<p_Height;y++)
			{
				for(x=0;x<p_Width;x++)
				{
					gray1 = int(lpBits[y*p_Width+x]);
					gray2 = int(lpbits_temp[y*p_Width+x]);
					if (gray1<128 || gray2<128)
						lpOut[y*p_Width+x] = 0;
					else
						lpOut[y*p_Width+x] = 255;
					
				}
			}
			break;
		}
	}
}

void CLOGIC_CAL::OnRadioAdd() 
{
	// TODO: Add your control notification handler code here
	m_radio = 1;
	Processing();
	StretchDIBits(T1,0,0,p_Width,p_Height,0,0,p_Width, p_Height,lpOut,pBIH,DIB_RGB_COLORS,SRCCOPY);
		
}

void CLOGIC_CAL::OnRadioDiv() 
{
	// TODO: Add your control notification handler code here
	m_radio = 4;
	Processing();
	StretchDIBits(T1,0,0,p_Width,p_Height,0,0,p_Width, p_Height,lpOut,pBIH,DIB_RGB_COLORS,SRCCOPY);
}

void CLOGIC_CAL::OnRadioMul() 
{
	// TODO: Add your control notification handler code here
	m_radio = 3;
	Processing();
	StretchDIBits(T1,0,0,p_Width,p_Height,0,0,p_Width, p_Height,lpOut,pBIH,DIB_RGB_COLORS,SRCCOPY);
}

void CLOGIC_CAL::OnRadioSub() 
{
	// TODO: Add your control notification handler code here
	m_radio = 2;
	Processing();
	StretchDIBits(T1,0,0,p_Width,p_Height,0,0,p_Width, p_Height,lpOut,pBIH,DIB_RGB_COLORS,SRCCOPY);
}

void CLOGIC_CAL::opentemp()
{
	char szFilter[] = "BMP Files(*.BMP)|*.BMP|GIF Files(*.GIF)|*.GIF|PCX Files(*.PCX)|*.PCX|Targa Files(*.TGA)|*.TGA|Jpeg Files(*.JPG)|*.JPG|Tif Files(*.TIF)|*.TIF||";
	CFileDialog dlg(TRUE,NULL,NULL,OFN_ALLOWMULTISELECT | OFN_NOVALIDATE |OFN_HIDEREADONLY, szFilter); 
	if(IDOK==dlg.DoModal()) 
	{
		//获取文件名
		CString Bmpname;
		//Bmpname.Format("%s",dlg.GetPathName()); 
		Bmpname = dlg.GetPathName();
		int bmpimagetype=FileType( Bmpname );
		CBitmap te_m_bitmap;
		HGLOBAL bmphdib;
		//如果存在图像,删除原图像
		if(te_m_bitmap.m_hObject)
			te_m_bitmap.DeleteObject();
		switch (bmpimagetype)
		{
			//图像句柄
		case IMAGETYPE_BMP:
			bmphdib = ::LoadBMP( Bmpname );
			break;
		case IMAGETYPE_GIF:
			bmphdib = ::LoadGIF( Bmpname );
			break;
		case IMAGETYPE_PCX:
			bmphdib = ::LoadPCX( Bmpname );
			break;
		case IMAGETYPE_TGA:
			bmphdib = ::LoadTGA( Bmpname );
			break;
		case IMAGETYPE_JPG:
			bmphdib = ::LoadJPG( Bmpname );
			break;
		case IMAGETYPE_TIF:
			bmphdib = ::LoadTIF( Bmpname );
			break;
	}
		BYTE *pTemp;
	  pTemp = (BYTE*)::GlobalLock( bmphdib );
	  BITMAPFILEHEADER *bmpBFH;
	  	if (pTemp == NULL) return;
		bmpBFH = (BITMAPFILEHEADER *)pTemp;//
		int nOffBits =bmpBFH->bfOffBits;
	lpbits_temp = pTemp+nOffBits;
	}
}


void CLOGIC_CAL::OnRadioAnd() 
{
	// TODO: Add your control notification handler code here
	m_radio = 5;
	Processing();
	StretchDIBits(T1,0,0,p_Width,p_Height,0,0,p_Width, p_Height,lpOut,pBIH,DIB_RGB_COLORS,SRCCOPY);
}

void CLOGIC_CAL::OnRadioOr() 
{
	// TODO: Add your control notification handler code here
	m_radio = 6;
	Processing();
	StretchDIBits(T1,0,0,p_Width,p_Height,0,0,p_Width, p_Height,lpOut,pBIH,DIB_RGB_COLORS,SRCCOPY);
}
