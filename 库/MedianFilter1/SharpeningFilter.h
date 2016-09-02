#if !defined(AFX_SHARPENINGFILTER_H__8F658965_43A1_407B_8FFE_162BA6D03F86__INCLUDED_)
#define AFX_SHARPENINGFILTER_H__8F658965_43A1_407B_8FFE_162BA6D03F86__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SharpeningFilter.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SharpeningFilter dialog
class AFX_EXT_CLASS CSharpeningFilterDlg : public CDialog
{
// Construction
public:
	CSharpeningFilterDlg(CWnd* pParent = NULL);   // standard constructor
	BOOL SharpeningFilter(int* piSharpCoef);
	void getmember(int nWidth,int nHeight,int nByteWidth,int nBits,BYTE *m_lpOut);
	BYTE *lpOut;
	int m_iWinSize;
	int m_nByteWidth,m_nHeight,m_nBits,m_nWidth;
    BYTE *lpBits;
// Dialog Data
	//{{AFX_DATA(SharpeningFilter)
	enum { IDD = IDD_SHARPENING_FILTER };
	int		m_nSharpCoef00;
	int		m_nSharpCoef01;
	int		m_nSharpCoef02;
	int		m_nSharpCoef03;
	int		m_nSharpCoef04;
	int		m_nSharpCoef05;
	int		m_nSharpCoef06;
	int		m_nSharpCoef07;
	int		m_nSharpCoef08;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SharpeningFilter)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SharpeningFilter)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHARPENINGFILTER_H__8F658965_43A1_407B_8FFE_162BA6D03F86__INCLUDED_)
