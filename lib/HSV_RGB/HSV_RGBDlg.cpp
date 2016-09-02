// HSV_RGBDlg.cpp : implementation file
//

#include "stdafx.h"
//#include "	\ add additional includes here"
#include "HSV_RGBDlg.h"
#include "math.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CHSV_RGBDlg dialog


CHSV_RGBDlg::CHSV_RGBDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CHSV_RGBDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHSV_RGBDlg)
	//}}AFX_DATA_INIT
}


void CHSV_RGBDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHSV_RGBDlg)
	DDX_Control(pDX, IDC_STATIC_V, m_nV);
	DDX_Control(pDX, IDC_STATIC_S, m_nS);
	DDX_Control(pDX, IDC_STATIC_H, m_nH);
	DDX_Control(pDX, IDC_SLIDER_V, m_cV);
	DDX_Control(pDX, IDC_SLIDER_S, m_cS);
	DDX_Control(pDX, IDC_SLIDER_H, m_cH);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHSV_RGBDlg, CDialog)
	//{{AFX_MSG_MAP(CHSV_RGBDlg)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_V, OnReleasedcaptureSliderV)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_S, OnReleasedcaptureSliderS)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_H, OnReleasedcaptureSliderH)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHSV_RGBDlg message handlers
int p_ByteWidth,p_Bits;
BYTE *lpBits;	BITMAPINFO *pBIH;
HDC T1;
    int p_Width,p_Height;
void CHSV_RGBDlg::getmembers(BITMAPINFO *m_pBIH,HDC t1,int m_nWidth,int m_nHeight,int m_nByteWidth,BYTE* m_lpOut)
{
	p_Width = m_nWidth;
	p_Height = m_nHeight;
	p_ByteWidth = m_nByteWidth;
	p_Bits = m_nByteWidth/m_nWidth*8;
	lpBits = m_lpOut;
	lpOut=m_lpOut;
	T1=t1;
	pBIH=m_pBIH;
}
void CHSV_RGBDlg::getRGB(float &R,float &G,float &B,int i,int j)
{
//	float sum;
	switch(p_Bits)
	{
	case 8:	R = lpBits[i*p_ByteWidth+j];
			G = lpBits[i*p_ByteWidth+j];
			B = lpBits[i*p_ByteWidth+j];
			break;
	case 24:B = lpBits[i*p_ByteWidth+j*3];
			G = lpBits[i*p_ByteWidth+j*3+1];
			R = lpBits[i*p_ByteWidth+j*3+2];
			break;
	}
//	sum = B+R+G;
//	R /= sum;
//	G /= sum;
//	B /= sum;
	R /= 255;
	G /= 255;
	B /= 255;
}

void CHSV_RGBDlg::Hsv2Rgb(float H, float S, float V, float &R, float &G, float &B)
{
	int i;
    float  p, f, q, t;
	H*=360;
	if( S == 0 ) 	
    {
		// achromatic (grey)
		R = G = B = V;
		return;
    }
    i = floor( H/60 );
    f = H/60-i; // factorial part of h
	p = V * ( 1 - S );
	q = V * ( 1 - S * f );
	t = V * ( 1 - S * ( 1 - f ) );
	switch( i )
	{	
    case 0: 
		R = V;
		G = t;
		B = p;
		break;
    case 1:
		R = q;
		G = V;
		B = p;
		break;	
    case 2:
		R = p;
		G = V;	
		B = t;
		break;
    case 3:
		R = p;
		G = q;
		B = V;
		break;
    case 4:
		R = t;
		G = p;
		B = V;
		break;
    default: // case 5:
		R = V;
		G = p;
		B = q;
		break;
    }
}
void CHSV_RGBDlg::Rgb2Hsv(float R, float G, float B, float& H, float& S, float&V)
{
	float min, max, delta,tmp;
    tmp = min(R, G);
    min = min( tmp, B );
    tmp = max( R, G);
    max = max(tmp, B );
    V = max; // v
//	float r,g,b;
	delta = max - min;
    if( max != 0 )
	{
		S = delta / max; // s
	//	r = (V - R)/delta;
	//	g = (V - G)/delta;
	//	b = (V - B)/delta;
		if(V == R)
		{
			if(B == min)
				H = 60*(G-B)/delta;
			else if(G == min)
				H = 360+60*(G-B)/delta;
		}
		else if(V == G)
		{
			H = 120+60*(B-R)/delta;
		}
		else if(V == B)
		{
			H = 240+60*(R-G)/delta;
		}
	}
    else	
    {
		// r = g = b = 0 // s = 0, v is undefined
		S = 0;
		H = 0;
		return;	
    }
	H/=360;
}

