// PhotoAnalysis2View.cpp : implementation of the CPhotoAnalysis2View class
//

#include "stdafx.h"
#include "PhotoAnalysis2.h"

#include "PhotoAnalysis2Doc.h"
#include "PhotoAnalysis2View.h"
#include "imageload.h"
#include "MainFrm.h"
#include "Get_RGB.h"
#include "Threshold.h"
#include "MorPhologyDlg.h"
#include "HSV_RGBDlg.h"
#include "GrayStretchDlg.h"
#include "LinerParaDlg.h"
#include "HisEqlize.h"
#include "HistogramMatchingDlg.h"
#include "MedianFiltDlg.h"
#include "SharpeningFilter.h"
#include "MirrorTransform.h"
#include "ZoomDlg.h"
#include "LOGIC_CAL.h"
#include "ButterworthFilter.h"
#include "IdealFilter.h"
#include "HomomorphicFilter.h"
#include "InverseFilterRadius.h"
#include "DegenerateModel.h"
#include "REGIONGROWTH.h"
#include "math.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPhotoAnalysis2View

IMPLEMENT_DYNCREATE(CPhotoAnalysis2View, CScrollView)

BEGIN_MESSAGE_MAP(CPhotoAnalysis2View, CScrollView)
	//{{AFX_MSG_MAP(CPhotoAnalysis2View)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_WM_MOUSEMOVE()
	ON_COMMAND(ID_GRAY_LINAR_STRETCH, OnGrayLinarStretch)
	ON_COMMAND(ID_GRAY_PIECEWISE, OnGrayPiecewise)
	ON_COMMAND(ID_COLOR_TO_GRAY, OnColorToGray)
	ON_COMMAND(ID_THRESHOLD, OnThreshold)
	ON_COMMAND(ID_RGB_TO_HSV, OnRgbToHsv)
	ON_COMMAND(ID_HISTOGRAM_EQUALIZE, OnHistogramEqualize)
	ON_COMMAND(ID_HISTOGRAM_MATCHING, OnHistogramMatching)
	ON_COMMAND(ID_ENHANCE_MIDIANFILTER, OnEnhanceMidianfilter)
	ON_COMMAND(ID_ENHANCE_MAXFILTER, OnEnhanceMaxfilter)
	ON_COMMAND(ID_ENHANCE_MINFILTER, OnEnhanceMinfilter)
	ON_COMMAND(ID_ENHANCE_EQUALIZEFILTER, OnEnhanceEqualizefilter)
	ON_COMMAND(ID_ENHANCE_SHARPENINGFILTER, OnEnhanceSharpeningfilter)
	ON_COMMAND(ID_GRAY_TO_COLOR, OnGrayToColor)
	ON_COMMAND(ID_TRANSFORM_MIRROR_X, OnTransformMirrorX)
	ON_COMMAND(ID_TRANSFORM_MIRROR_Y, OnTransformMirrorY)
	ON_COMMAND(ID_ZOOM, OnZoom)
	ON_COMMAND(ID_FFT, OnFft)
	ON_COMMAND(ID_IFFT, OnIfft)
	ON_COMMAND(ID_IMAGE_CAL, OnImageCal)
	ON_COMMAND(ID_IDEAL_LPF, OnIdealLpf)
	ON_COMMAND(ID_IDEAL_HPF, OnIdealHpf)
	ON_COMMAND(ID_BUTTER_LPF, OnButterLpf)
	ON_COMMAND(ID_BUTTER_HPF, OnButterHpf)
	ON_COMMAND(ID_HOMOMORPHIC_FILTER, OnHomomorphicFilter)
	ON_COMMAND(ID_INVERSE_FILTER, OnInverseFilter)
	ON_COMMAND(ID_MENUITEM32807, OnMenuitem32807)
	ON_COMMAND(ID_DEGENERATE, OnDegenerate)
	ON_COMMAND(ID_INVERSE, OnInverse)
	ON_COMMAND(ID_MORPHOLOGY, OnMorphology)
	ON_COMMAND(ID_REGION_GROW, OnRegionGrow)
	ON_COMMAND(ID_REGION_DIVANDCON, OnRegionDivandcon)
	ON_COMMAND(ID_FILE_SAVE_AS, OnFileSaveAs)
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CScrollView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CScrollView::OnFilePrintPreview)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPhotoAnalysis2View construction/destruction

CPhotoAnalysis2View::CPhotoAnalysis2View()
{
	// TODO: add construction code here

}

CPhotoAnalysis2View::~CPhotoAnalysis2View()
{
}

BOOL CPhotoAnalysis2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CScrollView::PreCreateWindow(cs);
}

/////////////////////////////////////////////////////////////////////////////
// CPhotoAnalysis2View drawing

void CPhotoAnalysis2View::OnDraw(CDC* pDC)
{
		switch(m)
		{
		case 0:StretchDIBits(pDC->GetSafeHdc(),0,0,p_Width,p_Height,0,0,p_Width, p_Height,pBits,pBIH,DIB_RGB_COLORS,SRCCOPY);
		break;
		case 1:StretchDIBits(pDC->GetSafeHdc(),0,0,p_Width,p_Height,0,0,p_Width, p_Height,lpOut,pBIH,DIB_RGB_COLORS,SRCCOPY);
        case 2:StretchDIBits(pDC->GetSafeHdc(),0,0,p_Width,p_Height,0,0,p_Width, p_Height,lpOut,pNewBIH,DIB_RGB_COLORS,SRCCOPY);
			  break;
			
		}
}

void CPhotoAnalysis2View::OnInitialUpdate()
{
	CScrollView::OnInitialUpdate();

	CSize sizeTotal;
	// TODO: calculate the total size of this view
	sizeTotal.cx = sizeTotal.cy = 100;
	SetScrollSizes(MM_TEXT, sizeTotal);
}

