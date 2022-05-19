#include <stdio.h>

#define PI 3.14

int main() {
	
    float radius = 11.0;
    float area;
    float circumference;

    if(radius <= 10.0) {
        area = PI * radius * radius;
	printf("\nArea:\t%f\n", area);
    } else {
        circumference = 2.0 * PI * radius;
	printf("\nCircumference:\t%f\n", circumference);
    }
	
    return(0);
}

