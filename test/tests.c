#include <ctest.h>
#include <figures.h>

const double PI = 3.14159265;

float circleP(float r)
{
    return (2 * PI * r);
}

CTEST(arithmetic_suite, circle_perimeter)
{
    const float r = 1;
    const float result = circleP(r);
    const float expected = 6.283185;
    ASSERT_DBL_NEAR(expected, result);
}
