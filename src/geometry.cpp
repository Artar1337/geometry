#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int circle_n = 0;
const double PI = 3.14159265;
const int N = 50;
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
    int i = 7, p = 0, k = 7, ix[2], x[N], y[N], j = 0, z, flag = 1;
    double r, c, rad[N];
    char A[] = "circle(", s[80], s1[80] = {0}, emp[] = "\0", exit[] = "exit";

    while (1) {
        printf("Input data in type 'circle(x,y,r)'.To exit input 'exit': ");
        scanf("%s", s);
        if (strncmp(A, s, 7) == 0) {
            while (p < 2) {
                if (s[i] == ',') {
                    ix[p] = atoi(s1);
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
            x[j] = ix[0];
            y[j] = ix[1];
            rad[j] = r;
            circle(ix[0], ix[1], r);
            printf("Intersects:\n");
            for (z = 0; z < j; z++) {
                if (x[z] == x[j] && y[z] == y[j])
                    continue;
                c = ((x[z] - x[j]) * (x[z] - x[j]))
                        + ((y[z] - y[j]) * (y[z] - y[j]));
                sqrt(c);
                if (c < fabs(rad[j] - rad[z]))
                    continue;
                if (c <= rad[j] || c <= rad[z]) {
                    flag = 0;
                    printf("%d. Circle\n", z + 1);
                }
            }
            if (flag)
                printf("none\n");
            flag = 1;
            j++;
        } else if (strcmp(s, exit) == 0) {
            printf("Executing stopped!\n");
            return 0;
        } else {
            printf("Wrong data type! Try again.\n");
        }
    }
}
