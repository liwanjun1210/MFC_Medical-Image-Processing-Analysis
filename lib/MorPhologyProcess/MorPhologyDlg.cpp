// MorPhologyDlg.cpp : implementation file
//

#include "stdafx.h"
//#include "	\ add additional includes here"
#include "MorPhologyDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMorPhologyDlg dialog
HDC T1;BITMAPINFO *pBIH;BYTE *lpOut1;
int nByteWidth,nHeight,m_Color,nWidth,m_nBits;
void CMorPhologyDlg::getmember(BITMAPINFO *m_pBIH,HDC t1,int m_nWidth,int m_nHeight,int m_nByteWidth,BYTE *m_lpBits,BYTE *m_lpOut)
{
	nWidth = m_nWidth;
	nHeight = m_nHeight;
	nByteWidth = m_nByteWidth;
	lpBits = m_lpBits;
	lpOut = m_lpOut;
	m_Color = m_nByteWidth/nWidth;
	pBIH=m_pBIH;
	T1=t1;
	m_Color=m_nByteWidth/m_nWidth;
}

void CMorPhologyDlg::lpBits_m_RGB()
{
	m_RGB =new BYTE **[m_Color];
	for(int k=0;k<m_Color;k++)	
	{
		m_RGB[k]=new BYTE *[nHeight];
		for(int i=0;i<nHeight;i++)
		{
			m_RGB[k][i]=new BYTE[nWidth];
			for(int j=0;j<nWidth;j++)
			{
				m_RGB[k][i][j]=lpBits[nByteWidth*i+m_Color*j+k];
			}
		}
	}
}

CMorPhologyDlg::CMorPhologyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMorPhologyDlg::IDD, pParent)
	, m_Threshold(-1)
	, m_MouseInRect(-1)
	, m_PointX(_T(""))
	, m_PointY(_T(""))
	, m_Preview(true)
	, m_BandW(FALSE)
{
	//{{AFX_DATA_INIT(CMorPhologyDlg)
	m_BandW = FALSE;
	m_Preview = FALSE;
	m_PointX = _T("");
	m_PointY = _T("");
	m_Threshold = 0;
	//}}AFX_DATA_INIT
	int RectTop=0,RectLeft=0,RectLength=30;
	m_filter=new BOOL* [9];
	for(int i=0;i<9;i++)
	{
		*(m_filter+i)=new BOOL [9];
		for(int j=0;j<9;j++)
		{
			*(*(m_filter+i)+j)=false;
			m_FilterRect[i][j].SetRect(RectLeft+j*RectLength,RectTop+i*RectLength,RectLeft+(j+1)*RectLength-1,RectTop+(i+1)*RectLength-1);
		}
	}
	*(*(m_filter+4)+4)=true;
}


void CMorPhologyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMorPhologyDlg)
	DDX_Control(pDX, IDC_COMBO_TYPE, m_Type);
	DDX_Control(pDX, IDC_SLIDER_THRESHOLD, m_Threshold_Sld);
	DDX_Control(pDX, IDC_EDIT_THRESHOLD, m_Threshold_Ctrl);
	DDX_Check(pDX, IDC_CHECK_BANDW, m_BandW);
	DDX_Check(pDX, IDC_CHECK_PREVIEW, m_Preview);
	DDX_Text(pDX, IDC_EDIT_POINTX, m_PointX);
	DDX_Text(pDX, IDC_EDIT_POINTY, m_PointY);
	DDX_Text(pDX, IDC_EDIT_THRESHOLD, m_Threshold);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMorPhologyDlg, CDialog)
	//{{AFX_MSG_MAP(CMorPhologyDlg)
	ON_MESSAGE(WM_MORPHOLOGY_OK, OnMorphologyOk)
//	ON_MESSAGE(WM_MORPHOLOGY_CERTAIN, OnMorphologyCertain)
	ON_MESSAGE(WM_MORPHOLOGY_CANCEL, OnMorphologyCancel)
	ON_BN_CLICKED(IDC_CHECK_BANDW, OnCheckBandw)
	ON_BN_CLICKED(IDC_CHECK_PREVIEW, OnCheckPreview)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER_THRESHOLD, OnCustomdrawSliderThreshold)
	ON_WM_LBUTTONDBLCLK()
	ON_WM_LBUTTONDOWN()
	ON_WM_MOUSEMOVE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMorPhologyDlg message handlers
