#if !defined(AFX_IDEALFILTER_H__3C46C96A_3445_4D7E_8FAB_CDC737302D81__INCLUDED_)
#define AFX_IDEALFILTER_H__3C46C96A_3445_4D7E_8FAB_CDC737302D81__INCLUDED_

#include "COMPLEX.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// IdealFilter.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CIdealFilter dialog

class AFX_EXT_CLASS CIdealFilter : public CDialog
{
// Construction
public:
	CIdealFilter(CWnd* pParent = NULL);   // standard constructor

	int m_nWidth,m_nHeight,m_nByteWidth,m_nBits;
	BOOL Flag;
	BYTE *m_lpBits;
	BYTE *m_lpOut;

//	COMPLEX* m_pComplex;	//用于保存傅里叶变换结果

	void GetMembers(int nByteWidth,int nHeight,int nBits,int nWidth,BYTE *lpBits);

	BOOL FFTDIB(COMPLEX *pComplex);
	BOOL IdealLowPassFilter();
	BOOL IdealHighPassFilter();
// Dialog Data
	//{{AFX_DATA(CIdealFilter)
	enum { IDD = IDD_IDEAL_FILTER };
	int		m_CutoffFreq;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CIdealFilter)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CIdealFilter)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IDEALFILTER_H__3C46C96A_3445_4D7E_8FAB_CDC737302D81__INCLUDED_)
