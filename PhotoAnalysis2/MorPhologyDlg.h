#if !defined(AFX_MORPHOLOGYDLG_H__6171F883_EC94_46EB_9B36_1E015E82D765__INCLUDED_)
#define AFX_MORPHOLOGYDLG_H__6171F883_EC94_46EB_9B36_1E015E82D765__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MorPhologyDlg.h : header file
//
#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// CMorPhologyDlg dialog
#define WM_MORPHOLOGY_OK WM_USER+14
//#define WM_MORPHOLOGY_CERTAIN WM_USER+15
#define WM_MORPHOLOGY_CANCEL WM_USER+16
class AFX_EXT_CLASS CMorPhologyDlg : public CDialog
{
// Construction
public:
	BOOL **m_filter; 
	int m_MouseInRect;
	CRect m_FilterRect[9][9];
	BOOL** GetFilter();
	int GetThreshold();
	CString GetType();
public:
	CMorPhologyDlg(CWnd* pParent = NULL);   // standard constructor
	void lpBits_m_RGB();
	BYTE *lpOut;BYTE ***m_RGB;
	void MorphologyCode(int Type,BOOL** filter,int threshold);
	void getmember(BITMAPINFO *m_pBIH,HDC t1,int m_nWidth,int m_nHeight,int m_nByteWidth,BYTE *m_lpBits,BYTE *m_lpOut);
	void Skeletoniz();
	void thin();BYTE *lpBits;
// Dialog Data
	//{{AFX_DATA(CMorPhologyDlg)
	enum { IDD = IDD_DIALOG_MORPHOLOGY };
	CComboBox	m_Type;
	CSliderCtrl	m_Threshold_Sld;
	CEdit	m_Threshold_Ctrl;
	BOOL	m_BandW;
	BOOL	m_Preview;
	CString	m_PointX;
	CString	m_PointY;
	int		m_Threshold;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMorPhologyDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMorPhologyDlg)
	afx_msg void OnCheckBandw();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnCheckPreview();
	afx_msg void OnCustomdrawSliderThreshold(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
   	afx_msg LRESULT OnMorphologyOk(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnMorphologyCancel(WPARAM wParam, LPARAM lParam);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MORPHOLOGYDLG_H__6171F883_EC94_46EB_9B36_1E015E82D765__INCLUDED_)
