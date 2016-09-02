#if !defined(AFX_DEGENERATEMODEL_H__08ABB4AA_30DE_4E15_9784_72E8920DBE45__INCLUDED_)
#define AFX_DEGENERATEMODEL_H__08ABB4AA_30DE_4E15_9784_72E8920DBE45__INCLUDED_

#include "COMPLEX.h"
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DegenerateModel.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDegenerateModel dialog

class AFX_EXT_CLASS CDegenerateModel : public CDialog
{
// Construction
public:
	CDegenerateModel(CWnd* pParent = NULL);   // standard constructor

	int DegenerateModelFlag;	//退化模型标志，0表示未选择退化模型、1表示大气湍流退化、2表示运动退化、3表示不需要人为退化

	int m_nWidth,m_nHeight,m_nByteWidth,m_nBits;
	BOOL Flag;
	BYTE *m_lpBits;
	BYTE *m_lpOut;

	void GetMembers(int nByteWidth,int nHeight,int nBits,int nWidth,BYTE *lpBits);
	BOOL Degenerate();
// Dialog Data
	//{{AFX_DATA(CDegenerateModel)
	enum { IDD = IDD_DEGENERATE };
	double	m_fAtmosTurbPara_k;
	double	m_fMotionDegePara_a;
	double	m_fMotionDegePara_b;
	double	m_fMotionDegePara_T;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDegenerateModel)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDegenerateModel)
	afx_msg void OnAtmosphericTurbulence();
	afx_msg void OnMotionDegenerate();
	afx_msg void OnRegenetatedImage();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEGENERATEMODEL_H__08ABB4AA_30DE_4E15_9784_72E8920DBE45__INCLUDED_)
