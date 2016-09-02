// MedianFiltDlg.cpp : implementation file
//

#include "stdafx.h"
//#include "	\ add additional includes here"
#include "MedianFiltDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMedianFiltDlg dialog
BYTE *lpBits;
int m_nByteWidth,m_nHeight,m_nBits,m_nWidth;
void CMedianFiltDlg::getmember(int nWidth,int nHeight,int nByteWidth,int nBits,BYTE *m_lpOut)
{
	m_nWidth = nWidth;
	m_nHeight = nHeight;
	m_nByteWidth = nByteWidth;
	m_nBits = nBits;
	lpBits = m_lpOut;
	lpOut = m_lpOut;
}
CMedianFiltDlg::CMedianFiltDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMedianFiltDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMedianFiltDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CMedianFiltDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMedianFiltDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CMedianFiltDlg, CDialog)
	//{{AFX_MSG_MAP(CMedianFiltDlg)
	ON_BN_CLICKED(IDC_MEDFILT_CHANGETOSIZE3, OnMedfiltChangetosize3)
	ON_BN_CLICKED(IDC_MEDFILT_CHANGETOSIZE5, OnMedfiltChangetosize5)
	ON_BN_CLICKED(IDC_MEDFILT_CHANGETOSIZE7, OnMedfiltChangetosize7)
	ON_BN_CLICKED(IDC_MEDFILT_CHANGETOSIZE9, OnMedfiltChangetosize9)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMedianFiltDlg message handlers

void CMedianFiltDlg::OnMedfiltChangetosize3() 
{
	// TODO: Add your control notification handler code here
	m_iWinSize=3;
}

void CMedianFiltDlg::OnMedfiltChangetosize5() 
{
	// TODO: Add your control notification handler code here
	m_iWinSize=5;
}

void CMedianFiltDlg::OnMedfiltChangetosize7() 
{
	// TODO: Add your control notification handler code here
	m_iWinSize=7;
}

