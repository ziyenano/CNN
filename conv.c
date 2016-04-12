#include "stdio.h"
// #include "R.h"
// #include "Rinternals.h"

void valid_conv(double * A, double * B,size_t m_A, size_t n_A,size_t m_B,size_t n_B, \
	double * C)
{
  size_t i,j,m,n;
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
  	C[i*(m_A-m_B+1)+j]=s;
  	}
  }
}

void full_conv(double * A, double * B,size_t m_A, size_t n_A,size_t m_B,size_t n_B, \
	double * C)
{
  size_t i,j,m,n;
  size_t l_mB,l_nB;  
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
  	C[i*(m_A+m_B-1)+j]=s;
  	}
  }
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
  	C[i*(m_A-m_B+1)+j]=s;
  	}
  }
}


// int main()
// {
// double a[]={1,2,3,4,5,6,7,8,9};
// double b[]={1,2,3,4};
// size_t ma=3,na=3;
// size_t mb=2,nb=2;
// // double c[(ma-mb+1)*(na-nb+1)];
// // valid_conv(a,b,ma,na,mb,nb,c);
// // int i;
// // for(i=0;i<(ma-mb+1)*(na-nb+1);++i)
// // 	printf("%5.2lf \n",c[i]);
// double c[(ma+mb-1)*(na+nb-1)];
// full_conv(a,b,ma,na,mb,nb,c);
// int i;
// for(i=0;i<(ma+mb-1)*(na+nb-1);++i)
// 	printf("%5.2lf \n",c[i]);
// return 0;
// }