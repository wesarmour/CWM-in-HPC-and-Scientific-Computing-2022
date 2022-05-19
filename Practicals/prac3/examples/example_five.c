#include <stdio.h>

#define PI 3.14

float area_of_circle(float radius); 

int main() {
	
    float radius[3] = {5.0, 10.0, 15.0};
    float area[3];
    float total_area;

    area[0] = area_of_circle(radius[0]);
    area[1] = area_of_circle(radius[1]);
    area[2] = area_of_circle(radius[2]);

    total_area = area[0] + area[1] + area[2];

    printf("\nTotal area:\t%f\n", total_area);
	
    return(0);

}

float area_of_circle(float radius) {

    float area = PI * radius * radius;

    return area;
}

