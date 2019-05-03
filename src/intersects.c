#include "intersects.h"
#include <math.h>
#include <stdio.h>

int IntersectCC(float rad[], float xc[], float yc[], int count[]) // RABOTAET
{
    int flag = 0, z = count[0] - 2;
    float c;
    while (z >= 0) {
        c = sqrt(
                ((xc[z] - xc[count[0] - 1]) * (xc[z] - xc[count[0] - 1]))
                + ((yc[z] - yc[count[0] - 1]) * (yc[z] - yc[count[0] - 1])));
        if (c < fabs(rad[count[0] - 1] - rad[z])) {
            z--;
            continue;
        }
        if (c <= rad[count[0] - 1] || c <= rad[z]) {
            flag = 1;
            printf("%d. Circle(%6.2f,%6.2f,%6.2f)\n",
                   z + 1,
                   xc[z],
                   yc[z],
                   rad[z]);
        }
        z--;
    }
    if (flag)
        return 1;
    else
        return 0;
}

int IntersectCT(
        float rad[],
        float xc[],
        float yc[],
        float xt[],
        float yt[],
        int count[]) // RABOTAET
{
    int z = count[0] - 1, i, j, flag = 0, flg = 0, f = 1;
    float A, b, B, C, y1, y2, x1, x2, D, k, ymax, ymin, xmax, xmin;
    A = -2 * xc[z];
    B = -2 * yc[z];
    C = xc[z] * xc[z] + yc[z] * yc[z] - rad[z] * rad[z];

    for (i = 1; i <= count[1]; i++) // vibor treygolnika
    {
        for (j = i * 3 - 3; j <= i * 3 - 1; j++) // vibor otrezka
        {
            if (j == i * 3 - 1) {
                y1 = yt[j - 2];
                y2 = yt[j];
                x1 = xt[j - 2];
                x2 = xt[j];
            } else {
                y1 = yt[j];
                y2 = yt[j + 1];
                x1 = xt[j];
                x2 = xt[j + 1];
            }
            if (y1 > y2) {
                ymax = y1 + 0.01;
                ymin = y2 - 0.01;
            } else {
                ymax = y2 + 0.01;
                ymin = y1 - 0.01;
            }
            if (x1 > x2) {
                xmax = x1 + 0.01;
                xmin = x2 - 0.01;
            } else {
                xmax = x2 + 0.01;
                xmin = x1 - 0.01;
            }
            if (y1 - y2 < 0.0001) {
                k = 0;
                b = y1;
            } else if (x1 - x2 > 0.0001) {
                k = (y1 - y2) / (x1 - x2);
                b = y1 - k * x1;
                f = 1;
            } else {
                b = x1;
                f = 0;
            }
            if (f)
                D = ((2 * b * k + A + B * k) * (2 * b * k + A + B * k))
                        - (4 * (1 + k * k) * (b * b + B * b + C));
            else
                D = (B * B) - 4 * (b * b + A * b + C);
            if (D > 0.00001) {
                if (f) {
                    x1 = (-2 * B * k - A - B * k + sqrt(D)) / (2 * (1 + k * k));
                    x2 = (-2 * B * k - A - B * k - sqrt(D)) / (2 * (1 + k * k));
                    y1 = k * x1 + b;
                    y2 = k * x2 + b;
                } else {
                    y1 = (-B * B + sqrt(D)) / 2;
                    y2 = (-B * B - sqrt(D)) / 2;
                }
                // printf("D=%6.2f,k=%6.2f,b=%6.2f,x1=%6.2f,x2=%6.2f,y1=%6.2f,y2=%6.2f",D,k,b,x1,x2,y1,y2);
                if (x1 >= xmin && x1 <= xmax && y1 <= ymax && y1 >= ymin) {
                    flag = 1;
                    break;
                } else if (
                        x2 >= xmin && x2 <= xmax && y2 <= ymax && y2 >= ymin) {
                    flag = 1;
                    break;
                }
            } else if (D < 0.00001 && D > -0.000001) {
                if (f) {
                    x1 = (-2 * B * k - A - B * k + sqrt(D)) / (2 * (1 + k * k));
                    y1 = k * x1 + b;
                } else
                    y1 = (-B * B + sqrt(D)) / 2;
                if (x1 >= xmin && x1 <= xmax && y1 <= ymax && y1 >= ymin) {
                    flag = 1;
                    break;
                }
            }
            if (D < 0.001)
                continue;
        }
        if (flag) {
            printf("%d. "
                   "Triangle(%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f)"
                   "\n",
                   i,
                   xt[i * 3 - 3],
                   yt[i * 3 - 3],
                   xt[i * 3 - 2],
                   yt[i * 3 - 2],
                   xt[i * 3 - 1],
                   yt[i * 3 - 1],
                   xt[i * 3 - 3],
                   yt[i * 3 - 3]);
            flg = 1;
            flag = 0;
        }
    }

    if (flg)
        return 1;
    else
        return 0;
}