/////////////////////////////////////////////////////////////////////////////
// CPhotoAnalysis2View printing

BOOL CPhotoAnalysis2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	// 设置总页数为一。
	pInfo->SetMaxPage(1);
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CPhotoAnalysis2View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CPhotoAnalysis2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}

/////////////////////////////////////////////////////////////////////////////
// CPhotoAnalysis2View diagnostics

#ifdef _DEBUG
void CPhotoAnalysis2View::AssertValid() const
{
	CScrollView::AssertValid();
}

void CPhotoAnalysis2View::Dump(CDumpContext& dc) const
{
	CScrollView::Dump(dc);
}

CPhotoAnalysis2Doc* CPhotoAnalysis2View::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CPhotoAnalysis2Doc)));
	return (CPhotoAnalysis2Doc*)m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPhotoAnalysis2View message handlers

void CPhotoAnalysis2View::OnFileOpen() 
{
	// TODO: Add your command handler code here
	m =0;
	pBits =NULL;
	CString FName;
	char szFilter[] = "BMP Files(*.BMP)|*.BMP|GIF Files(*.GIF)|*.GIF|PCX Files(*.PCX)|*.PCX|Targa Files(*.TGA)|*.TGA|Jpeg Files(*.JPG)|*.JPG|Tif Files(*.TIF)|*.TIF||";
	CFileDialog dlg(TRUE,NULL,NULL,OFN_ALLOWMULTISELECT | OFN_NOVALIDATE |OFN_HIDEREADONLY, szFilter);
	if(dlg.DoModal()==IDOK)
	{
		FName = dlg.GetPathName();
		p_Imagetype = FileType( FName );
		switch (p_Imagetype)
		{
			//图像句柄
		case IMAGETYPE_BMP:
			m_hDib = ::LoadBMP( FName );
			break;
		case IMAGETYPE_GIF:
			m_hDib = ::LoadGIF( FName );
			break;
		case IMAGETYPE_PCX:
			m_hDib = ::LoadPCX( FName );
			break;
		case IMAGETYPE_TGA:
			m_hDib = ::LoadTGA( FName );
			break;
		case IMAGETYPE_JPG:
			m_hDib = ::LoadJPG( FName );
			break;
		case IMAGETYPE_TIF:
			m_hDib = ::LoadTIF( FName );
			break;
		}
	BYTE *pTemp;
	
	pTemp = (BYTE*)::GlobalLock( m_hDib );
	if (pTemp == NULL) return;
	pBFH = (BITMAPFILEHEADER *)pTemp;//
	int nOffBits = pBFH->bfOffBits;
	pBits = pTemp+nOffBits;
	lpOut = pTemp+nOffBits;
	pBIH = (BITMAPINFO *) &pTemp[sizeof(BITMAPFILEHEADER)];
	
	
	p_Width = pBIH->bmiHeader.biWidth;
	p_Height = pBIH->bmiHeader.biHeight;
	p_Bits = pBIH->bmiHeader.biBitCount;
	p_Colors = 1 << p_Bits; 
	p_ByteWidth = p_Width*(p_Bits/8);
	if(p_ByteWidth%4) p_ByteWidth += 4-(p_ByteWidth%4); 
	::GlobalUnlock( m_hDib ); 
	Invalidate();
	}
}


void CPhotoAnalysis2View::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	CScrollView::OnMouseMove(nFlags, point);

	CMainFrame *pMainFrame=(CMainFrame*)AfxGetMainWnd();
	CStatusBar *pStatusBar=&pMainFrame->m_wndStatusBar;

	CString str;
	if(!pBits==NULL)
	{
	str.Format("%d X %d X %d",p_Width,p_Height,p_Bits/8);
	}
	else str="NULL";
	pStatusBar->SetPaneText(1,str);

	int scroll_x = GetScrollPos(SB_HORZ); 
	int scroll_y = GetScrollPos(SB_VERT);
	point.y += scroll_y;
	point.x += scroll_x;
	if(pStatusBar && point.x<p_Width && point.y<p_Height)//在状态栏显示鼠标所指位置的坐标
		str.Format("x=%d,y=%d",point.x,point.y);
	else str="NULL";
	pStatusBar->SetPaneText(2,str);

	CGet_RGB t1;
	t1.GetMembers(p_Width,p_Height,p_Bits,p_ByteWidth,lpOut);
	t1.GetRGBValue(point.x,point.y);
	if(pStatusBar && point.x<p_Width && point.y<p_Height)
		str.Format("R=%d ,G= %d,B=%d",t1.red,t1.green,t1.blue);
	else str="R=***,G=***,B=***";
	pStatusBar->SetPaneText(3,str);

	CScrollView::OnMouseMove(nFlags, point);
}

void CPhotoAnalysis2View::OnRgbToHsv() 
{
	// TODO: Add your command handler code here
	//lpOut = new BYTE[p_ByteWidth*p_Height];
    CHSV_RGBDlg t1;
	CDC* pDC =GetDC();
	t1.getmembers(pBIH,pDC->GetSafeHdc(),p_Width,p_Height,p_ByteWidth,lpOut);
	t1.DoModal();
	lpOut=t1.lpOut;
	m=1;
   	Invalidate();
}
void CPhotoAnalysis2View::OnGrayLinarStretch() 
{
	// TODO: Add your command handler code here
	CLinerParaDlg t1;
	CDC* pDC =GetDC();
	t1.getmembers(pBIH,pDC->GetSafeHdc(),p_Width,p_Height,p_ByteWidth,lpOut);       
	t1.DoModal();
	lpOut=t1.lpOut;
	m=1;
    Invalidate();
}

