#if !defined(AFX_GET_RGB_H__BBCF6752_2D01_4251_AFB1_E705105B9595__INCLUDED_)
#define AFX_GET_RGB_H__BBCF6752_2D01_4251_AFB1_E705105B9595__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Get_RGB.h : header file
//
extern "C" __declspec(dllexport) void Show();
/////////////////////////////////////////////////////////////////////////////
// CGet_RGB dialog
#define GETRGB888( a, b, c, d ) { DWORD *dwData = (DWORD *) d; a = (unsigned char) ( (*dwData) >> 16 ); b = (unsigned char) ( ( (*dwData) & 0x0000ff00 ) >> 8 ); c = (unsigned char) ( (*dwData) & 0x000000ff ); }
#define GETRGB555( a, b, c, d ) { WORD *wData = (WORD *) d; a = (unsigned char) ( ( (*wData) & 0x7c00 ) >> 7 ); b = (unsigned char) ( ( (*wData) & 0x03e0 ) >> 2 ); c = (unsigned char) ( ( (*wData) & 0x001f ) << 3 ); }
class  __declspec(dllexport)CGet_RGB : public CDialog
{
// Construction
public:
	CGet_RGB(CWnd* pParent = NULL);   // standard constructor
	void GetRGBValue(int x,int y);
	unsigned char red, green, blue;
	//	unsigned char& red,unsigned char& green,unsigned char& blue,int nByteWidth,char *lpBits);
	void GetMembers(int nWidth,int nHeight,int nBits,int mByteWidth,BYTE *m_lpOut);
// Dialog Data
	//{{AFX_DATA(CGet_RGB)
	enum { IDD = IDD_DIALOG_SHOWRGB };
	int		m_Blue;
	int		m_Green;
	int		m_PointX;
	int		m_PointY;
	int		m_Red;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CGet_RGB)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CGet_RGB)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GET_RGB_H__BBCF6752_2D01_4251_AFB1_E705105B9595__INCLUDED_)
