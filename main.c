//
//  main.c
//  lab2
//
//

#include <stdio.h>
#include <stdbool.h>
#include "omp.h"


double estimatePi(int long numTosses);

int main(int argc, const char * argv[]) {

    long int estimation;
    printf("Enter your toss value:");
    scanf("%d", &estimation);
    
    double pi_estimate = estimatePi(estimation);
    
    printf("%f\n",pi_estimate);
    
    
    return 0;
}


int insideCircle(long int block)
{
    srand (time( NULL));
    
    int number_in_circle = 0;
    for(int i = 0; i < block; i++)
    {
        double x =(double)rand()/RAND_MAX*2.0-1.0;
        double y =(double)rand()/RAND_MAX*2.0-1.0;
        
        double distance_squared = x*x + y*y;
        if(distance_squared <=1)
            number_in_circle++;
    }
    
    return number_in_circle;
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

