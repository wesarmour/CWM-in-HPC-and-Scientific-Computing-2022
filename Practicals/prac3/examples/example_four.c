#include <stdio.h>

#define PI 3.14

float area_of_circle(float radius); 

int main() {
	
    float radius_one   = 5.0;
    float radius_two   = 10.0;
    float radius_three = 15.0;
    float area_one, area_two, area_three;
    float total_area;

    area_one = area_of_circle(radius_one);
    area_two = area_of_circle(radius_two);
    area_three = area_of_circle(radius_three);

    total_area = area_one + area_two + area_three;

    printf("\nTotal area:\t%f\n", total_area);
	
    return(0);

}

float area_of_circle(float radius) {

    float area = PI * radius * radius;

    return area;
}

