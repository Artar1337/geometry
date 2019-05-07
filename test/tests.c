#include <ctest.h>
#include <figures.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
const double PI = 3.14159265;
int n=0;
int *ret;
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

int IntersectCC(float rad[], float xc[], float yc[], int count[], int type[])
{
    int i, j = 0, flag = 0, z = count[0] - 2, ind[n];
    float c;
    for (i = 0; i < n - 1; i++)
        if (type[i] == 1) {
            ind[j] = i;
            j++;
        }
    ind[i] = -1;
    i = 0;
    j = 0;
    while (z >= 0) {
        c = sqrt(
                ((xc[z] - xc[count[0] - 1]) * (xc[z] - xc[count[0] - 1]))
                + ((yc[z] - yc[count[0] - 1]) * (yc[z] - yc[count[0] - 1])));
        if (c < fabs(rad[count[0] - 1] - rad[z])) {
            z--;
            continue;
        }
        if (fabs(c - rad[z]) < rad[count[0] - 1]+0.01 || fabs(c-rad[count[0]-1]) < rad[z]+0.01) {
            flag = 1;
             //printf("%d. Circle(%6.2f,%6.2f,%6.2f)\n",z+1,xc[z],yc[z],rad[z]);
            ret[j] = ind[i];
            j++;
        }
        i++;
        z--;
    }
    if (flag)
        return j;
    else
        return 0;
}

int IntersectCT(
        float rad[],
        float xc[],
        float yc[],
        float xt[],
        float yt[],
        int count[],
        int type[])
{
    int z = count[0] - 1, i, j, flag = 0, flg = 0, f = 1, jn = 0, in, ind[n];
    float A, b, B, C, y1, y2, x1, x2, D, k, ymax, ymin, xmax, xmin;
    A = -2 * xc[z];
    B = -2 * yc[z];
    C = xc[z] * xc[z] + yc[z] * yc[z] - rad[z] * rad[z];
    for (in = 0; in < n; in++) {
        if (type[in] == 2) {
            ind[jn] = in;
            jn++;
        }
    }
    in = 0;
    jn = 0;
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
            if (fabs(y1 - y2) < 0.0001) {
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
                    y1 = (-B + sqrt(D)) / 2;
                    y2 = (-B - sqrt(D)) / 2;
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
                } 
                if (x1 >= xmin && x1 <= xmax && y1 <= ymax && y1 >= ymin) {
                    flag = 1;
                    break;
                }
            }
        }
        if (flag) {
            //printf("%d.Triangle(%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f)\n",i,xt[i*3-3],yt[i*3-3],xt[i*3-2],yt[i*3-2],xt[i*3-1],yt[i*3-1],xt[i*3-3],yt[i*3-3]);
            flg = 1;
            flag = 0;
            ret[jn] = ind[in];
            jn++;
        }
        in++;
    }

    if (flg)
        return jn;
    else
        return 0;
}

int IntersectCP(
        float rad[],
        float xc[],
        float yc[],
        float xp[],
        float yp[],
        int count[],
        int type[])
{
    int z = count[0] - 1, i, j, flag = 0, flg = 0, f = 1, jn = 0, in, ind[n];
    float A, b, B, C, y1, y2, x1, x2, D, k, ymax, ymin, xmax, xmin;
    A = -2 * xc[z];
    B = -2 * yc[z];
    C = xc[z] * xc[z] + yc[z] * yc[z] - rad[z] * rad[z];
    for (in = 0; in < n; in++) {
        if (type[in] == 3) {
            ind[jn] = in;
            jn++;
        }
    }
    in = 0;
    jn = 0;
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
            if (fabs(y1 - y2) < 0.0001) {
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
                    y1 = (-B + sqrt(D)) / 2;
                    y2 = (-B - sqrt(D)) / 2;
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
                } 
               if (x1 >= xmin && x1 <= xmax && y1 <= ymax && y1 >= ymin) {
                    flag = 1;
                    break;
                }
            }
        }
        if (flag) {
           // printf("%d.Polygone(%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f)\n",i,xp[i*4-4],yp[i*4-4],xp[i*4-3],yp[i*4-3],xp[i*4-2],yp[i*4-2],xp[i*4-1],yp[i*4-1],xp[i*4-4],yp[i*4-4]);
            flg = 1;
            flag = 0;
            ret[jn] = ind[in];
            jn++;
        }
        in++;
    }

    if (flg)
        return jn;
    else
        return 0;
}