afx_msg LRESULT CMorPhologyDlg::OnMorphologyOk(WPARAM wParam, LPARAM lParam)
{
	CString str=GetType();
	lpBits_m_RGB();
	if(str==_T("膨胀"))
	{
		MorphologyCode(0,GetFilter(),GetThreshold());
	}
	else if(str==_T("腐蚀"))
	{
		MorphologyCode(1,GetFilter(),GetThreshold());
	}
	else if(str==_T("开"))
	{
		MorphologyCode(1,GetFilter(),GetThreshold());
		MorphologyCode(0,GetFilter(),GetThreshold());
	}
	else if(str==_T("闭"))
	{
		MorphologyCode(0,GetFilter(),GetThreshold());
		MorphologyCode(1,GetFilter(),GetThreshold());
	}
	else if(str==_T("骨架化"))
	{
		Skeletoniz();
	}
	else if(str==_T("细化"))
	{
		thin();
	}
	StretchDIBits(T1,0,0,nWidth,nHeight,0,0,nWidth, nHeight,lpOut,pBIH,DIB_RGB_COLORS,SRCCOPY);
    return 0;
}
void CMorPhologyDlg::Skeletoniz()
{
	BOOL iteration ;
	lpBits_m_RGB();
	lpOut1=new BYTE[nByteWidth*nHeight];
	while(iteration)
	{
		iteration = false;
		MorphologyCode(1,GetFilter(),GetThreshold());
		MorphologyCode(0,GetFilter(),GetThreshold());
		for(int y=0;y<nHeight;y++)
		{
			for(int x=0;x<nWidth;x++)
			{
				if (lpBits[x+y*nByteWidth]==0 && lpOut[x+y*nByteWidth]==255)
				{
					//骨架碎片
					lpOut1[x+y*nWidth] = 0;
				}
			}
		}
		//检查是否腐蚀到空集
		for(int x=0;x<nByteWidth*nHeight;x++)
		{
			if (lpOut[x]!=255)
			{
				iteration = true;
				break;			
			}
		}
		if (iteration)
		{
			MorphologyCode(1,GetFilter(),GetThreshold());
			memcpy(lpBits,lpOut,nHeight*nByteWidth);
		}
		}
	memcpy(lpOut,lpOut1,nHeight*nByteWidth);
}
void CMorPhologyDlg::thin()
{
	bool iteration = true;
	int sum,x,y,mod;
	bool edge;
	BYTE *data = new BYTE[nByteWidth*nHeight];
	memcpy(data,lpBits,nByteWidth*nHeight);
	//temp数组为细化的碎片数组
	int *temp = new int[nByteWidth*nHeight];

	while(iteration)
	{
		//迭代标志位
		iteration = false;
		for(y=0;y<nHeight;y++)
		{
			for(x=0;x<nWidth;x++)
			{
				// 边界不做处理
				if (x==0 || y==0 || x==nWidth-1 || y==nHeight-1)
				{
					temp[x+y*nByteWidth] = 0;
				}
				else
				{
					edge = false;
					//八方向细化 根据击中击不中变换
					for (mod=0;mod<8;mod++)
					{
						sum = 0;
						switch(mod)
						{
						case 0:
							{
								sum = (int(data[x-1+(y-1)*nWidth]) + int(data[x+(y-1)*nWidth]) + int(data[x+1+(y-1)*nWidth])
									+                                        (255-int(data[x+y*nWidth]))
									+ (255-int(data[x-1+(y+1)*nWidth])) + (255-int(data[x+(y+1)*nWidth])) + (255-int(data[x+1+(y+1)*nWidth])))/255;
								if (sum==7)
								{
									temp[x+y*nWidth] = -255;
									edge = true;
								}
								break;
							}
						case 1:
							{
								sum = ( int(data[x+(y-1)*nWidth]) + int(data[x+1+(y-1)*nWidth])
									+ (255-int(data[x-1+y*nWidth])) + (255-int(data[x+y*nWidth])) + int(data[x+1+y*nWidth])
									+ (255-int(data[x-1+(y+1)*nWidth])) + (255-int(data[x+(y+1)*nWidth]))                                )/255;
								if (sum==7)
								{
									temp[x+y*nWidth] = -255;
									edge = true;
								}
								break;
							}
						case 2:
							{
								sum = ((255-int(data[x-1+(y-1)*nWidth])) +                             + int(data[x+1+(y-1)*nWidth])
									+ (255-int(data[x-1+y*nWidth])) + (255-int(data[x+y*nWidth])) + int(data[x+1+y*nWidth])
									+ (255-int(data[x-1+(y+1)*nWidth])) +                                int(data[x+1+(y+1)*nWidth])  )/255;
								if (sum==7)
								{
									temp[x+y*nWidth] = -255;
									edge = true;
								}
								break;
							}
						case 3:
							{
								sum = ((255-int(data[x-1+(y-1)*nWidth])) + (255-int(data[x+(y-1)*nWidth])) 
									+ (255-int(data[x-1+y*nWidth])) + (255-int(data[x+y*nWidth])) + int(data[x+1+y*nWidth])
									+                                        int(data[x+(y+1)*nWidth]) + int(data[x+1+(y+1)*nWidth]))/255;
								if (sum==7)
								{
									temp[x+y*nWidth] = -255;
									edge = true;
								}
								break;
							}
						case 4:
							{
								sum = ((255-int(data[x-1+(y-1)*nWidth])) + (255-int(data[x+(y-1)*nWidth])) + (255-int(data[x+1+(y-1)*nWidth]))
									+                                        (255-int(data[x+y*nWidth]))
									+ int(data[x-1+(y+1)*nWidth]) + int(data[x+(y+1)*nWidth]) + int(data[x+1+(y+1)*nWidth]))/255;
								if (sum==7)
								{
									temp[x+y*nWidth] = -255;
									edge = true;
								}
								break;
							}
						case 5:
							{
								sum = (                                     (255-int(data[x+(y-1)*nWidth])) + (255-int(data[x+1+(y-1)*nWidth]))
									+ int(data[x-1+y*nWidth]) + (255-int(data[x+y*nWidth])) + (255-int(data[x+1+y*nWidth]))
									+ int(data[x-1+(y+1)*nWidth]) + int(data[x+(y+1)*nWidth])                               )/255;
								if (sum==7)
								{
									temp[x+y*nWidth] = -255;
									edge = true;
								}
								break;
							}
						case 6:
							{
								sum = (int(data[x-1+(y-1)*nWidth]) +                             + (255-int(data[x+1+(y-1)*nWidth]))
									+ int(data[x-1+y*nWidth]) + (255-int(data[x+y*nWidth])) + (255-int(data[x+1+y*nWidth]))
									+ int(data[x-1+(y+1)*nWidth]) +                                (255-int(data[x+1+(y+1)*nWidth]))  )/255;
								if (sum==7)
								{
									temp[x+y*nWidth] = -255;
									edge = true;
								}
								break;
								break;
							}
						case 7:
							{
								sum = (int(data[x-1+(y-1)*nWidth]) + int(data[x+(y-1)*nWidth]) 
									+ int(data[x-1+y*nWidth]) + (255-int(data[x+y*nWidth])) + (255-int(data[x+1+y*nWidth]))
									+                                (255-int(data[x+(y+1)*nWidth])) + (255-int(data[x+1+(y+1)*nWidth])))/255;
								if (sum==7)
								{
									temp[x+y*nWidth] = -255;
									edge = true;
								}
								else
									temp[x+y*nWidth] = 0;
								break;
							}
						}
						if(edge) 
						{
							iteration = true;
							break;	
						}
					}	
				}
			}
		}
		//去除外围碎片
		for(y=0;y<nHeight;y++)
		{
			for(x=0;x<nWidth;x++)
			{
				
				if (x==0 || y==0 || x==nWidth-1 || y==nHeight-1)
				{
					lpOut[x+y*nWidth] = lpBits[x+y*nWidth];
				}
				else
				{
					//得到单次细化的结果
					data[x+y*nWidth] = BYTE(int(data[x+y*nWidth])-temp[x+y*nWidth]);
				}
			}
		}
	}
	memcpy(lpOut,data,nByteWidth*nHeight);
	delete[] data;
	delete[] temp;
}
afx_msg LRESULT CMorPhologyDlg::OnMorphologyCancel(WPARAM wParam, LPARAM lParam)
{
	return 0;
}
CString CMorPhologyDlg::GetType()
{
	UpdateData();
	CString strTemp;
	m_Type.GetWindowText(strTemp);
	return strTemp;
}
BOOL** CMorPhologyDlg::GetFilter()
{
	return m_filter;
}
int CMorPhologyDlg::GetThreshold()
{
	UpdateData();
	return m_Threshold;
}
void CMorPhologyDlg::OnCheckBandw() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if(m_BandW)
	{
		m_Threshold_Sld.ShowWindow(SW_SHOW);
		m_Threshold_Ctrl.ShowWindow(SW_SHOW);
		m_Threshold=m_Threshold_Sld.GetPos();
	}
	else
	{
		m_Threshold_Sld.ShowWindow(SW_HIDE);
		m_Threshold_Ctrl.ShowWindow(SW_HIDE);
		m_Threshold=-1;
	}
	UpdateData(0);
	if(m_Preview)
			GetParent()->SendMessage(WM_MORPHOLOGY_OK);
}

