//multiple layers perceptron
#include <stdio.h>
#include <cblas.h>
#include <stdlib.h>
#include <math.h>

double active_func(double x)
{
    return 1 / (1 + exp(-1 * x));
}

int main(int argc, char *argv[])
{
    int deapth = 2;
    int nodes[deapth];
    int n, p;
    double *x;
    double *y;
    double *coef;
    double *residual;
    double *output;
    double *input;
    int i, j;
    int sum_nodes = 0;
    for (i = 0; i < deapth; ++i) 
        sum_nodes += nodes[i];     
    //initialize the parameters
     
    //residual 
    for (i = 0; i < n; i++) 
    {
        residual[sum_nodes] = y[i] - output[sum_nodes]; 
        for (j = deapth; j >= 0; j--)
        {
            
        }
    }
    return 0;
}