int IntersectTC(
        float rad[],
        float xc[],
        float yc[],
        float xt[],
        float yt[],
        int count[],
        int type[])
{
    int z, i = count[1], j, flag = 0, flg = 0, f = 1, jn = 0, in, ind[n];
    float A, b, B, C, y1, y2, x1, x2, D, k, ymax, ymin, xmax, xmin;
    for (in = 0; in < n; in++) {
        if (type[in] == 1) {
            ind[jn] = in;
            jn++;
        }
    }
    in = 0;
    jn = 0;
    for (z = 0; z < count[0]; z++) // vibor kryga
    {
        A = -2 * xc[z];
        B = -2 * yc[z];
        C = xc[z] * xc[z] + yc[z] * yc[z] - rad[z] * rad[z];
        for (j = i * 3 - 3; j <= i * 3 - 1;
             j++) // vibor otrezka v vvedennom treyg
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
            if (fabs(y1 - y2) < 0.0001) {
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
                    y1 = (-B + sqrt(D)) / 2;
                    y2 = (-B - sqrt(D)) / 2;
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
                } 
                if (x1 >= xmin && x1 <= xmax && y1 <= ymax && y1 >= ymin) {
                    flag = 1;
                    break;
                }
            }
        }
        if (flag) {
            // printf("%d. Circle(%6.2f,%6.2f,%6.2f)\n",z+1,xc[z],yc[z],rad[z]);
            flg = 1;
            flag = 0;
            ret[jn] = ind[in];
            jn++;
        }
        in++;
    }

    if (flg)
        return jn;
    else
        return 0;
}

int IntersectTT(float xt[], float yt[], int count[], int type[])
{
    int i = count[1], p, c = 1, j, flag = 0, flg = 0, jn = 0, in, ind[n];
    float c1, z1, c2, z2, y1, y2, y3, y4, x1, x2, x3, x4, k1, k2;

    for (in = 0; in < n; in++) {
        if (type[in] == 2) {
            ind[jn] = in;
            jn++;
        }
    }
    in = 0;
    jn = 0;
    for (c = 1; c < count[1]; c++) // vibor sravnivaemogo treyga
    {
        for (j = i * 3 - 3; j <= i * 3 - 1;
             j++) // vibor otrezka v poslednem vvedennom treyge
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

            for (p = c * 3 - 3; p <= c * 3 - 1;
                 p++) // vibor otrezka v c-tom treyge
            {
                if (p == c * 3 - 1) {
                    y3 = yt[p - 2];
                    y4 = yt[p];
                    x3 = xt[p - 2];
                    x4 = xt[p];
                } else {
                    y3 = yt[p];
                    y4 = yt[p + 1];
                    x3 = xt[p];
                    x4 = xt[p + 1];
                }
                c1 = (x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3);
                z1 = (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);
                c2 = (x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3);
                z2 = (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);
                k1 = c1 / z1;
                k2 = c2 / z2;
                if (k1 > -0.0001 && k1 < 1.0001 && k2 > -0.0001
                    && k2 < 1.0001) {
                    flag = 1;
                    break;
                }
            }
            if (flag) {
                // printf("%d.
                // Triangle(%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f)\n",c,xt[c*3-3],yt[c*3-3],xt[c*3-2],yt[c*3-2],xt[c*3-1],yt[c*3-1],xt[c*3-3],yt[c*3-3]);
                flg = 1;
                flag = 0;
                ret[jn] = ind[in];
                jn++;
                break;
            }
        }
        in++;
    }
    if (flg)
        return jn;
    else
        return 0;
}

