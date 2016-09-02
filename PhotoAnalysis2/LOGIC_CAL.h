#if !defined(AFX_LOGIC_CAL_H__56E66F3F_CC77_46F0_BE98_215B22A0F50A__INCLUDED_)
#define AFX_LOGIC_CAL_H__56E66F3F_CC77_46F0_BE98_215B22A0F50A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LOGIC_CAL.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLOGIC_CAL dialog

class CLOGIC_CAL : public CDialog
{
// Construction
public:
	CLOGIC_CAL(CWnd* pParent = NULL);   // standard constructor
    void getmembers(BITMAPINFO *m_pBIH,HDC t1,int m_nWidth,int m_nHeight,int m_nByteWidth,BYTE* m_lpOut);
	BYTE* lpOut;
	BYTE *lpbits_temp;	
	void opentemp();
	void Processing();
// Dialog Data
	//{{AFX_DATA(CLOGIC_CAL)
	enum { IDD = IDD_DIALOG_LOGIC_CAL };
	int		m_radio;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLOGIC_CAL)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLOGIC_CAL)
	afx_msg void OnRadioAdd();
	afx_msg void OnRadioDiv();
	afx_msg void OnRadioMul();
	afx_msg void OnRadioSub();
	afx_msg void OnRadioAnd();
	afx_msg void OnRadioOr();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOGIC_CAL_H__56E66F3F_CC77_46F0_BE98_215B22A0F50A__INCLUDED_)
