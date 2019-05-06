#include <ctest.h>
#include <figures.h>
#include <math.h>
const double PI = 3.14159265;

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

CTEST(perimeter, circle)
{
    float r = 1;
    float result = circleP(r);
    float expected = 6.283185;
    ASSERT_DBL_NEAR(expected, result);
    r = 0.345;
    result = circleP(r);
    expected = 2.167698;
    ASSERT_DBL_NEAR(expected, result);
    r = 0;
    result = circleP(r);
    expected = 0;
    ASSERT_DBL_NEAR(expected, result);
    r = 415;
    result = circleP(r);
    expected = 2607.521899;
    ASSERT_DBL_NEAR(expected, result);
    r = 228.34534;
    result = circleP(r);
    expected = 1434.736083;
    ASSERT_DBL_NEAR(expected, result);
}

CTEST(perimeter, triangle)
{
    float x1 = 1, y1 = 1, x2 = 2, y2 = 2, x3 = 6, y3 = 3;
    float result = triangleP(x1, y1, x2, y2, x3, y3);
    float expected = 10.92;
    ASSERT_DBL_NEAR_TOL(expected, result, 1e-2);
    x1 = 1, y1 = 1, x2 = 1, y2 = 1, x3 = 2, y3 = 2;
    result = triangleP(x1, y1, x2, y2, x3, y3);
    expected = 2.83;
    ASSERT_DBL_NEAR_TOL(expected, result, 1e-2);
    x1 = 0, y1 = 0, x2 = 1, y2 = 0, x3 = 0, y3 = 1;
    result = triangleP(x1, y1, x2, y2, x3, y3);
    expected = 3.41;
    ASSERT_DBL_NEAR_TOL(expected, result, 1e-2);
    x1 = 1, y1 = 1, x2 = 2, y2 = 2, x3 = 3, y3 = 3;
    result = triangleP(x1, y1, x2, y2, x3, y3);
    expected = 5.65;
    ASSERT_DBL_NEAR_TOL(expected, result, 1e-2);
    x1 = 1.3, y1 = 1.7, x2 = 23.6, y2 = 34.23, x3 = 66.3, y3 = 0.04;
    result = triangleP(x1, y1, x2, y2, x3, y3);
    expected = 159.16;
    ASSERT_DBL_NEAR_TOL(expected, result, 1e-2);
}

CTEST(perimeter, polygone)
{
    float x1 = 0, y1 = 0, x2 = 1, y2 = 1, x3 = 2, y3 = 2,x4=1,y4=3;
    float result = polygoneP(x1, y1, x2, y2, x3, y3,x4,y4);
    float expected = 7.40491834;
    ASSERT_DBL_NEAR(expected, result);
    x1 = 1, y1 = 1, x2 = 2, y2 = 1, x3 = 2, y3 = 2,x4=1,y4=2;
    result = polygoneP(x1, y1, x2, y2, x3, y3,x4,y4);
    expected = 4;
    ASSERT_DBL_NEAR(expected, result);
    x1 = 2, y1 = 10.3, x2 = 2.66, y2 = 20, x3 = 5.5, y3 = 15.6,x4=4,y4=10.3;
    result = polygoneP(x1, y1, x2, y2, x3, y3,x4,y4);
    expected = 22.46754;
    ASSERT_DBL_NEAR(expected, result);
    x1 = 0, y1 = 0, x2 = 0, y2 = 2, x3 = 2, y3 = 1,x4=1,y4=1;
    result = polygoneP(x1, y1, x2, y2, x3, y3,x4,y4);
    expected = 6.65028153;
    ASSERT_DBL_NEAR(expected, result);
    x1 = 1, y1 = 1, x2 = 1, y2 = 1, x3 = 1, y3 = 1,x4=1,y4=1;
    result = polygoneP(x1, y1, x2, y2, x3, y3,x4,y4);
    expected = 0;
    ASSERT_DBL_NEAR(expected, result);
}

CTEST(square, circle)
{
    float r = 1;
    float result = circleS(r);
    float expected = 3.14159265;
    ASSERT_DBL_NEAR(expected, result);
    r = 0.345;
    result = circleS(r);
    expected = 0.373928065;
    ASSERT_DBL_NEAR(expected, result);
    r = 0;
    result = circleS(r);
    expected = 0;
    ASSERT_DBL_NEAR(expected, result);
    r = 415;
    result = circleS(r);
    expected = 541060.79414625;
    ASSERT_DBL_NEAR(expected, result);
    r = 228.34;
    result = circleS(r);
    expected = 163799.98801016;
    ASSERT_DBL_NEAR(expected, result);
}

CTEST(square, triangle)
{
    float x1 = 0, y1 = 0, x2 = 1, y2 = 3, x3 = 2, y3 = 1;
    float result = triangleS(x1, y1, x2, y2, x3, y3);
    float expected = 2.5;
    ASSERT_DBL_NEAR(expected, result);
    x1 = 0, y1 = 0, x2 = -2, y2 = 0, x3 = 0, y3 = -2;
    result = triangleS(x1, y1, x2, y2, x3, y3);
    expected = 2;
    ASSERT_DBL_NEAR(expected, result);
    x1 = 1, y1 = 1, x2 = 2, y2 = 2, x3 = 3, y3 = 3;
    result = triangleS(x1, y1, x2, y2, x3, y3);
    expected = 0;
    ASSERT_DBL_NEAR(expected, result);
    x1 = 7.4, y1 = 3.41, x2 = 7.6, y2 = 3.5, x3 = 7.5, y3 = 3.48;
    result = triangleS(x1, y1, x2, y2, x3, y3);
    expected = 0.0025;
    ASSERT_DBL_NEAR(expected, result);
    x1 = 10, y1 = 1, x2 = 100, y2 = 5, x3 = 1, y3 = 3.48;
    ;
    result = triangleS(x1, y1, x2, y2, x3, y3);
    expected = 129.6;
    ASSERT_DBL_NEAR_TOL(expected, result, 1e-3);
}

CTEST(square, polygone)
{
    float x1 = 0, y1 = 0, x2 = 0, y2 = 3, x3 = 0, y3 = 1,x4=0,y4=0;
    float result = polygoneS(x1, y1, x2, y2, x3, y3,x4,y4);
    float expected = 0;
    ASSERT_DBL_NEAR(expected, result);
    x1 = 1, y1 = 1, x2 = 2, y2 = 2, x3 = 3, y3 = 3,x4=6,y4=0;
    result = polygoneS(x1, y1, x2, y2, x3, y3,x4,y4);
    expected = 0;
    ASSERT_DBL_NEAR(expected, result);
    x1 = -2, y1 = -4, x2 = 0, y2 = -2, x3 = 1, y3 = -4,x4=1,y4=-5;
    result = polygoneS(x1, y1, x2, y2, x3, y3,x4,y4);
    expected = 4.5;
    ASSERT_DBL_NEAR(expected, result);
    x1 = -6.3, y1 = -0.34, x2 = 1, y2 = 4, x3 = 3.3, y3 = 4,x4=11.6,y4=-1;
    result = polygoneS(x1, y1, x2, y2, x3, y3,x4,y4);
    expected = 47.002;
    ASSERT_DBL_NEAR(expected, result);
    x1 = 1, y1 = 1, x2 = 2, y2 = 2, x3 = 3, y3 = 4,x4=0,y4=0;
    result = polygoneS(x1, y1, x2, y2, x3, y3,x4,y4);
    expected = 1 ;
    ASSERT_DBL_NEAR(expected, result);
}

