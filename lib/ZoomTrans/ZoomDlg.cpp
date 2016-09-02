// ZoomDlg.cpp : implementation file
//

#include "stdafx.h"
//#include "	\ add additional includes here"
#include "ZoomDlg.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CZoomDlg dialog

int p_ByteWidth,p_Bits;
BYTE *lpBits;	BITMAPINFO *pBIH;
HDC T1;
int p_Width,p_Height;int m_Color;
void CZoomDlg::getmembers(BITMAPINFO *m_pBIH,HDC t1,int m_nWidth,int m_nHeight,int m_nByteWidth,BYTE* m_lpOut)
{
	p_Width = m_nWidth;
	p_Height = m_nHeight;
	p_ByteWidth = m_nByteWidth;
	p_Bits = m_nByteWidth/m_nWidth*8;
	lpBits = m_lpOut;
	lpOut=m_lpOut;
	T1=t1;
	pBIH=m_pBIH;
	m_Color=p_Bits/8;
}
CZoomDlg::CZoomDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CZoomDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CZoomDlg)
	m_bWHScale = FALSE;
	m_fDH = 0;
	m_fDW = 0;
	//}}AFX_DATA_INIT
}


void CZoomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CZoomDlg)
	DDX_Control(pDX, IDC_COMBO_Method, m_Method);
	DDX_Control(pDX, IDC_EDIT_DW, m_cDW);
	DDX_Control(pDX, IDC_EDIT_DH, m_cDH);
	DDX_Check(pDX, IDC_CHECK_REALATE, m_bWHScale);
	DDX_Text(pDX, IDC_EDIT_DH, m_fDH);
	DDX_Text(pDX, IDC_EDIT_DW, m_fDW);
	DDX_Text(pDX, IDC_EDIT_OH, m_fOH);
	DDX_Text(pDX, IDC_EDIT_OW, m_fOW);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CZoomDlg, CDialog)
	//{{AFX_MSG_MAP(CZoomDlg)
	ON_BN_CLICKED(IDC_CHECK_REALATE, OnCheckRealate)
	ON_CBN_SELCHANGE(IDC_COMBO_Method, OnSelchangeCOMBOMethod)
	ON_EN_CHANGE(IDC_EDIT_DH, OnChangeEditDh)
	ON_EN_CHANGE(IDC_EDIT_DW, OnChangeEditDw)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CZoomDlg message handlers

void CZoomDlg::OnCheckRealate() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if(m_bWHScale)
	{
		OnChangeEditDh();
	}
	UpdateData(0);
}

void CZoomDlg::OnSelchangeCOMBOMethod() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	UpdateData(0);
}

void CZoomDlg::OnChangeEditDh() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	if(m_bWHScale)
	{
		
m_fDH=GetDlgItemInt(IDC_EDIT_DH);
		m_fDW=m_fDH*m_fOW/m_fOH;
		UpdateData(0);
	}
}

void CZoomDlg::OnChangeEditDw() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	if(m_bWHScale)
	{
	//	LPTSTR str=new WCHAR[10];
		m_fDW=GetDlgItemInt(IDC_EDIT_DW);
		m_fDH=m_fDW*m_fOH/m_fOW;
		UpdateData(0);
	}
}

int CZoomDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	m_fOW=m_fDW=p_Width;
	m_fDH=m_fOH=p_Height;
	return 0;
}
int CZoomDlg::GetH()
{
	return m_fDH;
}
int CZoomDlg::GetW()
{
	return m_fDW;
}
int CZoomDlg::GetMethod()
{
	int Method=m_Method.GetCurSel();;

	return Method;
}
void CZoomDlg::lpBits_m_RGB()
{
	m_RGB =new BYTE **[m_Color];
	for(int k=0;k<m_Color;k++)	
	{
		m_RGB[k]=new BYTE *[p_Height];
		for(int i=0;i<p_Height;i++)
		{
			m_RGB[k][i]=new BYTE[p_Width];
			for(int j=0;j<p_Width;j++)
			{
				m_RGB[k][i][j]=lpBits[p_ByteWidth*i+m_Color*j+k];
			}
		}
	}
}
void CZoomDlg:: Zoom(int TargetHeight,int TargetWidth,int Method)//图像缩放，三种缩放方式
	//Method：0：near 1：linear 2：cube
{
	unsigned char ***RGB=new unsigned char**[m_Color];
	for(int i=0;i<m_Color;i++)
	{
		RGB[i]=new unsigned char*[TargetHeight];
	}
	for( i=0;i<m_Color;i++)
	{
		for(int j=0;j<TargetHeight;j++)
		{
			RGB[i][j]=new unsigned char[TargetWidth];
		}
	}

	if(Method==0)//邻近
	{
		for(int i=0;i<m_Color;i++)
		{
			for(int j=0;j<TargetHeight;j++)
			{
				for(int k=0;k<TargetWidth;k++)
				{
					*(*(*(RGB+i)+j)+k)=*(*(*(m_RGB+i)+j*p_Height/TargetHeight)+k*p_Width/TargetWidth);
				}//邻近应该不用解释了
			}
		}
	}
	else if(Method==1)//两次线性
	{
		double x,y,fu,fd;
		int x1,y1,x2,y2;
		for(int i=0;i<m_Color;i++)
		{
			for(int j=0;j<TargetHeight;j++)
			{
				for(int k=0;k<TargetWidth;k++)
				{
					x=k*double(p_Width)/TargetWidth;
					y=j*double(p_Height)/TargetHeight;
					x1=x;
					y1=y;
					x2=min(p_Width-1,x1+1);
					y2=min(p_Height-1,y1+1);

					fu=m_RGB[i][y1][x1]+(x-x1)*(m_RGB[i][y1][x2]-m_RGB[i][y1][x1]);
					fd=m_RGB[i][y2][x1]+(x-x1)*(m_RGB[i][y2][x2]-m_RGB[i][y2][x1]);
					*(*(*(RGB+i)+j)+k)=fu+(y-y1)*(fd-fu);
				}//两次线性就是先算一次横向的的比例，再算一次纵向的比例
			}
		}
	}
	else if(Method==2)//两次立方
	{
		int a[5],b[5];
		double A,B,C,D,F[4],deltaA,deltaB;
		for(int i=0;i<m_Color;i++)
		{
			for(int j=0;j<TargetHeight;j++)
			{
				for(int k=0;k<TargetWidth;k++)
				{
					a[4]=j*p_Height/TargetHeight;
					b[4]=k*p_Width/TargetWidth;
					a[1]=max(min(a[4],p_Height-1),0);
					b[1]=max(min(b[4],p_Width-1),0);
					a[2]=min(a[1]+1,p_Height-1);
					b[2]=min(b[1]+1,p_Width-1);
					a[3]=min(a[2]+1,p_Height-1);
					b[3]=min(b[2]+1,p_Width-1);
					a[0]=max(a[1]-1,0);
					b[0]=max(b[1]-1,0);
					deltaA=j*double(p_Height)/TargetHeight-a[4];
					deltaB=k*double(p_Width)/TargetWidth-b[4];

					for(int l=0;l<4;l++)
					{
						D=m_RGB[i][a[l]][b[1]];
						B=double(m_RGB[i][a[l]][b[2]]+m_RGB[i][a[l]][b[0]]-2*D)/2;
						A=double(m_RGB[i][a[l]][b[3]]-2*m_RGB[i][a[l]][b[2]]+D-2*B)/6;
						C=m_RGB[i][a[l]][b[2]]-D-A-B;
						F[l]=A*deltaB*deltaB*deltaB+B*deltaB*deltaB+C*deltaB+D;
					}

					D=F[1];
					B=double(F[2]+F[0]-2*D)/2;
					A=double(F[3]-2*F[2]+D-2*B)/6;
					C=F[2]-A-B-D;
					*(*(*(RGB+i)+j)+k)=min(max(A*deltaA*deltaA*deltaA+B*deltaA*deltaA+C*deltaA+D,0),255);
				}//两次立方直接求两次立方公式，原理与两次线性差不多，不过用到的参数多了
			}
		}
	}
	lpOut = new BYTE [m_Color*m_fDH*m_fDW];
	for( i=0;i<m_Color;i++)
		for(int j=0;j<m_fDH;j++)
			for(int k=0;k<m_fDW;k++)
			{
				lpOut[m_Color*m_fDW*j+m_Color*k+i]=RGB[i][j][k];
			}
}
void CZoomDlg::OnOK() 
{
	// TODO: Add extra validation here
	lpBits_m_RGB();
	Zoom(GetH(),GetW(),GetMethod());
	CDialog::OnOK();
}

BOOL CZoomDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_fOH = p_Height;
	m_fOW = p_Width;
	m_Method.SetCurSel(0);
	m_bWHScale=TRUE;
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
