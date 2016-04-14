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
	{
		*avg_value+=A[i];
		*avg_value=*avg_value/len;
	}
}


void down_sample(double * A, double * B, int m_A, int n_A, int nr, int nc,\
 int mode)
{
   int i,j,m,n;
   	for(i=0;i<m_A;i+=nr)
   	{
   		for (j = 0; j<n_A;j+=nc)
   		{
   			
   		}
   	}
}