int IntersectTP(
        float xt[], float yt[], float xp[], float yp[], int count[], int type[])
{
    int i = count[1], p, c = 1, j, flag = 0, flg = 0, jn = 0, in, ind[n];
    float c1, z1, c2, z2, y1, y2, y3, y4, x1, x2, x3, x4, k1, k2;
    for (in = 0; in < n; in++) {
        if (type[in] == 3) {
            ind[jn] = in;
            jn++;
        }
    }
    in = 0;
    jn = 0;
    for (c = 1; c <= count[2]; c++) // vibor sravnivaemogo polygona
    {
        for (j = i * 3 - 3; j <= i * 3 - 1;
             j++) // vibor otrezka v poslednem vvedennom treyge
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

            for (p = c * 4 - 4; p <= c * 4 - 1;
                 p++) // vibor otrezka v c-tom polygone
            {
                if (p == c * 4 - 1) {
                    y3 = yp[p - 3];
                    y4 = yp[p];
                    x3 = xp[p - 3];
                    x4 = xp[p];
                } else {
                    y3 = yp[p];
                    y4 = yp[p + 1];
                    x3 = xp[p];
                    x4 = xp[p + 1];
                }
                c1 = (x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3);
                z1 = (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);
                c2 = (x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3);
                z2 = (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);
                k1 = c1 / z1;
                k2 = c2 / z2;
                if (k1 > -0.0001 && k1 < 1.0001 && k2 > -0.0001
                    && k2 < 1.0001) {
                    flag = 1;
                    break;
                }
            }
            if (flag) {
                // printf("%d.
                // Polygone(%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f)\n",c,xp[c*4-4],yp[c*4-4],xp[c*4-3],yp[c*4-3],xp[c*4-2],yp[c*4-2],xp[c*4-1],yp[c*4-1],xp[c*4-4],yp[c*4-4]);
                flg = 1;
                flag = 0;
                ret[jn] = ind[in];
                jn++;

                break;
            }
        }
        in++;
    }
    if (flg)
        return jn;
    else
        return 0;
}

int IntersectPC(
        float rad[],
        float xc[],
        float yc[],
        float xp[],
        float yp[],
        int count[],
        int type[])
{
    int z, i = count[2], j, flag = 0, flg = 0, f = 1, jn = 0, in, ind[n];
    float A, b, B, C, y1, y2, x1, x2, D, k, ymax, ymin, xmax, xmin;
    for (in = 0; in < n; in++) {
        if (type[in] == 1) {
            ind[jn] = in;
            jn++;
        }
    }
    in = 0;
    jn = 0;
    for (z = 0; z < count[0]; z++) // vibor kryga
    {
        A = -2 * xc[z];
        B = -2 * yc[z];
        C = xc[z] * xc[z] + yc[z] * yc[z] - rad[z] * rad[z];
        for (j = i * 4 - 4; j <= i * 4 - 1;
             j++) // vibor otrezka v vvedennom polyg
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
            if (fabs(y1 - y2) < 0.0001) {
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
                    y1 = (-B + sqrt(D)) / 2;
                    y2 = (-B - sqrt(D)) / 2;
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
                } 
                if (x1 >= xmin && x1 <= xmax && y1 <= ymax && y1 >= ymin) {
                    flag = 1;
                    break;
                }
            }
        }
        if (flag) {
          // printf("%d. Circle(%6.2f,%6.2f,%6.2f)\n",z+1,xc[z],yc[z],rad[z]);
            flg = 1;
            flag = 0;
            ret[jn] = ind[in];
            jn++;
        }
        in++;
    }

    if (flg)
        return jn;
    else
        return 0;
}

