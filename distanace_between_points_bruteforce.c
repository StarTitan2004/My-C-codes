//Next Lab exercise: Given a set of points p1....pn, write a program to find the pair of points having minimum distance. 
//Distance is calculated using Euclidean formula. Assume no two points have same co-ordinates.
//First do it using Brute force method and then you try using Divide and Conquer.

#include <stdio.h>
#include <math.h>

float euclidean_distance(float x1, float y1, float x2, float y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void min_distance(float points[][2], int n) {
    float min = 10000;
    int closest_pair[2] = {-1, -1};
	int i,j;
    for(i = 0; i < n; i++){
        for(j = i + 1; j < n; j++) {
            float dist = euclidean_distance(points[i][0], points[i][1], points[j][0], points[j][1]);
            if (dist < min) {
                min = dist;
                closest_pair[0] = i;
                closest_pair[1] = j;
            }
        }
    }

    printf("Closest pair: (%.2f, %.2f) and (%.2f, %.2f)\n", points[closest_pair[0]][0], points[closest_pair[0]][1], points[closest_pair[1]][0], points[closest_pair[1]][1]);
    printf("Minimum distance is : %.2f\n", min);
}

int main() {
    float points[][2] = {{1, 2}, {4, 6}, {7, 9}, {3, 1}, {8, 5}};
    int n = sizeof(points) / sizeof(points[0]);

    min_distance(points, n);

    return 0;
}
