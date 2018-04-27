//
//  main.c
//  lab2
//
//

#include <stdio.h>
#include <stdbool.h>
#include "omp.h"
#include <time.h>
#include <stdlib.h>



double estimatePi(int long numTosses);
double insideCircle(long int numTosses);

int main(int argc, const char * argv[]) {
    
    long int estimation;
    printf("Enter your toss value:");
    scanf("%d", &estimation);
    
    double pi_estimate = insideCircle(estimation);
    
    printf("%f\n",pi_estimate);
    
    
    return 0;
}


double insideCircle(int long numTosses)
{
    srand (time( NULL));
    
    double number_in_circle = 0.0;
    double x =0.0;
    double y= 0.0;
    double distance_squared = 0.0;
    #pragma omp parallel for shared(numTosses) reduction (+:number_in_circle)
    for(long int i = 0; i < numTosses; i++)
    {
        x =(double)rand()/RAND_MAX*2.0-1.0;
        y =(double)rand()/RAND_MAX*2.0-1.0;
        
        distance_squared = x*x + y*y;
        if(distance_squared <=1)
            number_in_circle++;
    }
    
    return (double)(4.0* number_in_circle / (double)numTosses);
   
}


double estimatePi(int long numTosses)
{
    long int number_of_tosses =numTosses;
    int blocks =8;
    long int block = number_of_tosses/blocks;
    
    int count =0;
    #pragma omp parallel for shared(blocks, block) reduction (+:count)
    for(int c=0; c < blocks; c++)
    {
        count += insideCircle(block);
    }
    
    double pi_estimate = 4.0* count / number_of_tosses;
    return pi_estimate;
}

