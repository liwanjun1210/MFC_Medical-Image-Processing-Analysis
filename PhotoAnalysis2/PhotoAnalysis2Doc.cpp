// PhotoAnalysis2Doc.cpp : implementation of the CPhotoAnalysis2Doc class
//

#include "stdafx.h"
#include "PhotoAnalysis2.h"

#include "PhotoAnalysis2Doc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPhotoAnalysis2Doc

IMPLEMENT_DYNCREATE(CPhotoAnalysis2Doc, CDocument)

BEGIN_MESSAGE_MAP(CPhotoAnalysis2Doc, CDocument)
	//{{AFX_MSG_MAP(CPhotoAnalysis2Doc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPhotoAnalysis2Doc construction/destruction

CPhotoAnalysis2Doc::CPhotoAnalysis2Doc()
{
	// TODO: add one-time construction code here

}

CPhotoAnalysis2Doc::~CPhotoAnalysis2Doc()
{
}

BOOL CPhotoAnalysis2Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)

	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CPhotoAnalysis2Doc serialization

void CPhotoAnalysis2Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CPhotoAnalysis2Doc diagnostics

#ifdef _DEBUG
void CPhotoAnalysis2Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CPhotoAnalysis2Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CPhotoAnalysis2Doc commands