int IntersectPT(
        float xt[], float yt[], float xp[], float yp[], int count[], int type[])
{
    int i = count[2], p, c = 1, j, flag = 0, flg = 0, jn = 0, in, ind[n];
    float c1, z1, c2, z2, y1, y2, y3, y4, x1, x2, x3, x4, k1, k2;
    for (in = 0; in < n; in++) {
        if (type[in] == 2) {
            ind[jn] = in;
            jn++;
        }
    }
    in = 0;
    jn = 0;
    for (c = 1; c <= count[1]; c++) // vibor sravnivaemogo treyga
    {
        for (j = i * 4 - 4; j <= i * 4 - 1;
             j++) // vibor otrezka v poslednem vvedennom polyg
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

            for (p = c * 3 - 3; p <= c * 3 - 1;
                 p++) // vibor otrezka v c-tom treyge
            {
                if (p == c * 3 - 1) {
                    y3 = yt[p - 2];
                    y4 = yt[p];
                    x3 = xt[p - 2];
                    x4 = xt[p];
                } else {
                    y3 = yt[p];
                    y4 = yt[p + 1];
                    x3 = xt[p];
                    x4 = xt[p + 1];
                }
                c1 = (x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3);
                z1 = (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);
                c2 = (x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3);
                z2 = (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);
                k1 = c1 / z1;
                k2 = c2 / z2;
                if (k1 > -0.0001 && k1 < 1.0001 && k2 > -0.0001
                    && k2 < 1.0001) {
                    flag = 1;
                    break;
                }
            }
            if (flag) {
                // printf("%d.
                // Triangle(%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f)\n",c,xt[c*3-3],yt[c*3-3],xt[c*3-2],yt[c*3-2],xt[c*3-1],yt[c*3-1],xt[c*3-3],yt[c*3-3]);
                flg = 1;
                flag = 0;
                ret[jn] = ind[in];
                jn++;

                break;
            }
        }
        in++;
    }
    if (flg)
        return jn;
    else
        return 0;
}

int IntersectPP(float xp[], float yp[], int count[], int type[])
{
    int i = count[2], p, c = 1, j, flag = 0, flg = 0, jn = 0, in, ind[n];
    float c1, z1, c2, z2, y1, y2, y3, y4, x1, x2, x3, x4, k1, k2;
    for (in = 0; in < n; in++) {
        if (type[in] == 3) {
            ind[jn] = in;
            jn++;
        }
    }
    in = 0;
    jn = 0;
    for (c = 1; c < count[2]; c++) // vibor sravnivaemogo polygona
    {
        for (j = i * 4 - 4; j <= i * 4 - 1;
             j++) // vibor otrezka v poslednem vvedennom polyg
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

            for (p = c * 4 - 4; p <= c * 4 - 1;
                 p++) // vibor otrezka v c-tom polygone
            {
                if (p == c * 4 - 1) {
                    y3 = yp[p - 3];
                    y4 = yp[p];
                    x3 = xp[p - 3];
                    x4 = xp[p];
                } else {
                    y3 = yp[p];
                    y4 = yp[p + 1];
                    x3 = xp[p];
                    x4 = xp[p + 1];
                }
                c1 = (x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3);
                z1 = (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);
                c2 = (x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3);
                z2 = (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);
                k1 = c1 / z1;
                k2 = c2 / z2;
                if (k1 > -0.0001 && k1 < 1.0001 && k2 > -0.0001
                    && k2 < 1.0001) {
                    flag = 1;
                    break;
                }
            }
            if (flag) {
                // printf("%d.
                // Polygone(%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f)\n",c,xp[c*4-4],yp[c*4-4],xp[c*4-3],yp[c*4-3],xp[c*4-2],yp[c*4-2],xp[c*4-1],yp[c*4-1],xp[c*4-4],yp[c*4-4]);
                flg = 1;
                flag = 0;
                ret[jn] = ind[in];
                jn++;

                break;
            }
        }
        in++;
    }
    if (flg)
        return jn;
    else
        return 0;
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

