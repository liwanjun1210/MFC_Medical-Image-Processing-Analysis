// HisEqlize.cpp: implementation of the CHisEqlize class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "HisEqlize.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CHisEqlize::CHisEqlize()
{

}

CHisEqlize::~CHisEqlize()
{

}
void CHisEqlize::HistEq(int m_nBits,int nWidth,int nHeight,int nByteWidth,BYTE *lpBits)
{
	lpOut=new BYTE[nByteWidth*nHeight];	//创建输出数组
	int len = nHeight*nWidth;
	int x,y,p,p1;
	BYTE *red_Points=new BYTE[len];		//图像红色分量
	BYTE *green_Points=new BYTE[len];	//图像绿色分量
	BYTE *blue_Points=new BYTE[len];	//图像蓝色分量
	
	switch(m_nBits)
	{
	case 8:
		for (y=0;y<nHeight;y++)
		{
			for(x=0;x<nWidth;x++)
			{
				p=x+y*nByteWidth;
				lpOut[p]=lpBits[p];
			}
		}
		HistFunc(len,lpOut);
		break;
	case 24:
		for(y=0;y<nHeight;y++)
		{
			for(x=0;x<nWidth;x++)
			{
				p=x*3+y*nByteWidth;
				red_Points[x+y*nWidth]=lpBits[p];		//红色分量提取
				green_Points[x+y*nWidth]=lpBits[p+1];	//绿色分量提取
				blue_Points[x+y*nWidth]=lpBits[p+2];	//蓝色分量提取
			}
		}
		
		HistFunc(len,red_Points);			//分别对3色通道做直方图均衡化处理
		HistFunc(len,green_Points);
		HistFunc(len,blue_Points);
		
		for(y=0;y<nHeight;y++)				//将处理完的3色通道数据存入输出数组
		{
			for(x=0;x<nWidth;x++)
			{
				p=x*3+y*nByteWidth;
				p1=x+y*nWidth;
				lpOut[p]=red_Points[p1];
				lpOut[p+1]=green_Points[p1];
				lpOut[p+2]=blue_Points[p1];
			}
		}
		delete []red_Points;
		delete []green_Points;
		delete []blue_Points;
		break;
	}
}

void CHisEqlize::HistFunc(int len,BYTE *lpBits)
{
	int i;
	int GP[256],S[256];			//GP为直方图数组，S为分布函数数组，都是256色
	ZeroMemory(GP,1024);			//初始化数组为0;ps:注意长度不是256，而是256*sizeof(int)
	ZeroMemory(S,1024);
	for(i=0;i<len;i++)
		GP[lpBits[i]]++;	//#define Point(x,y) lpPoints[(x)+(y)*nWidth]	//直方图数组//统计每个灰度值的像素个数
	
	S[0]=GP[0];
	for(i=1;i<256;i++)
	{
		S[i]=S[i-1];
		S[i]+=GP[i];
	}
	for(i=0;i<len;i++)
		lpBits[i]=S[lpBits[i]]*255/len;	//#define Point(x,y) lpPoints[(x)+(y)*nWidth]
}