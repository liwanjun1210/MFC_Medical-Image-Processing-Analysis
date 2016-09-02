#if !defined(AFX_HISTOGRAMVIEW1_H__7A7B962E_17A5_4E24_A581_CC5A6749D69A__INCLUDED_)
#define AFX_HISTOGRAMVIEW1_H__7A7B962E_17A5_4E24_A581_CC5A6749D69A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HistogramView1.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHistogramView dialog

class  __declspec(dllexport) CHistogramView : public CDialog
{
// Construction
public:
	CHistogramView(CWnd* pParent = NULL);   // standard constructor
void getmember(int m_nWidth,int m_nHeight,int m_nByteWidth,BYTE *m_lpBits,int m_nBits,BYTE *lpOut,BOOL Flag);
// Dialog Data
	//{{AFX_DATA(CHistogramView)
	enum { IDD = IDD_VIEW_HISTOGRAM };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHistogramView)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	float* m_pfDistr;
	// Generated message map functions
	//{{AFX_MSG(CHistogramView)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HISTOGRAMVIEW1_H__7A7B962E_17A5_4E24_A581_CC5A6749D69A__INCLUDED_)
