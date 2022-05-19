#include <stdio.h>

#define PI 3.14

int main() {
	
    float radius = 10.0;
    float area;

    if(radius <= 10.0) {
        area = PI * radius * radius;
    }

    printf("\nArea:\t%f\n", area);

    return(0);

}

