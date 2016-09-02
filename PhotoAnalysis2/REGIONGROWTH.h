#if !defined(AFX_REGIONGROWTH_H__A295ABBA_9C4E_470A_9468_E2AE53C46C63__INCLUDED_)
#define AFX_REGIONGROWTH_H__A295ABBA_9C4E_470A_9468_E2AE53C46C63__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// REGIONGROWTH.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CREGIONGROWTH dialog
class CREGIONGROWTH : public CDialog
{
// Construction
public:
	CREGIONGROWTH(CWnd* pParent = NULL);   // standard constructor
void OnReGrow() ;
//CPhotoAnalysis2View *bm;
BYTE *lpbits_trans;	
BYTE *lpbits;
void Growing(BYTE *seedmap,int delta);
void getmember(BITMAPINFO *m_pBIH,HDC t1,int m_nWidth,int m_nHeight,int m_nByteWidth,BYTE *m_lpBits,BYTE *m_lpOut);
BYTE *lpOut;BYTE *lpBits;HDC T1;BITMAPINFO *pBIH;
int p_ByteWidth,p_Height,m_Color,p_Width,m_nBits;

// Dialog Data
	//{{AFX_DATA(CREGIONGROWTH)
	enum { IDD = IDD_DIALOG_REGIONGROWTH };
	int		m_pX;
	int		m_pY;
	int		m_th;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CREGIONGROWTH)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CREGIONGROWTH)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_REGIONGROWTH_H__A295ABBA_9C4E_470A_9468_E2AE53C46C63__INCLUDED_)
