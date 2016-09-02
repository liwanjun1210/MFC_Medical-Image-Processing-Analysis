#if !defined(AFX_INVERSEFILTERRADIUS_H__FC46CC11_0A9E_4771_97E6_F0A5A0C008BE__INCLUDED_)
#define AFX_INVERSEFILTERRADIUS_H__FC46CC11_0A9E_4771_97E6_F0A5A0C008BE__INCLUDED_

#include "COMPLEX.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// InverseFilterRadius.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CInverseFilterRadius dialog

class AFX_EXT_CLASS CInverseFilterRadius : public CDialog
{
// Construction
public:
	CInverseFilterRadius(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CInverseFilterRadius)
	enum { IDD = IDD_INVERSEFILTER_RADIUS };
	int		m_nInverseFilterRadius;
	//}}AFX_DATA

	int m_nWidth,m_nHeight,m_nByteWidth,m_nBits;
	BOOL m_Flag;
	BYTE *m_lpBits;
	BYTE *m_lpOut;
	
	void GetMembers(int nByteWidth,int nHeight,int nBits,int nWidth,BYTE *lpBits,int nFlag);
	BOOL WienerFilterMotion();
	BOOL WienerFilterAtmoTurb();
	BOOL InverseFilterMotion(double Para_a, double Para_b, double Para_T, int FreqRadius);
	BOOL InverseFilterAtmoTurb(double Para_k);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInverseFilterRadius)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CInverseFilterRadius)
	afx_msg void OnRadio4();
	afx_msg void OnRadio2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INVERSEFILTERRADIUS_H__FC46CC11_0A9E_4771_97E6_F0A5A0C008BE__INCLUDED_)
