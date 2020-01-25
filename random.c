#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>

#define MAX_PRECISION 1000000000000

bool Bernoulli(double p, unsigned long int precision){
	if(precision > MAX_PRECISION){
              fprintf(stderr, "The degree of precision, %ld in bernouli experiment is bigger then the allowed degree of precision",precision);	
	}
	double random_sample = fmod(rand(),precision)/precision;
	return (random_sample<=p);



}
// A utility function to swap to integers
static void swap (int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}


// A function to generate a random permutation of arr[]
void shuffle ( int arr[], int n )
{
    // Use a different seed value so that we don't get same
    // result each time we run this program
  
    // Start from the last element and swap one by one. We don't
    // need to run for the first element that's why i > 0
    for (int i = n-1; i > 0; i--)
    {
        // Pick a random index from 0 to i
        int j = rand() % (i+1);

        // Swap arr[i] with the element at random index
        swap(&arr[i], &arr[j]);
    }
}



