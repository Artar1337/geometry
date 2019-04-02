#include <math.h>
#include <stdio.h>

extern int n;

const double PI = 3.14159265359;

int circle(float x, float y, float r)
{
    n++;
    printf("%d. Circle(%6.2f,%6.2f,%6.2f)\nPerimetr = %f\nArea = %f\n",
           n,
           x,
           y,
           r,
           2 * PI * r,
           PI * r * r);
    return 1;
}

int triangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
    float s, p, a, b, c;
    n++;
    a = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    b = sqrt((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2));
    c = sqrt((x1 - x3) * (x1 - x3) + (y1 - y3) * (y1 - y3));
    p = (a + b + c) / 2;
    s = sqrt(p * (p - a) * (p - b) * (p - c));
    if (s > 0.00001)
        printf("%d. Triangle(%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f)\nPerimetr = "
               "%f\nArea = %f\n",
               n,
               x1,
               y1,
               x2,
               y2,
               x3,
               y3,
               p * 2,
               s);
    else {
        printf("This triangle does not exists! Try again.\n");
        n--;
        return 0;
    }
    return 1;
}

int polygone(
        float x1,
        float y1,
        float x2,
        float y2,
        float x3,
        float y3,
        float x4,
        float y4)
{
    float s = 0, per = 0, p, a, b, c, z;
    n++;
    a = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    per += a;
    b = sqrt((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2));
    per += b;
    c = sqrt((x1 - x3) * (x1 - x3) + (y1 - y3) * (y1 - y3));
    p = (a + b + c) / 2;
    s += sqrt(p * (p - a) * (p - b) * (p - c));
    if (s < 0.000001) {
        printf("This polygone does not exists! Try again.\n");
        n--;
        return 0;
    }
    a = sqrt((x3 - x4) * (x3 - x4) + (y3 - y4) * (y3 - y4));
    per += a;
    b = sqrt((x4 - x1) * (x4 - x1) + (y4 - y1) * (y4 - y1));
    per += b;
    p = (a + b + c) / 2;
    z = sqrt(p * (p - a) * (p - b) * (p - c));
    if (z < 0.000001) {
        printf("This polygone does not exists! Try again.\n");
        n--;
        return 0;
    }
    s += z;
    printf("%d. "
           "Polygone(%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f)"
           "\nPerimetr = %f\nArea = %f\n",
           n,
           x1,
           y1,
           x2,
           y2,
           x3,
           y3,
           x4,
           y4,
           per,
           s);
    return 1;
}

