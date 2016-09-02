#if !defined(AFX_ZOOMRATEDLG_H__814CF43C_3D25_41E7_9117_924BA67FCF70__INCLUDED_)
#define AFX_ZOOMRATEDLG_H__814CF43C_3D25_41E7_9117_924BA67FCF70__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZoomRateDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CZoomRateDlg dialog

class AFX_EXT_CLASS CZoomRateDlg : public CDialog
{
// Construction
public:
	CZoomRateDlg(CWnd* pParent = NULL);   // standard constructor
	BYTE *lpOut;
	int T_Height,T_Width,newByteWidth;
	void Zoom( int m_nWidth,int m_nHeight,int m_nByteWidth,	BITMAPINFOHEADER *pNewBIH,BYTE *lpBits);
// Dialog Data
	//{{AFX_DATA(CZoomRateDlg)
	enum { IDD = IDD_ZOOM_RATE };
	float	m_fZoomRateHeight;
	float	m_fZoomRateWidth;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZoomRateDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CZoomRateDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZOOMRATEDLG_H__814CF43C_3D25_41E7_9117_924BA67FCF70__INCLUDED_)
