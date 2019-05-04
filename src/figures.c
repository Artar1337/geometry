#include <math.h>
#include <stdio.h>

extern int n;

const double PI = 3.14159265359;

float circleP(float r)
{
    return (2 * PI * r);
}

float circleS(float r)
{
    return (PI * r * r);
}

float triangleP(float x1, float y1, float x2, float y2, float x3, float y3)
{
    float a, b, c;
    a = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    b = sqrt((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2));
    c = sqrt((x1 - x3) * (x1 - x3) + (y1 - y3) * (y1 - y3));
    return (a + b + c);
}

float triangleS(float x1, float y1, float x2, float y2, float x3, float y3)
{
    float a, b, c, p, s;
    a = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    b = sqrt((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2));
    c = sqrt((x1 - x3) * (x1 - x3) + (y1 - y3) * (y1 - y3));
    p = (a + b + c) / 2;
    s = sqrt(p * (p - a) * (p - b) * (p - c));
    return s;
}

float polygoneP(
        float x1,
        float y1,
        float x2,
        float y2,
        float x3,
        float y3,
        float x4,
        float y4)
{
    float a, b, c, d;
    a = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    b = sqrt((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2));
    c = sqrt((x4 - x3) * (x4 - x3) + (y4 - y3) * (y4 - y3));
    d = sqrt((x1 - x4) * (x1 - x4) + (y1 - y4) * (y1 - y4));
    return (a + b + c + d);
}

float polygoneS(
        float x1,
        float y1,
        float x2,
        float y2,
        float x3,
        float y3,
        float x4,
        float y4)
{
    float s = 0, p, a, b, c, z;
    a = sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    b = sqrt((x3 - x2) * (x3 - x2) + (y3 - y2) * (y3 - y2));
    c = sqrt((x1 - x3) * (x1 - x3) + (y1 - y3) * (y1 - y3));
    p = (a + b + c) / 2;
    s += sqrt(p * (p - a) * (p - b) * (p - c));
    if (s < 0.000001)
        return 0;
    a = sqrt((x3 - x4) * (x3 - x4) + (y3 - y4) * (y3 - y4));
    b = sqrt((x4 - x1) * (x4 - x1) + (y4 - y1) * (y4 - y1));
    p = (a + b + c) / 2;
    z = sqrt(p * (p - a) * (p - b) * (p - c));
    if (z < 0.000001)
        return 0;
    s += z;
    return s;
}

void circle(float x, float y, float r)
{
    n++;
    printf("%d. Circle(%6.2f,%6.2f,%6.2f)\nPerimetr = %f\nArea = %f\n",
           n,
           x,
           y,
           r,
           circleP(r),
           circleS(r));
}

int triangle(float x1, float y1, float x2, float y2, float x3, float y3)
{
    float s;
    s = triangleS(x1, y1, x2, y2, x3, y3);
    if (s > 0.00001) {
        n++;
        printf("%d. "
               "Triangle(%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f)"
               "\nPerimetr = "
               "%f\nArea = %f\n",
               n,
               x1,
               y1,
               x2,
               y2,
               x3,
               y3,
               x1,
               y1,
               triangleP(x1, y1, x2, y2, x3, y3),
               s);
    } else {
        printf("This triangle does not exists! Try again.\n");
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
    float s;
    s = polygoneS(x1, y1, x2, y2, x3, y3, x4, y4);
    if (s > 0.00001) {
        n++;
        printf("%d. "
               "Polygone(%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,"
               "%6.2f)"
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
               x1,
               y1,
               polygoneP(x1, y1, x2, y2, x3, y3, x4, y4),
               s);
        return 1;
    } else {
        printf("This polygone does not exists! Try again.\n");
        return 0;
    }
}

