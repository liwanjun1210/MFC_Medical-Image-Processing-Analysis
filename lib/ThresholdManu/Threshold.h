#if !defined(AFX_THRESHOLD_H__95ED2090_7052_4675_A59F_490E2CA6E1E1__INCLUDED_)
#define AFX_THRESHOLD_H__95ED2090_7052_4675_A59F_490E2CA6E1E1__INCLUDED_
#include "resource.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Threshold.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CThreshold dialog

class  AFX_EXT_CLASS CThreshold : public CDialog
{
// Construction
public:
	CThreshold(CWnd* pParent = NULL);   // standard constructor
    int GetThreshold();
	BYTE*lpOut;
	void ThresholdProcess(int Threshold);
	void getmember(BITMAPINFO *m_pBIH,HDC t1,int m_nWidth,int m_nHeight,int m_nByteWidth,BYTE *m_lpBits,BYTE *m_lpOut);
	int OtsuThreshold();
	void GetHistogram();
	void DoThreshold();
	void RGB2Gray();
	int Threshold;
	float *m_pfDistr;
// Dialog Data
	//{{AFX_DATA(CThreshold)
	enum { IDD = IDD_DIALOG_ThresholdManu };
	CComboBox	m_Method;
	int		m_Threshold;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CThreshold)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CThreshold)
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_THRESHOLD_H__95ED2090_7052_4675_A59F_490E2CA6E1E1__INCLUDED_)
