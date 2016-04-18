#include "stdio.h"
#include "stdlib.h"
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
		(*avg_value)+=A[i];
	(*avg_value)=(*avg_value)/len;
}

void fill(double *A, int n_A, double * B, int nr, int nc, int rth, int cth)
{
	int m,n,cnt=0;
	for (m = 0; m<nr; ++m)
	{
		for (n = 0; n < nc; ++n)
		{
			B[cnt]=A[(rth+m)*n_A+n+cth];
			++cnt;
		}
	}
}

void down_sample(double * A, double * B, \
	int m_A, int n_A, int nr, int nc,\
	void (*f)(double *, int, double *))
{
   int i,j,cnt=0;
   int len=nr*nc;
   int m_E_A,n_E_A;
   double * tmp=(double *)calloc(len,sizeof(double));
   // double tmp[len];
   double pool_value;
   int mod_nr=m_A%nr;
   int mod_nc=n_A%nc;
   double * Expand_A;
   ////padding the boundary if necessary
   if(mod_nr==0 && mod_nc==0)  
   {
		Expand_A=A;
		m_E_A=m_A;
		n_E_A=n_A;
   }
   else
   {
		m_E_A=m_A-mod_nr+nr;
		n_E_A=n_A-mod_nc+nc;
   		Expand_A=(double *)calloc(m_E_A*n_E_A,sizeof(double));
		for(i=0;i<m_A;++i)
	   	{
	   		for (j = 0; j<n_A;++j)
	   		{
	   			Expand_A[i*n_E_A+j]=A[cnt];
	   			++cnt;
	   		}

	   	}	
   }
   ////

   cnt=0;
   
   for(i=0;i<m_E_A;i+=nr)
   {
   		for (j = 0; j<n_E_A;j+=nc)
   		{
   			 fill(Expand_A,n_E_A,tmp,nr,nc,i,j);
   			 (*f)(tmp,len,&pool_value);
	   		 B[cnt]=pool_value;
   			 ++cnt;
   		}

   }
   free(tmp);
   if(mod_nr!=0 || mod_nc!=0) 
   free(Expand_A);
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
double a[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25};
int ma=5,na=5;
int nr=2,nc=2;
int len=((int)(ma/nr)+1)*((int)(na/nc)+1);
double b[len];
down_sample(a, b,ma, na,  nr, nc,max);
int i;
for(i=0;i<len;++i)
	printf("%5.2lf \n",b[i]);
//  double b[ma*nr*na*nc];
// up_sample(a,b,ma,na,nr,nc);
// int i,j;
//  for(i=0;i<ma*nr;++i)
// 	{
//  	 for(j=0;j<na*nc;++j)
// 		printf("%5.2lf ",b[i*(na*nc)+j]);
// 	printf("\n");
// 	}
return 0;
}


