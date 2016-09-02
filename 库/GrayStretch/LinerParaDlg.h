#if !defined(AFX_LINERPARADLG_H__039BB21D_3CE3_4618_8B96_D664E92E20A3__INCLUDED_)
#define AFX_LINERPARADLG_H__039BB21D_3CE3_4618_8B96_D664E92E20A3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LinerParaDlg.h : header file
//
#include "resource.h"
/////////////////////////////////////////////////////////////////////////////
// CLinerParaDlg dialog

class AFX_EXT_CLASS CLinerParaDlg : public CDialog
{
// Construction
public:
	CLinerParaDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
public:	
	BOOL	m_bDrawed;			// 标识是否已经绘制橡皮筋线	
	CPoint	m_p1;				// 保存鼠标左键单击时的位置	
	CPoint	m_p2;				// 保存鼠标拖动时的位置	
	BOOL	m_bIsDraging;		// 当前鼠标拖动状态，TRUE表示正在拖动。	
	CRect	m_MouseRect;		// 相应鼠标事件的矩形区域
//	BYTE *lpOut;
	void LinerTrans();
	BYTE *lpOut;BYTE *lpBits;
	void getmembers(BITMAPINFO *m_pBIH,HDC t1,int m_nWidth,int m_nHeight,int m_nByteWidth,BYTE *m_lpOut);

	//{{AFX_DATA(CLinerParaDlg)
	enum { IDD = IDD_DLG_LINERPARA };
	float	m_fA;
	float	m_fB;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLinerParaDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLinerParaDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnKillfocusEditA();
	afx_msg void OnKillfocusEditB();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LINERPARADLG_H__039BB21D_3CE3_4618_8B96_D664E92E20A3__INCLUDED_)
