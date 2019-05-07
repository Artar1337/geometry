#include "intersects.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
extern int* ret;
extern const int n;
extern const int N;
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
            // printf("%d. Circle(%6.2f,%6.2f,%6.2f)\n",z+1,xc[z],yc[z],rad[z]);
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
                } else
                    y1 = (-B + sqrt(D)) / 2;
                if (x1 >= xmin && x1 <= xmax && y1 <= ymax && y1 >= ymin) {
                    flag = 1;
                    break;
                }
            }
        }
        if (flag) {
            // printf("%d.
            // Triangle(%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f)\n",i,xt[i*3-3],yt[i*3-3],xt[i*3-2],yt[i*3-2],xt[i*3-1],yt[i*3-1],xt[i*3-3],yt[i*3-3]);
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
            // printf("%d.
            // Polygone(%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f)\n",i,xp[i*4-4],yp[i*4-4],xp[i*4-3],yp[i*4-3],xp[i*4-2],yp[i*4-2],xp[i*4-1],yp[i*4-1],xp[i*4-4],yp[i*4-4]);
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

int Intersects(
        int ftype,
        float rad[],
        float xc[],
        float yc[],
        float xt[],
        float yt[],
        float xp[],
        float yp[],
        int count[],
        int type[])
{
    int i, j = 0, flag = 0, r[N];
    for (i = 0; i < N; i++)
        ret[i] = r[i] = -1;

    if (ftype == 1) // circle
    {
        if (count[0] - 1 > 0) {
            if (IntersectCC(rad, xc, yc, count, type))
                flag = 1;
            i = 0;
            while (ret[i] >= 0) {
                r[j] = ret[i];
                ret[i] = -1;
                i++;
                j++;
            }
        }
        if (count[1]) {
            if (IntersectCT(rad, xc, yc, xt, yt, count, type))
                flag = 1;
            i = 0;
            while (ret[i] >= 0) {
                r[j] = ret[i];
                ret[i] = -1;
                i++;
                j++;
            }
        }
        if (count[2]) {
            if (IntersectCP(rad, xc, yc, xp, yp, count, type))
                flag = 1;
            i = 0;
            while (ret[i] >= 0) {
                r[j] = ret[i];
                ret[i] = -1;
                i++;
                j++;
            }
        }
    } else if (ftype == 2) // triangle
    {
        if (count[0]) {
            if (IntersectTC(rad, xc, yc, xt, yt, count, type))
                flag = 1;
            i = 0;
            while (ret[i] >= 0) {
                r[j] = ret[i];
                ret[i] = -1;
                i++;
                j++;
            }
        }
        if (count[1] - 1 > 0) {
            if (IntersectTT(xt, yt, count, type))
                flag = 1;
            i = 0;
            while (ret[i] >= 0) {
                r[j] = ret[i];
                ret[i] = -1;
                i++;
                j++;
            }
        }
        if (count[2]) {
            if (IntersectTP(xt, yt, xp, yp, count, type))
                flag = 1;
            i = 0;
            while (ret[i] >= 0) {
                r[j] = ret[i];
                ret[i] = -1;
                i++;
                j++;
            }
        }
    } else if (ftype == 3) // polygone
    {
        if (count[0]) {
            if (IntersectPC(rad, xc, yc, xp, yp, count, type))
                flag = 1;
            i = 0;
            while (ret[i] >= 0) {
                r[j] = ret[i];
                ret[i] = -1;
                i++;
                j++;
            }
        }
        if (count[1]) {
            if (IntersectPT(xt, yt, xp, yp, count, type))
                flag = 1;
            i = 0;
            while (ret[i] >= 0) {
                r[j] = ret[i];
                ret[i] = -1;
                i++;
                j++;
            }
        }
        if (count[2] - 1 > 0) {
            if (IntersectPP(xp, yp, count, type))
                flag = 1;
            i = 0;
            while (ret[i] >= 0) {
                r[j] = ret[i];
                ret[i] = -1;
                i++;
                j++;
            }
        }
    }
    for (i = 0; i < N; i++)
        ret[i] = r[i];
    return flag;
}
void PrintIntersects(
        float rad[],
        float xc[],
        float yc[],
        float xt[],
        float yt[],
        float xp[],
        float yp[],
        int type[])
{
    int i = 0, j, *ind, nn, temp, cn = 0, tn = 0, pn = 0;
    while (ret[i] >= 0)
        i++;
    nn = i;
    ind = (int*)malloc(nn * sizeof(int));
    for (i = 0; i < nn; i++)
        ind[i] = ret[i];
    for (i = 0; i < nn - 1; i++) {
        for (j = nn - 1; j > i; j--) {
            if (ind[j] < ind[j - 1]) {
                temp = ind[j];
                ind[j] = ind[j - 1];
                ind[j - 1] = temp;
            }
        }
    }
    for (i = 0; i < nn; i++) {
        if (type[ind[i]] == 1) {
            cn++;
            printf("%d. Circle(%6.2f,%6.2f,%6.2f)\n",
                   ind[i] + 1,
                   xc[cn],
                   yc[cn],
                   rad[cn]);
        } else if (type[ind[i]] == 2) {
            tn++;
            printf("%d. "
                   "Triangle(%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f)"
                   "\n",
                   ind[i] + 1,
                   xt[tn * 3 - 3],
                   yt[tn * 3 - 3],
                   xt[tn * 3 - 2],
                   yt[tn * 3 - 2],
                   xt[tn * 3 - 1],
                   yt[tn * 3 - 1],
                   xt[tn * 3 - 3],
                   yt[tn * 3 - 3]);
        } else if (type[ind[i]] == 3) {
            pn++;
            printf("%d. "
                   "Polygone(%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%6.2f,%"
                   "6.2f,%6.2f)\n",
                   ind[i] + 1,
                   xp[pn * 4 - 4],
                   yp[pn * 4 - 4],
                   xp[pn * 4 - 3],
                   yp[pn * 4 - 3],
                   xp[pn * 4 - 2],
                   yp[pn * 4 - 2],
                   xp[pn * 4 - 1],
                   yp[pn * 4 - 1],
                   xp[pn * 4 - 4],
                   yp[pn * 4 - 4]);
        }
    }
    free(ind);
}