void CMorPhologyDlg::OnCancel() 
{
	// TODO: Add extra cleanup here
	GetParent()->SendMessage(WM_MORPHOLOGY_CANCEL);
	CDialog::OnCancel();
}

void CMorPhologyDlg::OnOK() 
{
	// TODO: Add extra validation here
	CString str=GetType();
	lpBits_m_RGB();
	if(str==_T("膨胀"))
	{
		MorphologyCode(0,GetFilter(),GetThreshold());
	}
	else if(str==_T("腐蚀"))
	{
		MorphologyCode(1,GetFilter(),GetThreshold());
	}
	else if(str==_T("开"))
	{
		MorphologyCode(1,GetFilter(),GetThreshold());
		MorphologyCode(0,GetFilter(),GetThreshold());
	}
	else if(str==_T("闭"))
	{
		MorphologyCode(0,GetFilter(),GetThreshold());
	    MorphologyCode(1,GetFilter(),GetThreshold());
	}
	else if(str==_T("骨架化"))
	{
		Skeletoniz();
	}
	else if(str==_T("细化"))
	{
		thin();
	}
StretchDIBits(T1,0,0,nWidth,nHeight,0,0,nWidth, nHeight,lpOut,pBIH,DIB_RGB_COLORS,SRCCOPY);

//	CDialog::OnOK();
}