void CHSV_RGBDlg::RGBTrans(float &R,float &G,float &B,int i,int j)
{
	switch(p_Bits)
	{
	case 8:	lpOut[i*p_ByteWidth+j]=min(R*255*v*2,255);
	        break;
	case 24:R = R*255+0.5;
		    G = G*255+0.5;
			B = B*255+0.5;
			lpOut[i*p_ByteWidth+j*3]=(int)B;
			lpOut[i*p_ByteWidth+j*3+1]=(int)G;
			lpOut[i*p_ByteWidth+j*3+2]=(int)R;
			break;
	}
}
void CHSV_RGBDlg::RGB_HSV()
{
	lpOut = new BYTE[p_Height*p_ByteWidth];
	float R,G,B,H,S,V;
	for (int i=0;i<p_Height;i++)
		for(int j=0;j<p_Width;j++)
		{
			getRGB(R,G,B,i,j);
			Rgb2Hsv(R,G,B,H,S,V);
			H=min(1,H*h*2);
			S=min(1,S*s*2);
			V=min(1,V*v*2);
			if(p_ByteWidth/p_Width==3)
			Hsv2Rgb(H,S,V,R,G,B);
			RGBTrans(R,G,B,i,j);
		}
}
BOOL CHSV_RGBDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_cH.SetRange(0,100);
	m_cH.SetPos(50);
	h = m_cH.GetPos()/100.0;
	CString Info;
	Info.Format("%f",h);
	m_nH.SetWindowText(Info);
	
	m_cS.SetRange(0,100);
	m_cS.SetPos(50);
	s = m_cS.GetPos()/100.0;
	//	CString Info;
	Info.Format("%f",s);
	m_nS.SetWindowText(Info);
	
	m_cV.SetRange(0,100);
	m_cV.SetPos(50);
	v = m_cV.GetPos()/100.0;
	//	CString Info;
	Info.Format("%f",v);
	m_nV.SetWindowText(Info);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CHSV_RGBDlg::OnReleasedcaptureSliderV(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CString Info;
	v = m_cV.GetPos()/100.0;
	UpdateData();
	Info.Format("%f",v);
	m_nV.SetWindowText(Info);
	RGB_HSV();
	StretchDIBits(T1,0,0,p_Width,p_Height,0,0,p_Width, p_Height,lpOut,pBIH,DIB_RGB_COLORS,SRCCOPY);
	*pResult = 0;
}

void CHSV_RGBDlg::OnReleasedcaptureSliderS(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	CString Info;
	s = m_cS.GetPos()/100.0;
	UpdateData();
	Info.Format("%f",s);
	m_nS.SetWindowText(Info);
	RGB_HSV();
	StretchDIBits(T1,0,0,p_Width,p_Height,0,0,p_Width, p_Height,lpOut,pBIH,DIB_RGB_COLORS,SRCCOPY);
	*pResult = 0;
}

void CHSV_RGBDlg::OnReleasedcaptureSliderH(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	h = m_cH.GetPos()/100.0;
	UpdateData();
	CString Info;
	Info.Format("%f",h);
	m_nH.SetWindowText(Info);
	RGB_HSV();
	StretchDIBits(T1,0,0,p_Width,p_Height,0,0,p_Width, p_Height,lpOut,pBIH,DIB_RGB_COLORS,SRCCOPY);
	*pResult = 0;
}
