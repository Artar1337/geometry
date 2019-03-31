#include "figures.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n = 0;

const int N = 10;
const char A[] = "circle(", B[] = "triangle(", C[] = "polygone(";

int main()
{
    int ic = 7, pc = 0, kc = 7, jc = 0, z, flag = 1;
    float r, c, rad[N], ix[2], xc[N], yc[N], xt[3 * N], yt[3 * N], xp[4 * N],
            yp[4 * N];
    char s[80], s1[80] = {0}, exit[] = "exit", emp[] = "\0";
    printf("Input data in type: "
           "\n'circle(x,y,r)'\n'triangle(x1,y1,x2,y2,x3,y3)'\n'polygone(x1,y1,"
           "x2,y2,x3,y3,x4,y4)'\nTo exit input 'exit'.\n");

    while (1) {
        printf("\nInput data: ");
        scanf("%s", s);

        if (strncmp(A, s, 7) == 0) {
            while (pc < 2) {
                if (s[ic] == ',') {
                    ix[pc] = atof(s1);
                    strcpy(s1, emp);
                    pc++;
                    kc++;
                } else if (
                        s[ic] == '.' || s[ic] == '0' || s[ic] == '1'
                        || s[ic] == '2' || s[ic] == '3' || s[ic] == '4'
                        || s[ic] == '5' || s[ic] == '6' || s[ic] == '7'
                        || s[ic] == '8' || s[ic] == '9') {
                    strncat(s1, s + kc, 1);
                    kc++;
                } else {
                    pc = 0;

                    printf("Wrong data type! Try again.\n");
                    break;
                }
                ic++;
            }

            while (pc != 0) {
                if (s[ic] == ')') {
                    r = atof(s1);
                    strcpy(s1, emp);
                    xc[jc] = ix[0];
                    yc[jc] = ix[1];
                    rad[jc] = r;
                    jc++;
                    circle(ix[0], ix[1], r);
                    pc = 0;
                } else if (
                        s[ic] == '.' || s[ic] == '0' || s[ic] == '1'
                        || s[ic] == '2' || s[ic] == '3' || s[ic] == '4'
                        || s[ic] == '5' || s[ic] == '6' || s[ic] == '7'
                        || s[ic] == '8' || s[ic] == '9') {
                    strncat(s1, s + kc, 1);
                    kc++;
                } else {
                    printf("Wrong data type! Try again.\n");
                    break;
                }
                ic++;
            }
            strcpy(s1, emp);
            kc = 7;
            pc = 0;
            ic = 7;
            /*printf("Intersects:\n");
            for(z=0;z<j;z++)
            {
            if(x[z]==x[j]&&y[z]==y[j]) continue;
            c=sqrt((x[z]-x[j])*(x[z]-x[j])+(y[z]-y[j])*(y[z]-y[j]));
            if(c<fabs(rad[j]-rad[z])) continue;
            if(c<=rad[j]||c<=rad[z])
            {
            flag=0;
            printf("%d. Circle\n",z+1);
            }

            }
            if(flag)
            printf("none\n");
            flag=1;*/

        }

        else if (strcmp(s, exit) == 0) {
            printf("Executing stopped!\n");
            break;
        }

        else if (strncmp(B, s, 9) == 0) {
            break;
        }

        else if (strncmp(C, s, 9) == 0) {
            break;
        }

        else {
            printf("Wrong data type! Try again.\n");
        }
    }
    return 0;
}