CTEST(intersection, circle_with_circles)
{
    ret=(int *) malloc(sizeof(int)*10);
    n=9;
    float xc[9]={0,1.9,-3,2.1,6,4,0,-4,0},yc[9]={0,2.1,0,2,2,0,4,3,0},rad[9]={1,0.07,2,1,1.1,1,1,0.5,3};
    int count[3]={9,0,0},type[9]={1,1,1,1,1,1,1,1,1};
    int result = IntersectCC(rad, xc, yc, count, type);
    int expected = 4;
    ASSERT_EQUAL(expected, result);
 n=7;
     xc[0]=5;
xc[1]=-2;
xc[2]=2;
xc[3]=0.5;
xc[4]=-2.1;
xc[5]=5;
xc[6]=-1;
yc[0]=3;
yc[1]=2;
yc[2]=1;
yc[3]=0.5;
yc[4]=-2.2;
yc[5]=0;
yc[6]=0;
rad[0]=1;rad[1]=1;rad[2]=1.2;rad[3]=0.9;rad[4]=1.1;rad[5]=100;rad[6]=2.5;rad[7]=0;
    count[0]=7;
    result = IntersectCC(rad, xc, yc, count, type);
    expected = 3;
    ASSERT_EQUAL(expected, result);
    free(ret);
}

CTEST(intersection, circle_with_triangles)
{
    ret=(int *) malloc(sizeof(int)*10);
    n=6;
    float xc[1]={0},yc[1]={0},rad[1]={2},xt[15]={1,-2,1,2,2,6.3,-1,-0.5,-2,-2,2,0,-100,-100,200},yt[15]={2,2,3,-1,2,-1.2,1,-0.8,-2,-3,-3,-4,100,-100,-90};
    int count[3]={1,5,0},type[6]={2,2,2,2,2,1};
    int result = IntersectCT(rad, xc, yc, xt,yt,count, type);
    int expected = 3;
    ASSERT_EQUAL(expected, result);
n=4;
type[3]=1;
type[4]=0;
type[5]=0;
count[1]=3;
rad[0]=3;
xt[0]=-2;
xt[1]=2;
xt[2]=-2;
yt[0]=2.2;
yt[1]=-1.9;
yt[2]=-1.9;
xt[3]=3.01;
xt[4]=3.01;
xt[5]=4;
yt[3]=0;
yt[4]=1;
yt[5]=0.3;
xt[6]=-3.01;
xt[7]=-3.01;
xt[8]=-4;
yt[6]=0;
yt[7]=1;
yt[8]=0.2;
result = IntersectCT(rad, xc, yc, xt,yt,count, type);
   expected = 0;
ASSERT_EQUAL(expected, result);
    free(ret);
}

CTEST(intersection, circle_with_polygones)
{
    ret=(int *) malloc(sizeof(int)*10);
    n=4;
    float xc[1]={0},yc[1]={0},rad[1]={2},xp[12]={1,1,3,3,-2.02,-2.02,-4,-4,1,-1,-1,1},yp[12]={1,3,3,1,-1,1,1,-1,-2,-2,-4,-4};
    int count[3]={1,0,3},type[4]={3,3,3,1};
    int result = IntersectCP(rad, xc, yc, xp,yp,count, type);
    int expected = 2;
    ASSERT_EQUAL(expected, result);
xp[0]=-4;
xp[1]=-3;
xp[2]=-3;
xp[3]=-4;
yp[0]=3;
yp[1]=3;
yp[2]=4;
yp[3]=4;
xp[4]=-1;
xp[5]=1;
xp[6]=1;
xp[7]=-1;
yp[4]=1;
yp[5]=1;
yp[6]=-1;
yp[7]=-1;
xp[8]=2;
xp[9]=4;
xp[10]=6;
xp[11]=4;
yp[8]=0;
yp[9]=2;
yp[10]=2;
yp[11]=0;

result = IntersectCP(rad, xc, yc, xp,yp,count, type);
   expected = 1;
ASSERT_EQUAL(expected, result);
    free(ret);
}

