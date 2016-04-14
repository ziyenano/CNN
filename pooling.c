#include "stdio.h"
#include "math.h"
void max(double * A, int len, double * max_value)
{
	int i;
	*max_value=A[0];
	for (i = 1; i < len; ++i)
	{
		if(A[i]>*max_value) 
			*max_value=A[i];
	}
}

void avg(double * A, int len, double * avg_value)
{
	int i;
	*avg_value=0;
	for (i = 0; i < len; ++i)
		*avg_value+=A[i];
	*avg_value=*avg_value/len;
}

void fill(double *A, int m_A, double * B, int nr, int nc, int rth, int cth)
{
	int m,n,cnt=0;
	for (m = 0; m<nr; ++m)
	{
		for (n = 0; n < nc; ++n)
		{
			B[cnt]=A[(rth+m)*m_A+n+cth];
			++cnt;
		}
	}
}

void down_sample(double * A, double * B, int mod_nr, int mod_nc, \
	int m_A, int n_A, int nr, int nc)
{
   int i,j,cnt;
   int len=nr*nc;
   double tmp[len];
   double pool_value;
   int b_cnt=0;
   	for(i=0;i<m_A;i+=nr)
   	{
   		for (j = 0; j<n_A;j+=nc)
   		{
   			fill(A,m_A,tmp,nr,nc,i,j);
   			avg(tmp,len,&pool_value);
   			B[b_cnt]=pool_value;
   			++b_cnt;
   		}
   	}
}

void up_sample(double * A, double * B, 
	int m_A, int n_A, int nr, int nc)
{
	int i,j,m,n;
	int m_B=nr*m_A;
	int n_B=nc*n_A;
	for(i=0;i<m_A;++i)
	{
		for(j=0;j<n_A;++j)
		{
			for (m = 0; m < nr; ++m)
			{
				for (n = 0; n < nc; ++n)
					B[(i*nr+m)*m_B+j*nc+n]=A[i*m_A+j];
			}
		}
	}
}




int main()
{
double a[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
int ma=4,na=4;
int nr=2,nc=2;
// double b[(int)(ma/nr)*(int)(na/nc)];
// down_sample(a, b, 0,0, 
// 	ma, na,  nr,  nc);
// int i;
// for(i=0;i<4;++i)
// 	printf("%5.2lf \n",b[i]);
 double b[ma*nr*na*nc];
up_sample(a,b,ma,na,nr,nc);
int i,j;
 for(i=0;i<ma*nr;++i)
	{
 	 for(j=0;j<na*nc;++j)
		printf("%5.2lf ",b[i*(na*nc)+j]);
	printf("\n");
	}
return 0;
}


