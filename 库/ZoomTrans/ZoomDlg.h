#if !defined(AFX_ZOOMDLG_H__66917C11_A378_4732_9A79_91922469B2DC__INCLUDED_)
#define AFX_ZOOMDLG_H__66917C11_A378_4732_9A79_91922469B2DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZoomDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CZoomDlg dialog
#include "Resource.h"
class AFX_EXT_CLASS CZoomDlg : public CDialog
{
// Construction
public:
	CZoomDlg(CWnd* pParent = NULL);   // standard constructor
	int GetH();int GetW(); int GetMethod();
	BYTE*lpOut;BYTE ***m_RGB;
	void Zoom(int TargetHeight,int TargetWidth,int Method);
	void lpBits_m_RGB();
	int newWidth,newHeight;
	void getmembers(BITMAPINFO *m_pBIH,HDC t1,int m_nWidth,int m_nHeight,int m_nByteWidth,BYTE *m_lpBits);
// Dialog Data
	//{{AFX_DATA(CZoomDlg)
	enum { IDD = IDD_DIALOG_ZOOM };
	CComboBox	m_Method;
	CEdit	m_cDW;
	CEdit	m_cDH;
	BOOL	m_bWHScale;
	int		m_fDH;
	int		m_fDW;
	int		m_fOH;
	int		m_fOW;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZoomDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CZoomDlg)
	afx_msg void OnCheckRealate();
	afx_msg void OnSelchangeCOMBOMethod();
	afx_msg void OnChangeEditDh();
	afx_msg void OnChangeEditDw();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZOOMDLG_H__66917C11_A378_4732_9A79_91922469B2DC__INCLUDED_)
