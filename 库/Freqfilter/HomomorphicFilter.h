#if !defined(AFX_HOMOMORPHICFILTER_H__9CC36ECB_4EB6_4E32_9D26_E8B1627DAE03__INCLUDED_)
#define AFX_HOMOMORPHICFILTER_H__9CC36ECB_4EB6_4E32_9D26_E8B1627DAE03__INCLUDED_

#include "COMPLEX.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HomomorphicFilter.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CHomomorphicFilter dialog

class AFX_EXT_CLASS CHomomorphicFilter : public CDialog
{
// Construction
public:
	CHomomorphicFilter(CWnd* pParent = NULL);   // standard constructor

	int m_nWidth,m_nHeight,m_nByteWidth,m_nBits;
	BOOL Flag;
	BYTE *m_lpBits;
	BYTE *m_lpOut;

	void GetMembers(int nByteWidth,int nHeight,int nBits,int nWidth,BYTE *lpBits);
	BOOL HomomorphicFilter();
// Dialog Data
	//{{AFX_DATA(CHomomorphicFilter)
	enum { IDD = IDD_HOMOMORPHIC_FILTER };
	int		m_nCutoffFreq;
	float	m_fGammaH;
	float	m_fGammaL;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHomomorphicFilter)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHomomorphicFilter)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HOMOMORPHICFILTER_H__9CC36ECB_4EB6_4E32_9D26_E8B1627DAE03__INCLUDED_)
