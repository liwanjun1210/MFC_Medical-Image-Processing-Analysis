// PhotoAnalysis2Doc.h : interface of the CPhotoAnalysis2Doc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_PHOTOANALYSIS2DOC_H__81A75B1E_E538_48FB_A47E_7421B070400F__INCLUDED_)
#define AFX_PHOTOANALYSIS2DOC_H__81A75B1E_E538_48FB_A47E_7421B070400F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CPhotoAnalysis2Doc : public CDocument
{
protected: // create from serialization only
	CPhotoAnalysis2Doc();
	DECLARE_DYNCREATE(CPhotoAnalysis2Doc)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPhotoAnalysis2Doc)
	public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CPhotoAnalysis2Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CPhotoAnalysis2Doc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PHOTOANALYSIS2DOC_H__81A75B1E_E538_48FB_A47E_7421B070400F__INCLUDED_)
