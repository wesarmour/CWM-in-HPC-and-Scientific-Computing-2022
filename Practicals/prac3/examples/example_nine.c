#include <stdio.h>

#define PI 3.14

float area_of_circle(float radius); 

int main() {
	
    int i;
    float radius[3] = {5.0, 10.0, 15.0};
    float area[3];
    float total_area;

    i=0;
    while(i<3) {
        area[i] = area_of_circle(radius[i]);
        i++;
    }

    total_area = 0.0;
    for(i=0; i<3; i++) {
        total_area += area[i];
    }

    printf("\nTotal area:\t%f\n", total_area);
	
    return(0);
}

float area_of_circle(float radius) {
    float area = PI * radius * radius;
    return area;
}