void CMorPhologyDlg::OnCheckPreview() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	if(m_Preview)
		GetParent()->SendMessage(WM_MORPHOLOGY_OK);
	else
		GetParent()->SendMessage(WM_MORPHOLOGY_CANCEL,1);
	UpdateData(0);
}

void CMorPhologyDlg::OnCustomdrawSliderThreshold(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	UpdateData();
	m_Threshold=m_Threshold_Sld.GetPos();
	UpdateData(0);
	if(m_Preview)
		GetParent()->SendMessage(WM_MORPHOLOGY_OK);
	*pResult = 0;
}

void CMorPhologyDlg::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	for(int i=0;i<9;i++)
	{
		for(int j=0;j<9;j++)
		{
			*(*(m_filter+i)+j)=false;
		}
	}
	*(*(m_filter+4)+4)=true;
	InvalidateRect(CRect(0,0,30*9,30*9),0);
	if(m_Preview)
	GetParent()->SendMessage(WM_MORPHOLOGY_OK);
	CDialog::OnLButtonDblClk(nFlags, point);
}

void CMorPhologyDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	for(int i=0;i<9;i++)
	{
		for(int j=0;j<9;j++)
		{
			if(PtInRect(m_FilterRect[i][j],point))
			{
				*(*(m_filter+i)+j)=!*(*(m_filter+i)+j);
			}
		}
	}
	InvalidateRect(CRect(0,0,30*9,30*9),0);
	if(m_Preview)
	GetParent()->SendMessage(WM_MORPHOLOGY_OK);
	CDialog::OnLButtonDown(nFlags, point);
}

void CMorPhologyDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	// TODO: Add your message handler code here and/or call default
	for(int i=0;i<9;i++)
	{
		for(int j=0;j<9;j++)
		{
			if(PtInRect(m_FilterRect[i][j],point))
			{
				m_MouseInRect=i*9+j;
				InvalidateRect(CRect(0,0,30*9,30*9),0);
				m_PointX.Format(_T("x=%d"),j-4);
				m_PointY.Format(_T("y=%d"),i-4);
				UpdateData(0);
				CDialog::OnMouseMove(nFlags, point);
				return;
			}
		}
	}
