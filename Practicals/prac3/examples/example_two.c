/* This is a C program that    
   calculates the area of a circle.
   Written by Wes  
   wes.armour@eng.ox.ac.uk
   06/05/18
*/

//Include standard IO library
#include <stdio.h>

// Define a symbolic constant, pi.
#define PI 3.14

// The main body of the program
int main() {

    // Define variables
    float radius = 10.0;
    float area;

    // Calculate the area
    area = PI * radius * radius;

    // Print out the result
    printf("\nThe area is:\t%f\n", area);
	
    return(0);
}