CTEST(intersection, triangle_with_circles)
{
    ret=(int *) malloc(sizeof(int)*10);
    n=6;
    float xc[5]={0,0,0,0,-1},yc[5]={1,-2.3,0,0,1},rad[5]={1,1.1,2,5,1.1},xt[3]={1,-1,0},yt[3]={0,2,0};
    int count[3]={5,1,0},type[6]={1,1,1,1,1,2};
    int result = IntersectTC(rad, xc, yc, xt,yt,count, type);
    int expected = 3;
    ASSERT_EQUAL(expected, result);
xt[0]=0;
xt[1]=3;
xt[2]=0;
yt[0]=0;
yt[1]=0;
yt[2]=3;
    xc[0]=1;
    yc[0]=1;
xc[1]=1;
    yc[1]=2;
xc[2]=2;
    yc[2]=2;
xc[3]=-0.5;
    yc[3]=2;
xc[4]=4;
    yc[4]=0;
rad[0]=0.04;
rad[1]=1;
rad[2]=2;
rad[3]=0.48;
rad[4]=1;
result = IntersectTC(rad, xc, yc, xt,yt,count, type);
   expected = 3;
ASSERT_EQUAL(expected, result);
    free(ret);
}

CTEST(intersection, triangle_with_triangles)
{
    ret=(int *) malloc(sizeof(int)*10);
    n=5;
    float xt[15]={1,1,3,2,2,1,4,4,5,1,2,3,2,2,6},yt[15]={1,3,1,5,4,4,1,3,4,0,-1,0,-2,6,1};
    int count[3]={0,5,0},type[5]={2,2,2,2,2};
    int result = IntersectTT(xt,yt,count, type);
    int expected = 4;
    ASSERT_EQUAL(expected, result);
xt[0]=4;
xt[1]=5;
xt[2]=4.5;
yt[0]=4;
yt[1]=4;
yt[2]=6;
xt[3]=0.5;
xt[4]=0.5;
xt[5]=1;
yt[3]=1;
yt[4]=0.5;
yt[5]=0.5;
xt[6]=0;
xt[7]=0;
xt[8]=-2;
yt[6]=1;
yt[7]=3;
yt[8]=2;
xt[9]=1;
xt[10]=2;
xt[11]=3;
yt[9]=0;
yt[10]=-1;
yt[11]=0;
xt[12]=0;
xt[13]=0;
xt[14]=3;
yt[12]=0;
yt[13]=3;
yt[14]=0;
result = IntersectTT(xt,yt,count, type);
expected = 2;
ASSERT_EQUAL(expected, result);
    free(ret);
}

CTEST(intersection, triangle_with_polygones)
{
    ret=(int *) malloc(sizeof(int)*10);
    n=4;
    float xt[3]={-2,0,2},yt[3]={0,3,0},xp[12]={2,2,4,4,1,1,2,2,-2,0,-2,-3},yp[12]={0,-2,-2,0,1,4,4,1,0,3,4,2};
    int count[3]={0,1,3},type[4]={3,3,3,2};
    int result = IntersectTP(xt,yt,xp,yp,count, type);
    int expected = 3;
    ASSERT_EQUAL(expected, result);
xp[0]=-0.6;
xp[1]=-0.6;
xp[2]=0.3;
xp[3]=0.7;
yp[0]=0.5;
yp[1]=0.7;
yp[2]=1.1;
yp[3]=0.8;
xp[4]=10;
xp[5]=10;
xp[6]=11;
xp[7]=11;
yp[4]=10;
yp[5]=11;
yp[6]=11;
yp[7]=10;
xp[8]=-3.02;
xp[9]=-3.02;
xp[10]=3.02;
xp[11]=3.02;
yp[8]=-0.02;
yp[9]=3.02;
yp[10]=3.02;
yp[11]=-0.02;
result = IntersectTP(xt,yt,xp,yp,count, type);
expected = 0;
ASSERT_EQUAL(expected, result);
    free(ret);
}