int IntersectCP(
        float rad[],
        float xc[],
        float yc[],
        float xp[],
        float yp[],
        int count[]) // RABOTAET
{
    int z = count[0] - 1, i, j, flag = 0, flg = 0, f = 1;
    float A, b, B, C, y1, y2, x1, x2, D, k, ymax, ymin, xmax, xmin;
    A = -2 * xc[z];
    B = -2 * yc[z];
    C = xc[z] * xc[z] + yc[z] * yc[z] - rad[z] * rad[z];

    for (i = 1; i <= count[2]; i++) // vibor polygona
    {
        for (j = i * 4 - 4; j <= i * 4 - 1; j++) // vibor otrezka
        {
            if (j == i * 4 - 1) {
                y1 = yp[j - 3];
                y2 = yp[j];
                x1 = xp[j - 3];
                x2 = xp[j];
            } else {
                y1 = yp[j];
                y2 = yp[j + 1];
                x1 = xp[j];
                x2 = xp[j + 1];
            }
            if (y1 > y2) {
                ymax = y1 + 0.01;
                ymin = y2 - 0.01;
            } else {
                ymax = y2 + 0.01;
                ymin = y1 - 0.01;
            }
            if (x1 > x2) {
                xmax = x1 + 0.01;
                xmin = x2 - 0.01;
            } else {
                xmax = x2 + 0.01;
                xmin = x1 - 0.01;
            }
            if (y1 - y2 < 0.0001) {
                k = 0;
                b = y1;
            } else if (fabs(x1 - x2) > 0.0001) {
                k = (y1 - y2) / (x1 - x2);
                b = y1 - k * x1;
                f = 1;
            } else {
                b = x1;
                f = 0;
            }
            if (f)
                D = ((2 * b * k + A + B * k) * (2 * b * k + A + B * k))
                        - (4 * (1 + k * k) * (b * b + B * b + C));
            else
                D = (B * B) - 4 * (b * b + A * b + C);
            if (D > 0.00001) {
                if (f) {
                    x1 = (-2 * B * k - A - B * k + sqrt(D)) / (2 * (1 + k * k));
                    x2 = (-2 * B * k - A - B * k - sqrt(D)) / (2 * (1 + k * k));
                    y1 = k * x1 + b;
                    y2 = k * x2 + b;
                } else {
                    y1 = (-B * B + sqrt(D)) / 2;
                    y2 = (-B * B - sqrt(D)) / 2;
                }
                if (x1 >= xmin && x1 <= xmax && y1 <= ymax && y1 >= ymin) {
                    flag = 1;
                    break;
                } else if (
                        x2 >= xmin && x2 <= xmax && y2 <= ymax && y2 >= ymin) {
                    flag = 1;
                    break;
                }
            } else if (D < 0.00001 && D > -0.000001) {
                if (f) {
                    x1 = (-2 * B * k - A - B * k + sqrt(D)) / (2 * (1 + k * k));
                    y1 = k * x1 + b;
                } else
                    y1 = (-B * B + sqrt(D)) / 2;
                if (x1 >= xmin && x1 <= xmax && y1 <= ymax && y1 >= ymin) {
                    flag = 1;
                    break;
                }
            }
            if (D < 0.001)
                continue;
        }
        if (flag) {
            printf("%d. "
                   "Polygone(%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%"
                   "6.2f,%6.2f)\n",
                   i,
                   xp[i * 4 - 4],
                   yp[i * 4 - 4],
                   xp[i * 4 - 3],
                   yp[i * 4 - 3],
                   xp[i * 4 - 2],
                   yp[i * 4 - 2],
                   xp[i * 4 - 1],
                   yp[i * 4 - 1],
                   xp[i * 4 - 4],
                   yp[i * 4 - 4]);
            flg = 1;
            flag = 0;
        }
    }

    if (flg)
        return 1;
    else
        return 0;
}

int IntersectTC()
{
    int flag = 0;
    if (flag)
        return 1;
    else
        return 0;
}

int IntersectTT()
{
    int flag = 0;
    if (flag)
        return 1;
    else
        return 0;
}

int IntersectTP()
{
    int flag = 0;
    if (flag)
        return 1;
    else
        return 0;
}

int IntersectPC()
{
    int flag = 0;
    if (flag)
        return 1;
    else
        return 0;
}

int IntersectPT()
{
    int flag = 0;
    if (flag)
        return 1;
    else
        return 0;
}

int IntersectPP()
{
    int flag = 0;
    if (flag)
        return 1;
    else
        return 0;
}

int Intersects(
        int type,
        float rad[],
        float xc[],
        float yc[],
        float xt[],
        float yt[],
        float xp[],
        float yp[],
        int count[])
{
    int flag = 0;
    printf("\nIntersects:\n");
    if (type == 1) // circle
    {
        if (count[0] - 1 > 0) {
            if (IntersectCC(rad, xc, yc, count))
                flag = 1;
        }
        if (count[1]) {
            if (IntersectCT(rad, xc, yc, xt, yt, count))
                flag = 1;
        }
        if (count[2]) {
            if (IntersectCP(rad, xc, yc, xp, yp, count))
                flag = 1;
        }
    } else if (type == 2) // triangle
    {
        if (count[0]) {
            if (IntersectTC(rad, xc, yc, count))
                flag = 1;
        }
        if (count[1] - 1 > 0) {
            if (IntersectTT(rad, xc, yc, xt, yt, count))
                flag = 1;
        }
        if (count[2]) {
            if (IntersectTP(rad, xc, yc, xp, yp, count))
                flag = 1;
        }
    } else if (type == 3) // polygone
    {
        if (count[0]) {
            if (IntersectPC(rad, xc, yc, count))
                flag = 1;
        }
        if (count[1]) {
            if (IntersectPT(rad, xc, yc, xt, yt, count))
                flag = 1;
        }
        if (count[2] - 1 > 0) {
            if (IntersectPP(rad, xc, yc, xp, yp, count))
                flag = 1;
        }
    }
    if (flag) {
        return 1;
    } else {
        printf("none\n");
        return 0;
    }
}