void CPhotoAnalysis2View::OnGrayPiecewise() 
{
	// TODO: Add your command handler code here
	CGrayStretchDlg t1;
	CDC* pDC =GetDC();
	t1.getmembers(pBIH,pDC->GetSafeHdc(),p_Width,p_Height,p_ByteWidth,lpOut);     
	t1.DoModal();
	lpOut=t1.lpOut;
	m=1;
   Invalidate();
}

void CPhotoAnalysis2View::OnThreshold() 
{
	// TODO: Add your command handler code here
	lpOut = new BYTE [p_ByteWidth*p_Height];
	CThreshold t1;
	CDC* pDC =GetDC();
	t1.getmember(pBIH,pDC->GetSafeHdc(),p_Width,p_Height,p_ByteWidth,pBits,lpOut);
	t1.DoModal();
	lpOut=t1.lpOut;
	m=1;
   	Invalidate();
}

void CPhotoAnalysis2View::OnHistogramEqualize() 
{
	// TODO: Add your command handler code here
	CHisEqlize t1;     //调用直方图均衡库中的函数
	t1.HistEq(p_Bits,p_Width,p_Height,p_ByteWidth,lpOut);
	lpOut=t1.lpOut;    //得到直方图均衡后的图像数据区的指针
	m=1;
	Invalidate();
}

void CPhotoAnalysis2View::OnHistogramMatching() 
{
	// TODO: Add your command handler code here
	CHistogramMatchingDlg t1;
	CDC* pDC =GetDC();
	t1.getmembers(pBIH,pDC->GetSafeHdc(),p_Width,p_Height,p_ByteWidth,lpOut);     
	t1.DoModal();
	lpOut=t1.lpOut;
	m=1;
   	Invalidate();
}

void CPhotoAnalysis2View::OnEnhanceMidianfilter() 
{
	// TODO: Add your command handler code here
	CMedianFiltDlg t1;
	if (t1.DoModal() != IDOK || t1.m_iWinSize == 0)
	{
		return;
	}
	t1.getmember(p_Width,p_Height,p_ByteWidth,p_Bits,lpOut);
	int iWinSize = t1.m_iWinSize;
	t1.MedianFilter(iWinSize);
	lpOut=t1.lpOut;
	m=1;
	Invalidate();
}

void CPhotoAnalysis2View::OnEnhanceMaxfilter() 
{
	// TODO: Add your command handler code here
	CMedianFiltDlg t1;
	if (t1.DoModal() != IDOK || t1.m_iWinSize == 0)
	{
		return;
	}
	t1.getmember(p_Width,p_Height,p_ByteWidth,p_Bits,lpOut);
	int iWinSize = t1.m_iWinSize;
	t1.MaxFilter(iWinSize);
	lpOut=t1.lpOut;
	m=1;
	Invalidate();
}

void CPhotoAnalysis2View::OnEnhanceMinfilter() 
{
	// TODO: Add your command handler code here
	CMedianFiltDlg t1;
	if (t1.DoModal() != IDOK || t1.m_iWinSize == 0)
	{
		return;
	}
	t1.getmember(p_Width,p_Height,p_ByteWidth,p_Bits,lpOut);
	int iWinSize = t1.m_iWinSize;
	t1.MinFilter(iWinSize);
	lpOut=t1.lpOut;
	m=1;
	Invalidate();
}

void CPhotoAnalysis2View::OnEnhanceEqualizefilter() 
{
	// TODO: Add your command handler code here
	CMedianFiltDlg t1;
	if (t1.DoModal() != IDOK || t1.m_iWinSize == 0)
	{
		return;
	}
	t1.getmember(p_Width,p_Height,p_ByteWidth,p_Bits,lpOut);
	int iWinSize = t1.m_iWinSize;
	t1.EaualizeFilter(iWinSize);
	lpOut=t1.lpOut;
	m=1;
	Invalidate();
}

void CPhotoAnalysis2View::OnEnhanceSharpeningfilter() 
{
	// TODO: Add your command handler code here
	CSharpeningFilterDlg t1;
	t1.getmember(p_Width,p_Height,p_ByteWidth,p_Bits,lpOut);
	if (t1.DoModal() != IDOK)
	{
		return;
	}
	int* piSharpCoef = new int[9];
	int i = 0 ;
	piSharpCoef[i++] = t1.m_nSharpCoef00;
	piSharpCoef[i++] = t1.m_nSharpCoef01;
	piSharpCoef[i++] = t1.m_nSharpCoef02;
	piSharpCoef[i++] = t1.m_nSharpCoef03;
	piSharpCoef[i++] = t1.m_nSharpCoef04;
	piSharpCoef[i++] = t1.m_nSharpCoef05;
	piSharpCoef[i++] = t1.m_nSharpCoef06;
	piSharpCoef[i++] = t1.m_nSharpCoef07;
	piSharpCoef[i++] = t1.m_nSharpCoef08;
    t1.SharpeningFilter(piSharpCoef);
	lpOut=t1.lpOut;
	m=1;
	Invalidate();
}

