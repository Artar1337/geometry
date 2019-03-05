#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int circle_n = 0;
const double PI = 3.14159265;

int circle(int x, int y, float r)
{
    circle_n++;
    printf("%d. Circle(%d,%d,%6.2f)\nPerimetr = %f\nArea = %f\n",
           circle_n,
           x,
           y,
           r,
           2 * PI * r,
           PI * r * r);
    return 0;
}

int main()
{
    int i = 7, p = 0, k = 7, x[2];
    double r;
    char A[] = "circle(", s[80], s1[80] = {0}, emp[] = "\0", exit[] = "exit";

    while (1) {
        printf("Input data in type 'circle(x,y,r)'.To exit input 'exit': ");
        gets(s);
        if (strncmp(A, s, 7) == 0) {
            while (p < 2) {
                if (s[i] == ',') {
                    x[p] = atoi(s1);
                    strcpy(s1, emp);
                    p++;
                    k++;
                } else {
                    strncat(s1, s + k, 1);
                    k++;
                }
                i++;
            }
            while (p != 0) {
                if (s[i] == ')') {
                    r = atof(s1);
                    strcpy(s1, emp);
                    k = 7;
                    p = 0;
                    i = 6;
                } else {
                    strncat(s1, s + k, 1);
                    k++;
                }
                i++;
            }
            circle(x[0], x[1], r);
        } else if (strcmp(s, exit) == 0) {
            printf("Executing stopped!\n");
            return 0;
        } else {
            printf("Wrong data type! Try again.\n");
        }
    }
}
