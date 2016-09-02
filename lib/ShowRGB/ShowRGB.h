// ShowRGB.h : main header file for the SHOWRGB DLL
//

#if !defined(AFX_SHOWRGB_H__424BC90F_4BDF_4526_8DB2_7173DD282152__INCLUDED_)
#define AFX_SHOWRGB_H__424BC90F_4BDF_4526_8DB2_7173DD282152__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CShowRGBApp
// See ShowRGB.cpp for the implementation of this class
//

class CShowRGBApp : public CWinApp
{
public:
	CShowRGBApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CShowRGBApp)
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CShowRGBApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SHOWRGB_H__424BC90F_4BDF_4526_8DB2_7173DD282152__INCLUDED_)
