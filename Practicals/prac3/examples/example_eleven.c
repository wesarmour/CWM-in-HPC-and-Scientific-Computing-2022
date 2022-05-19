#include <stdio.h>
#define PI 3.14

float area_of_circle(float radius); 

int main() {
    int i=0;
    float radius[3];
    float area[3];
    float total_area;

    printf("\nEnter three radii:\t");
    scanf("%f %f %f", &radius[0], &radius[1], &radius[2]);

    while(i<3) {
        area[i] = area_of_circle(radius[i]);
        i++;
    }

    total_area = 0.0;
    for(i=0; i<3; i++) {
        total_area += area[i];
    }
    printf("\nTotal area is:\t%f\n", total_area);
    return(0);
}

float area_of_circle(float radius) {
    float area = PI * radius * radius;
    return area;
}