void CPhotoAnalysis2View::OnGrayToColor() 
{
	// TODO: Add your command handler code here
	int newByteWidth = p_ByteWidth*3;
	lpOut = new BYTE[p_ByteWidth*p_Height*3];
	//   pNewBIH1 = new BITMAPINFO;
	pNewBIH = pBIH;
	pNewBIH->bmiHeader.biBitCount=24;
	pNewBIH->bmiHeader.biSizeImage =p_ByteWidth*p_Height*3; 
	int R,G,B,i,j;
	
	for(i=0;i<p_Height;i++)
		for(j=0;j<p_Width;j++)
		{
			if(pBits[j+i*p_ByteWidth]<=30)
			{
				R = 0;
				G = (int)8*lpOut[p_ByteWidth*i];
				B = 255;
			}
			if(pBits[j+i*p_ByteWidth] >30 && pBits[j+i*p_ByteWidth]<=50)
			{
				R=0;
				G=255;
				B=(int)8*(128-lpOut[j+i*p_ByteWidth]);
			}
			if(pBits[j+i*p_ByteWidth]>50 && pBits[j+i*p_ByteWidth]<=100)
			{
				R=(int)8*(lpOut[j+i*p_ByteWidth]-128);
				G=255;
				B=0;
			}
			if(pBits[j+i*p_ByteWidth]>100 && pBits[j+i*p_ByteWidth]<=255)
			{
				R=255;
				G=(int)8*(255-lpOut[j+i*p_ByteWidth]);
				B=0;
			}
			lpOut[i*newByteWidth+j*3] = B;
			lpOut[i*newByteWidth+j*3+1] = G;
			lpOut[i*newByteWidth+j*3+2] = R;
		} 
		m=1;
Invalidate();
}
void CPhotoAnalysis2View::OnColorToGray()
{
	if(p_Bits==8)
	{
		return;
	}
//	RGBQUAD *rgbquad=NULL;
//	rgbquad= new RGBQUAD[256];
//	for(int i = 0;i < 256;i++) 
//	{ 
	//	rgbquad[i].rgbRed  = i; 
//		rgbquad[i].rgbGreen = i; 
	//	rgbquad[i].rgbBlue  = i; 
	//	rgbquad[i].rgbReserved = 0; 
	//	} 
   // pBFH->bfSize = sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER) + 256 * sizeof(RGBQUAD) + p_Width*p_Height;  
//	pBFH->bfOffBits = 54+1024;  
	//	int newByteWidth= p_ByteWidth/3;
	//	pBIH->bmiHeader.biBitCount=8;
	//	pBIH->bmiHeader.biSizeImage =(p_Width+3)/4*4;	
	lpOut = new BYTE [p_ByteWidth*p_Height];
	for(int i=0;i<p_Height;i++)
		for(int j=0;j<p_Width;j++)
		{
			lpOut[i*p_ByteWidth+3*j] = min(255,max(0,(int)(0.299*pBits[i*p_Width*3+3*j+2]+0.587*pBits[i*p_Width*3+3*j+1]+0.114*pBits[i*p_Width*3+3*j])));
			lpOut[i*p_ByteWidth+j*3+1] = min(255,max(0,(int)(0.299*pBits[i*p_Width*3+3*j+2]+0.587*pBits[i*p_Width*3+3*j+1]+0.114*pBits[i*p_Width*3+3*j])));
			lpOut[i*p_ByteWidth+3*j+2] = min(255,max(0,(int)(0.299*pBits[i*p_Width*3+3*j+2]+0.587*pBits[i*p_Width*3+3*j+1]+0.114*pBits[i*p_Width*3+3*j])));
		}
		m=1;
		Invalidate();
}

void CPhotoAnalysis2View::OnTransformMirrorX() 
{
	// TODO: Add your command handler code here
	CMirrorTransform t1;
	t1.getmember(p_Width,p_Height,p_ByteWidth,p_Bits,lpOut);
	int nDircFlag = 0;
	t1.Mirror(nDircFlag);
	lpOut=t1.lpOut;
	m=1;
	Invalidate();
}

void CPhotoAnalysis2View::OnTransformMirrorY() 
{
	// TODO: Add your command handler code here
	CMirrorTransform t1;
	t1.getmember(p_Width,p_Height,p_ByteWidth,p_Bits,lpOut);
	int nDircFlag = 1;
	t1.Mirror(nDircFlag);
	lpOut=t1.lpOut;
	m=1;
	Invalidate();
}

void CPhotoAnalysis2View::OnZoom() 
{
	// TODO: Add your command handler code here
	int newByteWidth=0;
	CZoomDlg t1;
	CDC* pDC =GetDC();
	t1.getmembers(pBIH,pDC->GetSafeHdc(),p_Width,p_Height,p_ByteWidth,lpOut);  
    if(t1.DoModal()!=IDOK) return;
	p_Height=t1.GetH();
	p_Width = t1.GetW();
	pBIH->bmiHeader.biSizeImage = newByteWidth * p_Height;
    pBIH->bmiHeader.biWidth =p_Width;
    pBIH->bmiHeader.biHeight = p_Height;
	newByteWidth = p_Bits/8*p_Width;
	lpOut=new BYTE[newByteWidth*p_Height];
	lpOut=t1.lpOut;
	m=1;
	Invalidate();
}

void CPhotoAnalysis2View::OnFft() 
{
	// TODO: Add your command handler code here
	int n=2,mm=1;
	double nn[3];
	double *fftSrc;
	fftSrc = new double [p_Height*p_ByteWidth*2+1];
	nn[1] = p_Height;
	nn[2] = p_ByteWidth;
	fourn(fftSrc,nn,n,mm);
	memcpy(lpOut,fftSrc,p_ByteWidth*p_Height);
	//对图像进行FFT
	//由于不会操作移中，所以显示有问题。
	m=1;
	Invalidate();
}

void CPhotoAnalysis2View::OnIfft() 
{
	// TODO: Add your command handler code here
	int n=2,mm=-1;
	double nn[3];
	double *fftSrc;
	fftSrc = new double [p_Height*p_ByteWidth*2+1];
	nn[1] = p_Height;
	nn[2] = p_ByteWidth;
	fourn(fftSrc,nn,n,mm);
	memcpy(lpOut,fftSrc,p_ByteWidth*p_Height);
	//对图像进行FFT
	int max;
	max = lpOut[0];
	int tmp;
	for(int i=0;i<p_ByteWidth*p_Height;i++)
	{
		if(max<lpOut[i])
			max=lpOut[i];
	}
	for(i=0;i<p_ByteWidth*p_Height;i++)
	{
		tmp=lpOut[i];
		lpOut[i]=255*tmp/max;
	}
	m=1;
	Invalidate();
}

