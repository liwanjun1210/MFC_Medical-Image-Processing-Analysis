// PhotoAnalysis2.h : main header file for the PHOTOANALYSIS2 application
//

#if !defined(AFX_PHOTOANALYSIS2_H__EBEDD930_67F5_4F12_9028_545273DC0031__INCLUDED_)
#define AFX_PHOTOANALYSIS2_H__EBEDD930_67F5_4F12_9028_545273DC0031__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPhotoAnalysis2App:
// See PhotoAnalysis2.cpp for the implementation of this class
//

class CPhotoAnalysis2App : public CWinApp
{
public:
	CPhotoAnalysis2App();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPhotoAnalysis2App)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CPhotoAnalysis2App)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PHOTOANALYSIS2_H__EBEDD930_67F5_4F12_9028_545273DC0031__INCLUDED_)
