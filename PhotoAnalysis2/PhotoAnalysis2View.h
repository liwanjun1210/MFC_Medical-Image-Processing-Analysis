// PhotoAnalysis2View.h : interface of the CPhotoAnalysis2View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PHOTOANALYSIS2VIEW_H__4DC49D40_8A96_4CFB_AF61_47DEEE6E67C7__INCLUDED_)
#define AFX_PHOTOANALYSIS2VIEW_H__4DC49D40_8A96_4CFB_AF61_47DEEE6E67C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

void fourn(double data[],double nn[],int &ndim,int &isign);
class CPhotoAnalysis2View : public CScrollView
{
protected: // create from serialization only
	CPhotoAnalysis2View();
	DECLARE_DYNCREATE(CPhotoAnalysis2View)
BOOL SaveBitMapToFile(HBITMAP hBitmap, CString lpFileName);
// Attributes
public:
	CPhotoAnalysis2Doc* GetDocument();
/*	CScrollBar m_hScrollBar;//定义水平滚动条变量
	CScrollBar m_vScrollBar;//定义垂直滚动条变量
	CRect rect;
	int m_iHMax,m_iVMax;//定义屏幕
	int m_iStartTrace,m_iStartPoint,EndTrace,EndPoint;
	int m_iTracePerScreen,m_iPntsPerScreen;*/
// Operations
public:
	int p_Width;int p_Height;int p_Bits;int p_Colors; int p_ByteWidth;
	BITMAPFILEHEADER *pBFH;   //图像文件头指针
	BITMAPINFO *pBIH;   //图像信息头指针
	RGBQUAD *pRGB;     //图像调色板指针
	int p_Imagetype;HGLOBAL m_hDib;BYTE *pBits;
	int m;	int T_Height;int T_Width;
	BYTE *lpOut;
	BITMAPINFO *pNewBIH;
	int DFlag;double temp;//退化模型
	void MySpliting(BYTE *input,CRect region,int p_Width);
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPhotoAnalysis2View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPhotoAnalysis2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPhotoAnalysis2View)
	afx_msg void OnFileOpen();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnGrayLinarStretch();
	afx_msg void OnGrayPiecewise();
	afx_msg void OnColorToGray();
	afx_msg void OnThreshold();
	afx_msg void OnRgbToHsv();
	afx_msg void OnHistogramEqualize();
	afx_msg void OnHistogramMatching();
	afx_msg void OnEnhanceMidianfilter();
	afx_msg void OnEnhanceMaxfilter();
	afx_msg void OnEnhanceMinfilter();
	afx_msg void OnEnhanceEqualizefilter();
	afx_msg void OnEnhanceSharpeningfilter();
	afx_msg void OnGrayToColor();
	afx_msg void OnTransformMirrorX();
	afx_msg void OnTransformMirrorY();
	afx_msg void OnZoom();
	afx_msg void OnFft();
	afx_msg void OnIfft();
	afx_msg void OnImageCal();
	afx_msg void OnIdealLpf();
	afx_msg void OnIdealHpf();
	afx_msg void OnButterLpf();
	afx_msg void OnButterHpf();
	afx_msg void OnHomomorphicFilter();
	afx_msg void OnInverseFilter();
	afx_msg void OnMenuitem32807();
	afx_msg void OnDegenerate();
	afx_msg void OnInverse();
	afx_msg void OnAndor();
	afx_msg void OnLogicAnd();
	afx_msg void OnMorphology();
	afx_msg void OnRegionGrow();
	afx_msg void OnRegionDivandcon();
	afx_msg void OnFileSaveAs();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in PhotoAnalysis2View.cpp
inline CPhotoAnalysis2Doc* CPhotoAnalysis2View::GetDocument()
   { return (CPhotoAnalysis2Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PHOTOANALYSIS2VIEW_H__4DC49D40_8A96_4CFB_AF61_47DEEE6E67C7__INCLUDED_)
