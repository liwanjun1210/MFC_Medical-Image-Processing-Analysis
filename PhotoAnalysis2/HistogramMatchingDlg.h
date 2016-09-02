#if !defined(AFX_HISTOGRAMMATCHINGDLG_H__D8892FDB_8017_48EA_BF90_9EC82087D569__INCLUDED_)
#define AFX_HISTOGRAMMATCHINGDLG_H__D8892FDB_8017_48EA_BF90_9EC82087D569__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HistogramMatchingDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHistogramMatchingDlg dialog

class AFX_EXT_CLASS CHistogramMatchingDlg : public CDialog
{
// Construction
public:
	CHistogramMatchingDlg(CWnd* pParent = NULL);   // standard constructor
	int m_IsDragingFlag;
	CRect m_MouseRect;
	CPoint m_Point3;
	CPoint m_Point2;
	CPoint m_Point1;
	void getmembers(BITMAPINFO *m_pBIH,HDC t1,int m_nWidth,int m_nHeight,int m_nByteWidth,BYTE *m_lpOut);
	BYTE* lpOut;
	HistogramMatching(CPoint point1, CPoint point2, CPoint point3);
// Dialog Data
	//{{AFX_DATA(CHistogramMatchingDlg)
	enum { IDD = IDD_HISTOGRAM_MATCHING };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHistogramMatchingDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHistogramMatchingDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HISTOGRAMMATCHINGDLG_H__D8892FDB_8017_48EA_BF90_9EC82087D569__INCLUDED_)