void CPhotoAnalysis2View::OnImageCal() 
{
	// TODO: Add your command handler code here
	CLOGIC_CAL t1;
	CDC* pDC =GetDC();
	t1.getmembers(pBIH,pDC->GetSafeHdc(),p_Width,p_Height,p_ByteWidth,lpOut);  
	t1.opentemp();
	t1.DoModal();
	lpOut=t1.lpOut;
	m=1;
	Invalidate();
}

void CPhotoAnalysis2View::OnIdealLpf() 
{
	// TODO: Add your command handler code here
	CIdealFilter t1;
	if (t1.DoModal()==IDOK)
	{
		t1.GetMembers(p_ByteWidth,p_Height,p_Bits,p_Width,lpOut);
		t1.IdealLowPassFilter();
		lpOut=t1.m_lpOut;
	}	
	m=1;
	Invalidate();
}

void CPhotoAnalysis2View::OnIdealHpf() 
{
	// TODO: Add your command handler code here
	CIdealFilter t1;
	if (t1.DoModal()==IDOK)
	{
		t1.GetMembers(p_ByteWidth,p_Height,p_Bits,p_Width,lpOut);
		t1.IdealHighPassFilter();
		lpOut=t1.m_lpOut;
	}	
	m=1;
	Invalidate();
}

void CPhotoAnalysis2View::OnButterLpf() 
{
	// TODO: Add your command handler code here
	CButterworthFilter t1;
	if (t1.DoModal()==IDOK)
	{
		t1.GetMembers(p_ByteWidth,p_Height,p_Bits,p_Width,lpOut);
		t1.ButterWorthLowPassFilter();
		lpOut=t1.m_lpOut;
	}	
	m=1;
	Invalidate();
}

void CPhotoAnalysis2View::OnButterHpf() 
{
	// TODO: Add your command handler code here
	CButterworthFilter t1;
	if (t1.DoModal()==IDOK)
	{
		t1.GetMembers(p_ByteWidth,p_Height,p_Bits,p_Width,lpOut);
		t1.ButterWorthHighPassFilter();
		lpOut=t1.m_lpOut;
	}	
	m=1;
	Invalidate();	
}

void CPhotoAnalysis2View::OnHomomorphicFilter() 
{
	// TODO: Add your command handler code here
	CHomomorphicFilter t1;
	if (t1.DoModal()==IDOK)
	{
		t1.GetMembers(p_ByteWidth,p_Height,p_Bits,p_Width,lpOut);
		t1.HomomorphicFilter();
		lpOut=t1.m_lpOut;
	}
	m=1;
	Invalidate();
}

void CPhotoAnalysis2View::OnInverseFilter() 
{
	// TODO: Add your command handler code here
	CInverseFilterRadius t;
	if (t.DoModal()==IDOK)
	{
		t.GetMembers(p_ByteWidth,p_Height,p_Bits,p_Width,lpOut,DFlag);
		if (t.InverseFilterAtmoTurb(temp)==TRUE)
			lpOut=t.m_lpOut;		
	}
	DFlag=0;
	m=1;
	Invalidate();
}

