// HisEqlize.h: interface for the CHisEqlize class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HISEQLIZE_H__6764CF24_000D_44A9_A912_C5C1C9051B7C__INCLUDED_)
#define AFX_HISEQLIZE_H__6764CF24_000D_44A9_A912_C5C1C9051B7C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class AFX_EXT_CLASS CHisEqlize  
{
public:
	CHisEqlize();
	virtual ~CHisEqlize();
	void HistEq(int m_nBits,int nWidth,int nHeight,int nByteWidth,BYTE *lpBits);
	void HistFunc(int len,BYTE *lpBits);
	BYTE *lpOut;

};

#endif // !defined(AFX_HISEQLIZE_H__6764CF24_000D_44A9_A912_C5C1C9051B7C__INCLUDED_)
