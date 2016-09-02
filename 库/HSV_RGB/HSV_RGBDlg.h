#if !defined(AFX_HSV_RGBDLG_H__E08A63E1_5206_4EF9_8212_2A9AAFEB912C__INCLUDED_)
#define AFX_HSV_RGBDLG_H__E08A63E1_5206_4EF9_8212_2A9AAFEB912C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HSV_RGBDlg.h : header file
//
#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// CHSV_RGBDlg dialog

class AFX_EXT_CLASS CHSV_RGBDlg : public CDialog
{
// Construction
public:
	BYTE *lpOut;
	void RGB_HSV();
	void getmembers(BITMAPINFO *m_pBIH,HDC t1,int m_nWidth,int m_nHeight,int m_nByteWidth,BYTE *m_lpBits);
	void getRGB(float &R,float &G,float &B,int i,int j);
	void RGBTrans(float &R,float &G,float &B,int i,int j);
	void Hsv2Rgb(float H, float S, float V, float &R, float &G, float &B);
	void Rgb2Hsv(float R, float G, float B, float& H, float& S, float&V);

public:
	CHSV_RGBDlg(CWnd* pParent = NULL);   // standard constructor
	double h,s,v;
// Dialog Data
	//{{AFX_DATA(CHSV_RGBDlg)
	enum { IDD = IDD_HSV_RGB };
	CStatic	m_nV;
	CStatic	m_nS;
	CStatic	m_nH;
	CSliderCtrl	m_cV;
	CSliderCtrl	m_cS;
	CSliderCtrl	m_cH;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHSV_RGBDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHSV_RGBDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnReleasedcaptureSliderV(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSliderS(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSliderH(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HSV_RGBDLG_H__E08A63E1_5206_4EF9_8212_2A9AAFEB912C__INCLUDED_)
