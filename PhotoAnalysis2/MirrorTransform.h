// MirrorTransform.h: interface for the MirrorTransform class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MIRRORTRANSFORM_H__EE8B7254_CC28_43AE_B68D_01153909646A__INCLUDED_)
#define AFX_MIRRORTRANSFORM_H__EE8B7254_CC28_43AE_B68D_01153909646A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class AFX_EXT_CLASS CMirrorTransform  
{
public:
	CMirrorTransform();
	virtual ~CMirrorTransform();
	void Mirror(int nDircFlag);
	void getmember(int nWidth,int nHeight,int nByteWidth,int nBits,BYTE *m_lpOut);
	BYTE* lpOut;
};

#endif // !defined(AFX_MIRRORTRANSFORM_H__EE8B7254_CC28_43AE_B68D_01153909646A__INCLUDED_)
