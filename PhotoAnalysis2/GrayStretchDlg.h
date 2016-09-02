#if !defined(AFX_GRAYSTRETCHDLG_H__76F89B7F_5101_473E_AB8F_1ABD494E4B43__INCLUDED_)
#define AFX_GRAYSTRETCHDLG_H__76F89B7F_5101_473E_AB8F_1ABD494E4B43__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GrayStretchDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CGrayStretchDlg dialog

class AFX_EXT_CLASS CGrayStretchDlg : public CDialog
{
// Construction
public:
	CGrayStretchDlg(CWnd* pParent = NULL);   // standard constructor
	BYTE *lpOut;int nWidth,nHeight;int nByteWidth,nBits;
	unsigned char* m_pTempBits;BYTE *lpBits;
	BOOL GrayStrentch();
    void getmembers(BITMAPINFO *m_pBIH,HDC t1,int m_nWidth,int m_nHeight,int m_nByteWidth,BYTE *m_lpOut);
// Dialog Data
	//{{AFX_DATA(CGrayStretchDlg)
	enum { IDD = IDD_STRETCH };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGrayStretchDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGrayStretchDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GRAYSTRETCHDLG_H__76F89B7F_5101_473E_AB8F_1ABD494E4B43__INCLUDED_)