void CPhotoAnalysis2View::OnDegenerate() 
{
	// TODO: Add your command handler code here
	CDegenerateModel t;
	if (t.DoModal()==IDOK)
	{
		t.GetMembers(p_ByteWidth,p_Height,p_Bits,p_Width,lpOut);
		t.Degenerate();
		lpOut=t.m_lpOut;
		temp=t.m_fAtmosTurbPara_k;
	}
	DFlag=1;
	m=1;
	Invalidate();
}
void CPhotoAnalysis2View::OnMenuitem32807() 
{
	//维纳滤波
	// TODO: Add your command handler code here
	//用于做FFT的数组
	double *fftSrc,*fftKernel,*fftNoise;
	double a,b,c,d,e,f,multi;
	//二维FFT的长度和宽度
	double nn[3];
	//图像归一化因子
	double MaxNum;
	double dPower = log((double)p_ByteWidth)/log(2.0);
	if(dPower != (int) dPower)
	{
		return ;
	}
	dPower = log((double)p_Height)/log(2.0);
	if(dPower != (int) dPower)
	{
		return ;
	}
	fftSrc = new double [p_Height*p_ByteWidth*2+1];
	fftKernel = new double [p_Height*p_ByteWidth*2+1];
	fftNoise = new double [p_Height*p_ByteWidth*2+1];
	nn[1] = p_Height;
	nn[2] = p_ByteWidth;
	int i,j;
	for (j = 0;j < p_Height ;j++)
	{
		for(i = 0;i < p_ByteWidth ;i++)
		{
			// 指向源图像倒数第j行，第i个象素的指针			
			fftSrc[(2*p_ByteWidth)*j + 2*i + 1] = (double)pBits[j*p_ByteWidth+j];
			fftSrc[(2*p_ByteWidth)*j + 2*i + 2] = 0.0;
			
			if(i < 5 && j == 0)
			{
				fftKernel[(2*p_ByteWidth)*j + 2*i + 1] = 1/5.0;
			}
			else
			{
				fftKernel[(2*p_ByteWidth)*j + 2*i + 1] = 0.0;
			}
			fftKernel[(2*p_ByteWidth)*j + 2*i + 2] = 0.0;
			if ( i + j == ((int)((i+j)/8))*8)
			{
				fftNoise [(2*p_ByteWidth)*j + 2*i + 1]= -16.0;
			}
			else
			{
				fftNoise [(2*p_ByteWidth)*j + 2*i + 1]= 0.0;
			}
			fftNoise[(2*p_ByteWidth)*j + 2*i + 2] = 0.0;
		}
	}
	srand((unsigned)time(NULL));
	//对源图像进行FFT
	int n=2,m1=1,m2=-1;
	fourn(fftSrc,nn,n,m1);
	//对卷积核图像进行FFT
	fourn(fftKernel,nn,n,m1);
	//对噪声图像进行FFT
	fourn(fftNoise,nn,n,m1);
	for (i = 1;i <p_Height*p_ByteWidth*2;i+=2)
	{
		a = fftSrc[i];
		b = fftSrc[i+1];
		c = fftKernel[i];
		d = fftKernel[i+1];
		e = fftNoise[i];
		f = fftNoise[i+1];
		multi = (a*a + b*b)/(a*a + b*b - e*e - f*f);
		if (c*c + d*d > 1e-3)
		{
			fftSrc[i] = ( a*c + b*d ) / ( c*c + d*d ) / multi;
			fftSrc[i+1] = ( b*c - a*d ) / ( c*c + d*d )/multi;
		}
	}
	//对结果图像进行反FFT
	fourn(fftSrc,nn,n,m2);
	
	//确定归一化因子
	MaxNum = 0.0;
	for (j = 0;j < p_Height ;j++)
	{
		for(i = 0;i < p_ByteWidth ;i++)
		{
			fftSrc[(2*p_ByteWidth)*j + 2*i + 1] = 
				sqrt(fftSrc[(2*p_ByteWidth)*j + 2*i + 1] * fftSrc[(2*p_ByteWidth)*j + 2*i + 1]\
				+fftSrc[(2*p_ByteWidth)*j + 2*i + 2] * fftSrc[(2*p_ByteWidth)*j + 2*i + 2]);
			if( MaxNum < fftSrc[(2*p_ByteWidth)*j + 2*i + 1])
				MaxNum = fftSrc[(2*p_ByteWidth)*j + 2*i + 1];
		}
	}
	
	//转换为图像
	for (j = 0;j < p_Height ;j++)
	{
		for(i = 0;i < p_ByteWidth ;i++)
		{
			// 指向源图像倒数第j行，第i个象素的指针			
			
			lpOut[j*p_ByteWidth+i] = (unsigned char) (fftSrc[(2*p_ByteWidth)*j + 2*i + 1]*255.0/MaxNum );
		}
	}
	
	delete fftSrc;
	delete fftKernel;
	delete fftNoise;
	m=1;
	Invalidate();
}
void fourn(double data[],double nn[],int &ndim,int &isign)
{
	int ntot,idim,i1,i2,i3,i2rev,i3rev,k1,k2,nprev,n;
	double nrem,ip3,tempr,tempi,ibit,ip1,ip2,wi,wr,wpi,wpr;
	double ifp1,ifp2,wtemp,theta;
    ntot = 1;
    for (idim = 1; idim<=ndim; idim++)
	{
        ntot = ntot * nn[idim];
	}
    nprev = 1;
    for (idim = 1; idim<=ndim; idim++)
	{
        n = nn[idim];
        nrem = ntot / (n * nprev);
        ip1 = 2 * nprev;
        ip2 = ip1 * n;
        ip3 = ip2 * nrem;
        i2rev = 1;
        for (i2 = 1; i2<=ip2; i2+=ip1)
		{
            if( i2 < i2rev)
			{
                for (i1 = i2; i1<=i2 + ip1 - 2; i1+=2)
				{
                    for (i3 = i1;i3<=ip3;i3+=ip2)
					{
                        i3rev = i2rev + i3 - i2;
                        tempr = data[i3];
                        tempi = data[i3 + 1];
                        data[i3] = data[i3rev];
                        data[i3 + 1] = data[i3rev + 1];
                        data[i3rev] = tempr;
                        data[i3rev + 1] = tempi;
                    }
                }
            }
            ibit = ip2 / 2;
yi:         if( ibit >= ip1 && i2rev > ibit)
			{
                i2rev = i2rev - ibit;
                ibit = ibit / 2;
                goto yi;
			}
            i2rev = i2rev + ibit;
        }
        ifp1 = ip1;
er:     if (ifp1 < ip2)
		{
            ifp2 = 2 * ifp1;
            theta = isign * 6.28318530717959 / (ifp2 / ip1);
            wpr = -2.0 * (sin(0.5 * theta))*(sin(0.5 * theta));
            wpi = sin(theta);
            wr = 1.0;
            wi = 0.0;
            for (i3 = 1; i3<=ifp1; i3+=ip1)
			{
				for (i1 = i3;i1<=i3 + ip1 - 2;i1+=2)
				{
					for(i2 = i1; i2<=ip3; i2+=ifp2)
					{
						k1 = i2;
						k2 = k1 + ifp1;
						tempr=float(wr)*data[k2]-float(wi)*data[k2+1];
						tempi=float(wr)*data[k2+1]+float(wi)*data[k2];
						data[k2] = data[k1] - tempr;
						data[k2 + 1] = data[k1 + 1] - tempi;
						data[k1] = data[k1] + tempr;
						data[k1 + 1] = data[k1 + 1] + tempi;
					}
				}
				wtemp = wr;
				wr = wr * wpr - wi * wpi + wr;
				wi = wi * wpr + wtemp * wpi + wi;
            }
            ifp1 = ifp2;
            goto er;
		}
        nprev = n * nprev;
	}
}
void CPhotoAnalysis2View::OnInverse() 
{
	// TODO: Add your command handler code here
	int temp;
	for(int i=0;i<p_ByteWidth*p_Height;i++)
	{
		temp=(int)lpOut[i];
		lpOut[i]=(BYTE)(255-temp);
	}
	m=1;
	Invalidate();
}

void CPhotoAnalysis2View::OnAndor() 
{
	// TODO: Add your command handler code here

}

