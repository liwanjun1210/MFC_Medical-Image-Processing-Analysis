#if !defined(AFX_MEDIANFILTDLG_H__66E7F739_A659_42E1_AA89_FFF49E3EFBC4__INCLUDED_)
#define AFX_MEDIANFILTDLG_H__66E7F739_A659_42E1_AA89_FFF49E3EFBC4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MedianFiltDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMedianFiltDlg dialog

class AFX_EXT_CLASS CMedianFiltDlg : public CDialog
{
// Construction
public:
	CMedianFiltDlg(CWnd* pParent = NULL);   // standard constructor
	int m_iWinSize;
	inline BOOL BubbleSort(int* pdData, int iAmount);
	BOOL MedianFilter(int m_iWinSize);
	BYTE *lpOut;
	void getmember(int nWidth,int nHeight,int nByteWidth,int nBits,BYTE *m_lpOut);
	BOOL MaxFilter(int m_iWinSize);
	BOOL MinFilter(int m_iWinSize);
	BOOL EaualizeFilter(int m_iWinSize);
// Dialog Data
	//{{AFX_DATA(CMedianFiltDlg)
	enum { IDD = IDD_ENHANCE_MEDIANFILT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMedianFiltDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CMedianFiltDlg)
	afx_msg void OnMedfiltChangetosize3();
	afx_msg void OnMedfiltChangetosize5();
	afx_msg void OnMedfiltChangetosize7();
	afx_msg void OnMedfiltChangetosize9();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MEDIANFILTDLG_H__66E7F739_A659_42E1_AA89_FFF49E3EFBC4__INCLUDED_)
