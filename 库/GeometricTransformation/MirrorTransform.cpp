// MirrorTransform.cpp: implementation of the MirrorTransform class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MirrorTransform.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
int m_nByteWidth,m_nHeight,m_nBits,m_nWidth;
BYTE *lpBits;
void CMirrorTransform::getmember(int nWidth,int nHeight,int nByteWidth,int nBits,BYTE *m_lpOut)
{
	m_nWidth = nWidth;
	m_nHeight = nHeight;
	m_nByteWidth = nByteWidth;
	m_nBits = nBits;
	lpBits = m_lpOut;
	lpOut = m_lpOut;
}
CMirrorTransform::CMirrorTransform()
{

}

CMirrorTransform::~CMirrorTransform()
{

}
void CMirrorTransform::Mirror(int nDircFlag)
{
	lpOut=new BYTE [m_nByteWidth*m_nWidth];
	if (lpBits == NULL)
	{
		return ;
	}
	int i, j;
	switch(m_nBits)
	{
	case 8:
		for (j=0; j<m_nHeight; j++)
		{
			for (i=0; i<m_nWidth; i++)
			{
				if (nDircFlag == 0)	//Ë®Æ½¾µÏñ
					lpOut[(m_nHeight-1-j)*m_nByteWidth + i] = lpBits[(m_nHeight-1-j)*m_nByteWidth + (m_nWidth-1-i)];
				else if(nDircFlag == 1)	//´¹Ö±¾µÏñ
					lpOut[(m_nHeight-1-j)*m_nByteWidth + i] = lpBits[j*m_nByteWidth + i];
			}
		}
		break;
	case 16:
		break;
	case 24:
		break;
	case 32:
		break;
	default:
		break;
	}
}