void CMedianFiltDlg::OnMedfiltChangetosize9() 
{
	// TODO: Add your control notification handler code here
	m_iWinSize=9;
}
BOOL CMedianFiltDlg::MedianFilter(int m_iWinSize)
{
	
	lpOut=new BYTE[m_nByteWidth*m_nHeight];
	/***************Median filter**********************/
	//define a template of the median filter
	int iAmount = m_iWinSize*m_iWinSize;
	int* piTemplate = new int[iAmount];
	for (int k=0; k<iAmount; k++)
	{
		piTemplate[k] = 0;
	}
	
	// the original processing point
	int iX = m_iWinSize / 2;
	int iY = m_iWinSize / 2;
	int iMedIndex = iAmount / 2;
	
	// begin to process
	int i,j,ii,jj;
	switch (m_nBits)
	{
	case 8:
		// image loop
		for(j=iY; j<m_nHeight-iY; j++)
		{		
			for (i=iX; i<m_nWidth-iX; i++)
			{
				//template loop
				for (jj=0; jj<m_iWinSize; jj++)
				{
					for (ii=0; ii<m_iWinSize; ii++)
					{
						//Get gray value of the pixel in line(j-iY+jj) and column(i-iX+ii)

						piTemplate[jj*m_iWinSize+ii] = lpBits[(m_nHeight-1-(j-iY+jj))*m_nByteWidth+(i-iX+ii)];
						
					}
				}
				
				//Sort the elements in the template                                   
				BubbleSort(piTemplate,iAmount);
				//Get the median value in the template
				lpOut[(m_nHeight-1-j)*m_nByteWidth+i] = piTemplate[iMedIndex];
			}
		}
		break;			
	case 16:			
		break;
	case 24:
		break;
	case 32:
		break;
	}
	
	delete [] piTemplate;
	piTemplate = NULL;
	return TRUE;
}
inline BOOL CMedianFiltDlg::BubbleSort(int *pdData, int iAmount)
{
	ASSERT(pdData != NULL);
	if (iAmount <= 0)
	{
		return FALSE;
	}
	
	int dTemp = 0;
	for (int j = iAmount-1; j>=0; j--)
	{
		for (int i = 0; i<j; i++)
		{
			if (pdData[i] > pdData[i+1])
			{
				dTemp = pdData[i];
				pdData[i] = pdData[i+1];
				pdData[i+1] = dTemp;
			}
		}
	}
	return TRUE;
}
BOOL CMedianFiltDlg::MaxFilter(int m_iWinSize)
{
	
	lpOut=new BYTE[m_nByteWidth*m_nHeight];
	/***************Median filter**********************/
	//define a template of the median filter
	int iAmount = m_iWinSize*m_iWinSize;
	int* piTemplate = new int[iAmount];
	for (int k=0; k<iAmount; k++)
	{
		piTemplate[k] = 0;
	}
	
	// the original processing point
	int iX = m_iWinSize / 2;
	int iY = m_iWinSize / 2;
	int iMedIndex = iAmount / 2;
	
	// begin to process
	int i,j,ii,jj;
	switch (m_nBits)
	{
	case 8:
		// image loop
		for(j=iY; j<m_nHeight-iY; j++)
		{		
			for (i=iX; i<m_nWidth-iX; i++)
			{
				//template loop
				for (jj=0; jj<m_iWinSize; jj++)
				{
					for (ii=0; ii<m_iWinSize; ii++)
					{
						//Get gray value of the pixel in line(j-iY+jj) and column(i-iX+ii)
						piTemplate[jj*m_iWinSize+ii] = lpBits[(m_nHeight-1-(j-iY+jj))*m_nByteWidth+(i-iX+ii)];							
					}
				}
				
				//Sort the elements in the template                                   
				BubbleSort(piTemplate,iAmount);
				//Get the median value in the template
				lpOut[(m_nHeight-1-j)*m_nByteWidth+i] = piTemplate[iAmount-1];
			}
		}
		break;			
	case 16:			
		break;
	case 24:
		break;
	case 32:
		break;
	}
	
	delete [] piTemplate;
	piTemplate = NULL;
	return TRUE;
}
BOOL CMedianFiltDlg::MinFilter(int m_iWinSize)
{
	
	lpOut=new BYTE[m_nByteWidth*m_nHeight];
	/***************Median filter**********************/
	//define a template of the median filter
	int iAmount = m_iWinSize*m_iWinSize;
	int* piTemplate = new int[iAmount];
	for (int k=0; k<iAmount; k++)
	{
		piTemplate[k] = 0;
	}
	
	// the original processing point
	int iX = m_iWinSize / 2;
	int iY = m_iWinSize / 2;
	int iMedIndex = iAmount / 2;
	
	// begin to process
	int i,j,ii,jj;
	switch (m_nBits)
	{
	case 8:
		// image loop
		for(j=iY; j<m_nHeight-iY; j++)
		{		
			for (i=iX; i<m_nWidth-iX; i++)
			{
				//template loop
				for (jj=0; jj<m_iWinSize; jj++)
				{
					for (ii=0; ii<m_iWinSize; ii++)
					{
						//Get gray value of the pixel in line(j-iY+jj) and column(i-iX+ii)
						piTemplate[jj*m_iWinSize+ii] = lpBits[(m_nHeight-1-(j-iY+jj))*m_nByteWidth+(i-iX+ii)];							
					}
				}
				
				//Sort the elements in the template        
				BubbleSort(piTemplate,iAmount);
				//Get the median value in the template
				lpOut[(m_nHeight-1-j)*m_nByteWidth+i] = piTemplate[0];
			}
		}
		break;			
	case 16:			
		break;
	case 24:
		break;
	case 32:
		break;
	}
	
	delete [] piTemplate;
	piTemplate = NULL;
	return TRUE;
}
BOOL CMedianFiltDlg::EaualizeFilter(int m_iWinSize)
{
	
	lpOut=new BYTE[m_nByteWidth*m_nHeight];
	/***************Median filter**********************/
	//define a template of the median filter
	int iAmount = m_iWinSize*m_iWinSize;
	int* piTemplate = new int[iAmount];
	for (int k=0; k<iAmount; k++)
	{
		piTemplate[k] = 0;
	}
	
	// the original processing point
	int iX = m_iWinSize / 2;
	int iY = m_iWinSize / 2;
	int iMedIndex = iAmount / 2;
	
	// begin to process
	int i,j,ii,jj;
	switch (m_nBits)
	{
	case 8:
		// image loop
		for(j=iY; j<m_nHeight-iY; j++)
		{		
			for (i=iX; i<m_nWidth-iX; i++)
			{
				//template loop
				for (jj=0; jj<m_iWinSize; jj++)
				{
					for (ii=0; ii<m_iWinSize; ii++)
					{
						//Get gray value of the pixel in line(j-iY+jj) and column(i-iX+ii)
						piTemplate[jj*m_iWinSize+ii] = lpBits[(m_nHeight-1-(j-iY+jj))*m_nByteWidth+(i-iX+ii)];							
					}
				}
				
				//Sort the elements in the template                                   
				BubbleSort(piTemplate,iAmount);
				for (int m = 0;m < iAmount - 1; m++)
				{
					piTemplate[0]+=piTemplate[m];
				}
					piTemplate[0]/=m+1;
				//Get the median value in the template
				lpOut[(m_nHeight-1-j)*m_nByteWidth+i] = piTemplate[0];
			}
		}
		break;			
	case 16:			
		break;
	case 24:
		break;
	case 32:
		break;
	}
	
	delete [] piTemplate;
	piTemplate = NULL;
	return TRUE;
}