void CPhotoAnalysis2View::OnLogicAnd() 
{
	// TODO: Add your command handler code here
	
}

void CPhotoAnalysis2View::OnMorphology() 
{
	// TODO: Add your command handler code here
	CMorPhologyDlg t1;
	CDC* pDC =GetDC();
	t1.getmember(pBIH,pDC->GetSafeHdc(),p_Width,p_Height,p_ByteWidth,pBits,lpOut);
	t1.lpOut=lpOut;
	t1.lpBits=lpOut;
	t1.DoModal();
	lpOut=t1.lpOut;
	m=1;
   	Invalidate();
}

void CPhotoAnalysis2View::OnRegionGrow() 
{
	// TODO: Add your command handler code here
    CREGIONGROWTH m_DlgRegGrow;
	CDC* pDC =GetDC();
	m_DlgRegGrow.getmember(pBIH,pDC->GetSafeHdc(),p_Width,p_Height,p_ByteWidth,pBits,lpOut);
//	m_DlgRegGrow.lpbits_trans = lpOut;
//	m_DlgRegGrow.lpbits = lpOut;
	//创建对话框
//	if(m_DlgRegGrow.DoModal()==IDOK)
	//	lpOut=m_DlgRegGrow.lpbits_trans;
	m_DlgRegGrow.DoModal();
//	m=1;
//	Invalidate();
}

void CPhotoAnalysis2View::OnRegionDivandcon() 
{
	// TODO: Add your command handler code here
	//lpbits_trans = new BYTE[bm.bmHeight*bm.bmWidth];
	//memcpy(lpbits_trans,lpbits,sizeof(BYTE)*bm.bmHeight*bm.bmWidth);
	//分裂合并 一分为四
	CRect region1(0,0,p_Height/2-1,p_Width/2-1);
	CRect region2(0,p_Width/2,p_Height/2-1,p_Width-1);
	CRect region3(p_Height/2,0,p_Height-1,p_Width/2-1);
	CRect region4(p_Height/2,p_Width/2,p_Height-1,p_Width-1);
	MySpliting(lpOut,region1,p_Width);
	MySpliting(lpOut,region2,p_Width);
	MySpliting(lpOut,region3,p_Width);
	MySpliting(lpOut,region4,p_Width);
	Invalidate();
}
void CPhotoAnalysis2View::MySpliting(BYTE *input,CRect region,int p_Width)
{
	double sum = 0;
	double AveGrey,StdVarGrey;	
	int x,y;
	if (region.Width()==0 || region.Height()==0)
	{
		//求平均灰度
		for(y=region.top;y<=region.bottom;y++)
		{
			for(x=region.left;x<=region.right;x++)
			{
				sum += double(input[x+y*p_Width]);
			}
		}
		AveGrey = sum/((region.Height()+1)*(region.Width()+1));
		for(y=region.top;y<=region.bottom;y++)
		{
			for(x=region.left;x<=region.right;x++)
			{
				input[x+y*p_Width] = BYTE(AveGrey);
			}
		}
		return;
	}
	else
	{
		//求平均灰度
		for(y=region.top;y<=region.bottom;y++)
		{
			for(x=region.left;x<=region.right;x++)
			{
				sum += double(input[x+y*p_Width]);
			}
		}
		AveGrey = sum/((region.Height()+1)*(region.Width()+1));
		//求灰度标准方差
		sum = 0;
		for(y=region.top;y<=region.bottom;y++)
		{
			for(x=region.left;x<=region.right;x++)
			{
				sum += pow((double(input[x+y*p_Width])-AveGrey),2)
					/((region.Height()+1)*(region.Width()+1));
			}
		}
		StdVarGrey = sqrt(sum);
		//求终止条件
		sum = 0;
		for(y=region.top;y<=region.bottom;y++)
		{
			for(x=region.left;x<=region.right;x++)
			{
				if (fabs(double(input[x+y*p_Width])-AveGrey) <= StdVarGrey)
				{
					sum++;
				}
			}
		}
		//如果70%的点满足条件，则将此区域灰度全部置为平均灰度；否则，分裂为4块
		if (sum > 0.70*(region.Height()+1)*(region.Width()+1))
		{
			for(y=region.top;y<=region.bottom;y++)
			{
				for(x=region.left;x<=region.right;x++)
				{
					input[x+y*p_Width] = BYTE(AveGrey);
				}
			}
		}
		else
		{
			//左上
			CRect region1(region.left,region.top,
				region.left+(region.Width()-1)/2,region.top+(region.Height()-1)/2);
			MySpliting(input,region1,p_Width);
			//右上
			CRect region2(region.left+(region.Width()-1)/2+1,region.top,
				region.right,region.top+(region.Height()-1)/2);
			MySpliting(input,region2,p_Width);
			//左下
			CRect region3(region.left,region.top+(region.Height()-1)/2,
				region.left+(region.Width()-1)/2,region.bottom);
			MySpliting(input,region3,p_Width);
			//右下
			CRect region4(region.left+(region.Width()-1)/2+1,region.top+(region.Height()-1)/2+1,
				region.right,region.bottom);
			MySpliting(input,region4,p_Width);
			//		MySpliting(input,region,bm);
		}
	}
}

