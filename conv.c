#include "stdio.h"
#include "R.h"
#include "Rinternals.h"
#include "stdlib.h"

void valid_conv(double * A, double * B,int m_A, int n_A,int m_B,int n_B, \
	double * C)
{
  int i,j,m,n;
  for(i=0;i<m_A-m_B+1;++i)
  {
  	for(j=0;j<n_A-n_B+1;++j)
  	{
  		double s=0;
  		for(m=0;m<m_B;++m)
  		{
  			for(n=0;n<n_B;++n)
  			{
  				s+=A[(m+i)*n_A+n+j]*B[(m_B-m-1)*n_B+n_B-n-1];
  				//s+=1;
  			}
  		}
  	C[i*(n_A-n_B+1)+j]=s;
  	}
  }
}

void full_conv(double * A, double * B,int m_A, int n_A,int m_B,int n_B, \
	double * C)
{
  int i,j,m,n;
  int l_mB,l_nB;  
  for(i=0;i<m_A+m_B-1;++i)
  {
    l_mB=(i<m_A)?i+1:m_B-i+m_A-1;
    l_mB=(m_B<l_mB)?m_B:l_mB;

  	for(j=0;j<n_A+n_B-1;++j)
  	{	
  		l_nB=(j<n_A)?j+1:n_B-j+n_A-1;
  		l_nB=(n_B<l_nB)?n_B:l_nB;
  		double s=0;
  		for(m=0;m<l_mB ;++m)
  		{
  			for(n=0;n<l_nB;++n)
  			{
  				 // s+=A[(m+i)*n_A+n+j]*B[];
  				 s+=1;
  			}
  		}
  	C[i*(n_A+n_B-1)+j]=s;
  	}
  }
}

void full_conv2(double * A, double * B, int m_A,\
 int n_A,int m_B,int n_B, double * C)  
 //mainpulate full convolution by aid of vaild mode
{
  int i,j;
  int nrow=2*m_B-2+m_A;
  int ncol=2*n_B-2+n_A;
  // double expand_A[nrow*ncol];
  double * Expand_A=(double *)calloc(nrow*ncol,sizeof(double));
  int cnt=0;
  for (i = m_B-1; i <m_A+m_B-1 ; ++i)
    {
      for (j =n_B-1; j <n_A+n_B-1; ++j)
        {
          Expand_A[i*ncol+j]=A[cnt];
          ++cnt;
        } 
    }
  valid_conv(Expand_A,B,nrow,ncol,m_B,n_B,C);
  free(Expand_A);
}


void same_conv(double * A, double * B, int m_A,\
 int n_A,int m_B,int n_B, double * C)  
 //mainpulate same convolution by aid of vaild mode
{
  int i,j;
  int nrow=m_B+m_A-1;
  int ncol=n_B+n_A-1;
  int left_B=(int)(n_B/2);
  int up_B=(int)(m_B/2);
  double * Expand_A=(double *)calloc(nrow*ncol,sizeof(double));
  int cnt=0;
  for (i = left_B; i <m_A+left_B; ++i)
    {
      for (j =up_B; j <n_A+up_B; ++j)
        {
          Expand_A[i*ncol+j]=A[cnt];
          ++cnt;
        } 
    }
  valid_conv(Expand_A,B,nrow,ncol,m_B,n_B,C);
  free(Expand_A);
}


void valid_conv_ori(double * A, double * B,int *ma, int *na,int * mb,int * nb, \
	double * C)
{
  int i,j,m,n;
  int m_A=*ma,m_B=*mb,n_A=*na,n_B=*nb;
  for(i=0;i<m_A-m_B+1;++i)
  {
  	for(j=0;j<n_A-n_B+1;++j)
  	{
  		double s=0;
  		for(m=0;m<m_B;++m)
  		{
  			for(n=0;n<n_B;++n)
  			{
  				s+=A[(m+i)*n_A+n+j]*B[(m_B-m-1)*n_B+n_B-n-1];
  				//s+=1;
  			}
  		}
  	C[i*(n_A-n_B+1)+j]=s;
  	}
  }
}


// int main()
// {
// double a[]={1,2,3,4,5,6,7,8,9};
// double b[]={1,2,3,4};
// int ma=3,na=3;
// int mb=2,nb=2;
// // double c[(ma-mb+1)*(na-nb+1)];
// // valid_conv(a,b,ma,na,mb,nb,c);
// // int i;
// // for(i=0;i<(ma-mb+1)*(na-nb+1);++i)
// // 	printf("%5.2lf \n",c[i]);
// double c[(ma+mb-1)*(na+nb-1)];
// double expand_a[(2*mb-2+ma)*(2*nb-2+na)];
// full_conv2(a,b,expand_a,ma,na,mb,nb,2*mb-2+ma,2*nb-2+na,c);
// int i;
// for(i=0;i<(ma+mb-1)*(na+nb-1);++i)
// 	printf("%5.2lf \n",c[i]);
// return 0;
// }

SEXP r_valid_conv(SEXP r_A, SEXP r_B, SEXP r_m_A, SEXP r_n_A,SEXP r_m_B, SEXP r_n_B)
{
  double *A=REAL(r_A);
  double *B=REAL(r_B);
  int m_A=INTEGER(r_m_A)[0]; 
  int n_A=INTEGER(r_n_A)[0]; 
  int m_B=INTEGER(r_m_B)[0];
  int n_B=INTEGER(r_n_B)[0];
  SEXP conv;
  int len=(m_A-m_B+1)*(n_A-n_B+1);
  PROTECT(conv=allocVector(REALSXP,len));
  double *p=REAL(conv);
  valid_conv(A,B,m_A,n_A,m_B,n_B,p);
  UNPROTECT(1);
  return(conv);
}

SEXP r_full_conv(SEXP r_A, SEXP r_B, SEXP r_m_A, SEXP r_n_A,SEXP r_m_B, SEXP r_n_B)
{
  double *A=REAL(r_A);
  double *B=REAL(r_B);
  int m_A=INTEGER(r_m_A)[0]; 
  int n_A=INTEGER(r_n_A)[0]; 
  int m_B=INTEGER(r_m_B)[0];
  int n_B=INTEGER(r_n_B)[0];
  SEXP conv;
  int len=(m_A+m_B-1)*(n_A+n_B-1);
  PROTECT(conv=allocVector(REALSXP,len));
  double * p=REAL(conv);
  full_conv2(A,B,m_A,n_A,m_B,n_B,p);
  UNPROTECT(1);
  return(conv);
}

SEXP r_same_conv(SEXP r_A, SEXP r_B, SEXP r_m_A, SEXP r_n_A,SEXP r_m_B, SEXP r_n_B)
{
  double *A=REAL(r_A);
  double *B=REAL(r_B);
  int m_A=INTEGER(r_m_A)[0]; 
  int n_A=INTEGER(r_n_A)[0]; 
  int m_B=INTEGER(r_m_B)[0];
  int n_B=INTEGER(r_n_B)[0];
  SEXP conv;
  int len=m_A*n_A;
  PROTECT(conv=allocVector(REALSXP,len));
  double * p=REAL(conv);
  same_conv(A,B,m_A,n_A,m_B,n_B,p);
  UNPROTECT(1);
  return(conv);
}



