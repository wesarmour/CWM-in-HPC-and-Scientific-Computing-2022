#include <stdio.h>
#include <stdlib.h>

#define NUM_ELS 100000

int main() {
	
    float random_array[NUM_ELS];
    float sum=0;

    for(int i=0; i<NUM_ELS; i++) {
        float x = ((float)rand())/((float)RAND_MAX);
        random_array[i] = x;
    }

    for(int i=0; i<NUM_ELS; i++) {
        sum+=random_array[i];
    }

    printf("\nAverage:\t%f\n", sum/(float)NUM_ELS);

    return(0);
}