void CPhotoAnalysis2View::OnFileSaveAs() 
{
	// TODO: Add your command handler code here
	if(pBits!=NULL)
	{
		CFileDialog dlg(FALSE, "*.BMP", "Output.bmp", NULL,"位图文件(*.BMP)|*.bmp;*.BMP|");
		CString filepath("");
		if (dlg.DoModal()==IDOK)
		{
			filepath = dlg.GetPathName();
			HDC m_hScrDC = GetDC()->GetSafeHdc();
			HDC m_hMemDC = CreateCompatibleDC(m_hScrDC);
			LPRECT lp = new RECT;
			POINT pt;
			//	GetClientRect(lp);
			lp->left = 0;
			lp->top = 0;
			lp->right = p_Width;
			lp->bottom = p_Height;
			pt.x = 1*(lp->right - lp->left);
			pt.y = 1*(lp->bottom - lp->top);
			HBITMAP m_hBitmap = CreateCompatibleBitmap(m_hScrDC, pt.x, pt.y);
			HBITMAP m_hOldBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hBitmap);
			BitBlt(m_hMemDC, p_Width, p_Height, p_Width, p_Height, m_hScrDC, 0, 0, SRCCOPY);
			m_hBitmap = (HBITMAP)SelectObject(m_hMemDC, m_hOldBitmap);
			
			//	CString filepath = filepath.Left(filepath.Find(".")+1) + "bmp";
			SaveBitMapToFile(m_hBitmap, filepath);
			DeleteObject(lp);
		}
	}
}
BOOL CPhotoAnalysis2View::SaveBitMapToFile(HBITMAP hBitmap, CString lpFileName)
{
	//保存结果图像
    HDC        hDC;        //设备描述表       
    int        iBits;        //当前显示分辨率下每个像素所占字节数   
    WORD    wBitCount;    //位图中每个像素所占字节数   
    DWORD    dwPaletteSize=0,//定义调色板大小，位图中像素字节大小，位图文件大小，写入文件字节数
        dwBmBitsSize,
        dwDIBSize,
        dwWritten;
    BITMAP    Bitmap;      
    BITMAPFILEHEADER    bmfHdr;    //位图属性结构
    BITMAPINFOHEADER    bi;        //位图文件头结构                
    LPBITMAPINFOHEADER    lpbi;    //位图信息头结构           
    HANDLE    fh,   hDib,   hPal,hOldPal=NULL;//指向位图信息头结构,定义文件，分配内存句柄，调色板句柄
    //计算位图文件每个像素所占字节数   
    hDC = CreateDC("DISPLAY",NULL,NULL,NULL);   
    iBits = GetDeviceCaps(hDC,BITSPIXEL)*GetDeviceCaps(hDC,PLANES);   
    DeleteDC(hDC);
    if(iBits<=1)   
        wBitCount = 1;   
    else if(iBits<=4)   
        wBitCount = 4;   
    else if(iBits<=8)   
        wBitCount = 8;
    else if(iBits<=24)   
        wBitCount = 24;
    else
        wBitCount = 32;
    //计算调色板大小   
    if(wBitCount<=8)   
        dwPaletteSize = (1<<wBitCount)*sizeof(RGBQUAD);   
     
    //设置位图信息头结构
    GetObject(hBitmap, sizeof(BITMAP), (LPSTR)&Bitmap);   
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = Bitmap.bmWidth;   
    bi.biHeight = Bitmap.bmHeight;   
    bi.biPlanes = 1;   
    bi.biBitCount = wBitCount;   
    bi.biCompression = BI_RGB;   
    bi.biSizeImage = 0;   
    bi.biXPelsPerMeter = 0;   
    bi.biYPelsPerMeter = 0;   
    bi.biClrUsed = 0;   
    bi.biClrImportant = 0;   
     
    dwBmBitsSize = ((Bitmap.bmWidth*wBitCount+31)/32)*4*Bitmap.bmHeight;   
     
    //为位图内容分配内存   
    hDib = GlobalAlloc(GHND,dwBmBitsSize+dwPaletteSize+sizeof(BITMAPINFOHEADER));   
    lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDib);   
    *lpbi = bi;   
     
    //   处理调色板         
    hPal = GetStockObject(DEFAULT_PALETTE);   
    if(hPal)
    {   
        hDC = ::GetDC(NULL);   
        hOldPal = SelectPalette(hDC, (HPALETTE)hPal, FALSE);   
        RealizePalette(hDC);  
    }   
     
    //   获取该调色板下新的像素值   
    GetDIBits(hDC, hBitmap, 0, (UINT)Bitmap.bmHeight,
        (LPSTR)lpbi+sizeof(BITMAPINFOHEADER)+dwPaletteSize,
        (LPBITMAPINFO)lpbi,DIB_RGB_COLORS);   
     
    //恢复调色板         
    if(hOldPal)
    {
        SelectPalette(hDC,(HPALETTE)hOldPal,TRUE);
        RealizePalette(hDC);
        ::ReleaseDC(NULL, hDC);
    }   
     
    //创建位图文件           
    fh = CreateFile(lpFileName,GENERIC_WRITE,0,NULL,CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL|FILE_FLAG_SEQUENTIAL_SCAN,NULL);
     
    if(fh==INVALID_HANDLE_VALUE)
        return   FALSE;
     
    //   设置位图文件头   
    bmfHdr.bfType = 0x4D42;//   "BM"   
    dwDIBSize = sizeof(BITMAPFILEHEADER)+
        sizeof(BITMAPINFOHEADER)+
        dwPaletteSize+dwBmBitsSize;
    bmfHdr.bfSize = dwDIBSize;
    bmfHdr.bfReserved1 = 0;
    bmfHdr.bfReserved2 = 0;
    bmfHdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER)+
        (DWORD)sizeof(BITMAPINFOHEADER)+dwPaletteSize;
     
    //   写入位图文件头
    WriteFile(fh,(LPSTR)&bmfHdr,sizeof(BITMAPFILEHEADER),&dwWritten,NULL);
    //   写入位图文件其余内容
    WriteFile(fh,(LPSTR)lpbi,dwDIBSize,&dwWritten,NULL);
     
    //消除内存分配
    GlobalUnlock(hDib);
    GlobalFree(hDib);
    CloseHandle(fh);
    return   TRUE;
}
