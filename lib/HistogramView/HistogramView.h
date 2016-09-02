// HistogramView.h : main header file for the HISTOGRAMVIEW DLL
//

#if !defined(AFX_HISTOGRAMVIEW_H__0FE4047A_67F5_4FC5_B7AF_D7C6C79F55C2__INCLUDED_)
#define AFX_HISTOGRAMVIEW_H__0FE4047A_67F5_4FC5_B7AF_D7C6C79F55C2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif
#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CHistogramViewApp
// See HistogramView.cpp for the implementation of this class
//

class __declspec(dllexport) CHistogramViewApp : public CWinApp
{
public:
	CHistogramViewApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHistogramViewApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CHistogramViewApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HISTOGRAMVIEW_H__0FE4047A_67F5_4FC5_B7AF_D7C6C79F55C2__INCLUDED_)
