#include <stdio.h>

#define PI 3.14

int main() {
	
    float radius_one   = 5.0;
    float radius_two   = 10.0;
    float radius_three = 15.0;
    float area_one, area_two, area_three;
    float total_area;

    area_one = PI * radius_one * radius_one;
    area_two = PI * radius_two * radius_two;
    area_three = PI * radius_three * radius_three;

    total_area = area_one + area_two + area_three;

    printf("\nTotal area:\t%f\n", total_area);
	
    return(0);

}