CTEST(intersection, polygone_with_circles)
{
    ret=(int *) malloc(sizeof(int)*10);
    n=5;
    float xc[4]={-2,2,-1,-4},yc[4]={2,0,1,3.1},rad[4]={100,1,0.02,1},xp[4]={0,2,0,-4},yp[4]={-1,0,2,3};
    int count[3]={4,0,1},type[5]={1,1,1,1,3};
    int result = IntersectPC(rad, xc, yc, xp,yp,count, type);
    int expected = 1;
    ASSERT_EQUAL(expected, result);
xp[0]=1;
xp[1]=1;
xp[2]=2;
xp[3]=2;
yp[0]=1;
yp[1]=2;
yp[2]=2;
yp[3]=1;
    xc[0]=3;
    yc[0]=1.5;
xc[1]=1.5;
yc[1]=0;
xc[2]=1;
    yc[2]=1;
xc[3]=-6;
    yc[3]=-3;
rad[0]=0.97;
rad[1]=0.97;
rad[2]=6;
rad[3]=1;
result = IntersectTC(rad, xc, yc, xp,yp,count, type);
   expected = 1;
ASSERT_EQUAL(expected, result);
    free(ret);
}

CTEST(intersection, polygone_with_triangles)
{
    ret=(int *) malloc(sizeof(int)*10);
    n=5;
    float xt[9]={0,2,2,-1,-1,0,-1,-1,2},yt[9]={2,3,0,0,1,0,1,3,3},xp[4]={0,2,0,-1},yp[4]={0,0,2,1};
    int count[3]={0,3,1},type[5]={2,2,2,3};
    int result = IntersectPT(xt,yt,xp,yp,count, type);
    int expected = 3;
    ASSERT_EQUAL(expected, result);
xp[0]=0;
xp[1]=0;
xp[2]=1;
xp[3]=1;
yp[0]=0;
yp[1]=2;
yp[2]=2;
yp[3]=0;
xt[0]=-1;
xt[1]=0;
xt[2]=0;
yt[0]=2;
yt[1]=2;
yt[2]=3;
xt[3]=1.02;
xt[4]=1.52;
xt[5]=2;
yt[3]=1;
yt[4]=2;
yt[5]=1.3;
xt[6]=0;
xt[7]=1;
xt[8]=0.4;
yt[6]=-0.02;
yt[7]=-0.02;
yt[8]=-5;


result = IntersectPT(xt,yt,xp,yp,count, type);
expected = 1;
ASSERT_EQUAL(expected, result);
    free(ret);
}


CTEST(intersection, polygone_with_polygones)
{
    ret=(int *) malloc(sizeof(int)*10);
    n=4;
    float xp[16]={-4,-4,-2,-2,0,0,2,2,2,2,4,4,-2,0,2,0},yp[16]={0,2,2,0,-2,0,0,-2,2,4,4,2,0,2,2,0};
    int count[3]={0,0,4},type[4]={3,3,3,3};
    int result = IntersectPP(xp,yp,count, type);
    int expected = 3;
    ASSERT_EQUAL(expected, result);
xp[0]=-2;
xp[1]=-2;
xp[2]=-0.02;
xp[3]=-0.02;
yp[0]=2;
yp[1]=4;
yp[2]=4;
yp[3]=2;
xp[4]=2;
xp[5]=2;
xp[6]=3;
xp[7]=3;
yp[4]=0;
yp[5]=5;
yp[6]=5;
yp[7]=0;
xp[8]=-2;
xp[9]=-2;
xp[10]=10;
xp[11]=10;
yp[8]=-2;
yp[9]=10;
yp[10]=10;
yp[11]=-2;
xp[12]=0;
xp[13]=0;
xp[14]=2;
xp[15]=2;
yp[12]=0;
yp[13]=2;
yp[14]=2;
yp[15]=0;
result = IntersectPP(xp,yp,count, type);;
expected = 1;
ASSERT_EQUAL(expected, result);
    free(ret);
}












