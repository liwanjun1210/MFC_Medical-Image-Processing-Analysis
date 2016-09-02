// COMPLEX.cpp: implementation of the CCOMPLEX class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "COMPLEX.h"

#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCOMPLEX::CCOMPLEX()
{

}

CCOMPLEX::~CCOMPLEX()
{

}


COMPLEX Add(COMPLEX c1, COMPLEX c2)
{
	COMPLEX c;
	c.re=c1.re+c2.re;
	c.im=c1.im+c2.im;
	return c;
}

/*complex substract*/
COMPLEX Sub(COMPLEX c1, COMPLEX c2)
{
	COMPLEX c;
	c.re=c1.re-c2.re;
	c.im=c1.im-c2.im;
	return c;
}

/*complex multiple*/
COMPLEX Mul(COMPLEX c1, COMPLEX c2)
{
	COMPLEX c;
	c.re=c1.re*c2.re-c1.im*c2.im;
	c.im=c1.re*c2.im+c2.re*c1.im;
	return c;
}

/*complex divide*/
COMPLEX Div(COMPLEX c1, COMPLEX c2) //  c1/c2
{
	COMPLEX c;
	double temp;
	temp = c2.re*c2.re+c2.im*c2.im;
	c.re=(c1.re*c2.re+c1.im*c2.im)/temp;
	c.im=(c1.im*c2.re-c1.re*c2.im)/temp;
	return c;
}

void CCOMPLEX::FFT(COMPLEX * TD, COMPLEX * FD, int power)
{
	int count;
	int i,j,k,bfsize,p;
	double angle;
	COMPLEX *W,*X1,*X2,*X;
	
	/*计算傅立叶变换点数*/
	count=1<<power;
	
	/*分配运算所需存储器*/
	W=(COMPLEX *)malloc(sizeof(COMPLEX)*count/2);
	X1=(COMPLEX *)malloc(sizeof(COMPLEX)*count);
	X2=(COMPLEX *)malloc(sizeof(COMPLEX)*count);
	
	/*计算加权系数*/
	for(i=0;i<count/2;i++)
	{
		angle=-i*PI*2/count;
		W[i].re=cos(angle);
		W[i].im=sin(angle);
	}
	
	/*将时域点写入存储器*/
	memcpy(X1,TD,sizeof(COMPLEX)*count);
	
	/*蝶形运算*/
	for(k=0;k<power;k++)
	{
		for(j=0;j<1<<k;j++)
		{
			bfsize=1<<(power-k);
			for(i=0;i<bfsize/2;i++)
			{
				p=j*bfsize;
				X2[i+p]=Add(X1[i+p],X1[i+p+bfsize/2]);
				X2[i+p+bfsize/2]=Mul(Sub(X1[i+p],X1[i+p+bfsize/2]),W[i*(1<<k)]);
			}
		}
		X=X1;
		X1=X2;
		X2=X;
	}
	
	/*重新排序*/
	for(j=0;j<count;j++)
	{
		p=0;
		for(i=0;i<power;i++)
		{
			if (j&(1<<i)) p+=1<<(power-i-1);
		}
		FD[j]=X1[p];
	}
	
	/*释放存储器*/
	free(W);
	free(X1);
	free(X2);
}

void CCOMPLEX::IFFT(COMPLEX * FD, COMPLEX * TD, int power)
{
	int i, count;
	COMPLEX *x;
	
	/*计算傅立叶反变换点数*/
	count=1<<power;
	
	/*分配运算所需存储器*/
	x=(COMPLEX *)malloc(sizeof(COMPLEX)*count);
	
	/*将频域点写入存储器*/
	memcpy(x,FD,sizeof(COMPLEX)*count);
	
	/*求频域点的共轭*/
	for(i=0;i<count;i++)
		x[i].im = -x[i].im;
	
	/*调用FFT*/
	FFT(x, TD, power);
	
	/*求时域点的共轭*/
	for(i=0;i<count;i++)
	{
		TD[i].re /= count;
		TD[i].im = -TD[i].im / count;
	}
	
	/*释放存储器*/
	free(x);
}

//计算点(x1,y1)与点(x2,y2)之间的距离
double CCOMPLEX::Distance(int x1, int y1, int x2, int y2)
{
	double result = 0.0;
	result = sqrt((y2-y1)*(y2-y1) + (x2-x1)*(x2-x1));
	return result;
}

void CCOMPLEX::Calculate(COMPLEX *&FILTER, int nCutoffFreq, int nOrder, int w, int h, int TYPE)
{
	int i, j;
	double pow2nOrder;
	switch(TYPE)
	{
	case BWLOWPASS:
		for (j=0; j<h; j++)
		{
			for (i=0; i<w; i++)
			{
				pow2nOrder = pow(Distance(i,j, w/2,h/2)/nCutoffFreq , 2*nOrder);
				FILTER[i + j*w].re = 1/(1+pow2nOrder);
				FILTER[i + j*w].im = 0;
			}
		}
		break;
	case BWHIGHPASS:
		for (j=0; j<h; j++)
		{
			for (i=0; i<w; i++)
			{
				if (Distance(i,j, w/2,h/2) < 1)
				{
					FILTER[i + j*w].re = 0;
				}
				else
				{
					pow2nOrder = pow(nCutoffFreq/Distance(i,j, w/2,h/2) , 2*nOrder);
					FILTER[i + j*w].re = 1/(1+pow2nOrder);
					FILTER[i + j*w].im = 0;
				}
			}
		}
		break;
	default:
		break;
	}
}

void CCOMPLEX::Calculate(COMPLEX *&FILTER, float fGammaH, float fGammaL, int nCutoffFreq, int w, int h)
{
	int i, j;
	int c = 1;	//注：常数 c 被引入用来控制滤波器函数斜面的陡度，用户不做设置，设置由程序员完成
	double expTemp;
	for (j=0; j<h; j++)
	{
		for (i=0; i<w; i++)
		{
			expTemp = exp(-c*(Distance(i,j, w/2,h/2) * Distance(i,j, w/2,h/2) / nCutoffFreq / nCutoffFreq));
			FILTER[i + j*w].re = (fGammaH - fGammaL)*(1 - expTemp) + fGammaL;
			FILTER[i + j*w].im = 0;
		}
	}
}

void CCOMPLEX::AtmosphTurbuDegeModel(COMPLEX* &Model, int w, int h, double Para_k)
{
	int i, j;
	double powTemp;
	for (j=0; j<h; j++)
	{
		for (i=0; i<w; i++)
		{
			powTemp = pow(((i-w/2)*(i-w/2) + (j-h/2)*(j-h/2)),5.0/6);
			Model[i + j*w].re = exp(-Para_k*powTemp);
			Model[i + j*w].im = 0;
		}
	}
}

void CCOMPLEX::MotionDegenerateModel(COMPLEX* &Model, int w, int h, double Para_a, double Para_b, double Para_T)
{
	int i, j;
	double Temp;
	for (j=0; j<h; j++)
	{
		for (i=0; i<w; i++)
		{
			if (i==w/2 && j==h/2)
				Temp = Para_T;
			else
				Temp = Para_T*sin(PI*((i-w/2)*Para_a+(j-h/2)*Para_b))/(PI*((i-w/2)*Para_a+(j-h/2)*Para_b));
			Model[i + j*w].re = Temp*sin(PI*((i-w/2)*Para_a+(j-h/2)*Para_b));
			Model[i + j*w].im = Temp*cos(PI*((i-w/2)*Para_a+(j-h/2)*Para_b));
		}
	}
}