/*	m_MouseInRect=-1;
	InvalidateRect(CRect(0,0,30*9,30*9),0);
	m_PointX.Empty();
	m_PointY.Empty();
	UpdateData(0);
	CDialog::OnMouseMove(nFlags, point);
	*/
}
void CMorPhologyDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	//设置四种颜色
	CBrush GrayBrush(RGB(160,160,160));//未选中
	CBrush BlackBrush(RGB(0,0,0));//选中
	CBrush LGrayBrush(RGB(192,192,192));//鼠标击下未弹起
	CBrush LBlackBrush(RGB(64,64,64));//鼠标指向
	for(int i=0;i<9;i++)
	{
		for(int j=0;j<9;j++)
		{
			if(*(*(m_filter+i)+j))
			{
				if(m_MouseInRect==i*9+j)
				{
					dc.FillRect(m_FilterRect[i][j],&LBlackBrush);
				}
				else
				{
					dc.FillRect(m_FilterRect[i][j],&BlackBrush);
				}
			}
			else
			{
				if(m_MouseInRect==i*9+j)
				{
					dc.FillRect(m_FilterRect[i][j],&LGrayBrush);
				}
				else
				{
					dc.FillRect(m_FilterRect[i][j],&GrayBrush);
				}
			}
		}
	}
	// Do not call CDialog::OnPaint() for painting messages
}

BOOL CMorPhologyDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CDialog::OnInitDialog();
	m_Type.SetCurSel(0);
	m_Threshold_Sld.SetRange(0,255);
	m_Threshold_Sld.SetTicFreq(1);
	m_Threshold_Sld.SetPos(128);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CMorPhologyDlg::MorphologyCode(int Type,BOOL** filter,int threshold)
{
	int i,j,k,l,m,a;
	unsigned char ***tmp=new unsigned char**[m_Color];
	for(i=0;i<m_Color;i++)
	{
		*(tmp+i)=new unsigned char*[nHeight];
	}
	for(i=0;i<m_Color;i++)
	{
		for(j=0;j<nHeight;j++)
		{
			*(*(tmp+i)+j)=new unsigned char[nWidth];
		}
	}
	
	if(!Type)//Dilation
	{
		for(i=0;i<m_Color;i++)
		{
			for(j=0;j<nHeight;j++)
			{
				for(k=0;k<nWidth;k++)
				{
					*(*(*(tmp+i)+j)+k)=0;
					for(l=0;l<9;l++)
					{
						for(m=0;m<9;m++)
						{//膨胀的话，算法需要把结构因子反过来
							if(*(*(filter+8-l)+8-m))//如果结构因子为1，才进行运算以节省时间
								if(*(*(*(tmp+i)+j)+k)<(a=(*(*(*(m_RGB+i)+max(0,min(nHeight-1,j+l-4)))+max(0,min(nWidth-1,k+m-4))))))
									*(*(*(tmp+i)+j)+k)=a;//求出该结构因子内的最大值
						}
					}
				}
			}
		}
	}
	else//Erosion
	{
		for(i=0;i<m_Color;i++)
		{
			for(j=0;j<nHeight;j++)
			{
				for(k=0;k<nWidth;k++)
				{
					*(*(*(tmp+i)+j)+k)=255;
					for(l=0;l<9;l++)
					{
						for(m=0;m<9;m++)
						{
							if(*(*(filter+l)+m))//如果结构因子为1，才进行运算以节省时间
								if(*(*(*(tmp+i)+j)+k)>(a=(*(*(*(m_RGB+i)+max(0,min(nHeight-1,j+l-4)))+max(0,min(nWidth-1,k+m-4))))))
									*(*(*(tmp+i)+j)+k)=a;//求出该结构因子内的最小值
						}
					}
				}
			}
		}
	}
	
	for(i=0;i<m_Color;i++)
	{
		for(j=0;j<nHeight;j++)
		{
			for(k=0;k<nWidth;k++)
			{
				*(*(*(m_RGB+i)+j)+k)=threshold==-1?*(*(*(tmp+i)+j)+k):*(*(*(tmp+i)+j)+k)>=threshold?255:0;
			}//如果设定了阈值，则对图像进行二值化
			delete(*(*(tmp+i)+j));
		}
		delete(*(tmp+i));
	}
	free(tmp);
	lpOut = new BYTE [nByteWidth*nHeight];
	for(i=0;i<m_Color;i++)
		for(int j=0;j<nHeight;j++)
			for(int k=0;k<nWidth;k++)
			{
				lpOut[nByteWidth*j+m_Color*k+i]=m_RGB[i][j][k];
			}
}
