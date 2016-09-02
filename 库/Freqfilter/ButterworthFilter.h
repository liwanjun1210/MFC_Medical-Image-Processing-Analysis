#if !defined(AFX_BUTTERWORTHFILTER_H__B93ECF1D_6C1B_4870_9D02_EB992EF04655__INCLUDED_)
#define AFX_BUTTERWORTHFILTER_H__B93ECF1D_6C1B_4870_9D02_EB992EF04655__INCLUDED_

#include "COMPLEX.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ButterworthFilter.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CButterworthFilter dialog

class AFX_EXT_CLASS CButterworthFilter : public CDialog
{
// Construction
public:
	CButterworthFilter(CWnd* pParent = NULL);   // standard constructor

	int m_nWidth,m_nHeight,m_nByteWidth,m_nBits;
	BOOL Flag;
	BYTE *m_lpBits;
	BYTE *m_lpOut;
	
	//	COMPLEX* m_pComplex;	//用于保存傅里叶变换结果
	
	void GetMembers(int nByteWidth,int nHeight,int nBits,int nWidth,BYTE *lpBits);
	BOOL ButterWorthLowPassFilter();
	BOOL ButterWorthHighPassFilter();
// Dialog Data
	//{{AFX_DATA(CButterworthFilter)
	enum { IDD = IDD_BUTTERWORTH_FILTER };
	int		m_BwCutoffFreq;
	int		m_BwOrder;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CButterworthFilter)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CButterworthFilter)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BUTTERWORTHFILTER_H__B93ECF1D_6C1B_4870_9D02_EB992EF04655__INCLUDED_)
