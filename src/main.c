#include "figures.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int n = 0;

const int N = 10;
const char A[] = "circle(", B[] = "triangle(", C[] = "polygone(";

int main()
{
    int i, ic = 7, pc = 0, kc = 7, jc = 0, it = 9, jt = 0, kt = 9, pt = 0,
           jp = 0;
    float r, c, rad[N], ix[8], xc[N], yc[N], xt[3 * N], yt[3 * N], xp[4 * N],
            yp[4 * N];
    char s[80], s1[80] = {0}, exit[] = "exit", emp[] = "\0";
    printf("Input data in type: "
           "\n'circle(x,y,r)'\n'triangle(x1,y1,x2,y2,x3,y3)'\n'polygone(x1,y1,"
           "x2,y2,x3,y3,x4,y4)'\nTo exit input 'exit'.\n");

    while (1) {
        printf("\nInput data: ");
        scanf("%s", s);

        /*CHECK FOR CIRCLE*/
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
                        || s[ic] == '8' || s[ic] == '9' || s[ic] == '-') {
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
        }

        else if (strcmp(s, exit) == 0) {
            printf("Executing stopped!\n");
            break;
        }

        /*CHECK FOR TRIANGLE*/
        else if (strncmp(B, s, 9) == 0) {
            while (pt < 6) {
                if (s[it] == ',') {
                    ix[pt] = atof(s1);
                    strcpy(s1, emp);
                    pt++;
                    kt++;
                } else if (
                        s[it] == '.' || s[it] == '0' || s[it] == '1'
                        || s[it] == '2' || s[it] == '3' || s[it] == '4'
                        || s[it] == '5' || s[it] == '6' || s[it] == '7'
                        || s[it] == '8' || s[it] == '9' || s[it] == '-') {
                    strncat(s1, s + kt, 1);
                    kt++;
                } else if (pt == 5 && s[it] == ')') {
                    ix[pt] = atof(s1);
                    for (i = 0; i < 6; i += 2) {
                        xt[jt] = ix[i];
                        yt[jt] = ix[i + 1];
                        jt++;
                    }
                    pt++;
                    triangle(ix[0], ix[1], ix[2], ix[3], ix[4], ix[5]);
                } else {
                    printf("Wrong data type! Try again.\n");
                    break;
                }
                it++;
            }
            strcpy(s1, emp);
            it = 9;
            kt = 9;
            pt = 0;
        }

        /*CHECK FOR POLYGONE*/
        else if (strncmp(C, s, 9) == 0) {
            while (pt < 8) {
                if (s[it] == ',') {
                    ix[pt] = atof(s1);
                    strcpy(s1, emp);
                    pt++;
                    kt++;
                } else if (
                        s[it] == '.' || s[it] == '0' || s[it] == '1'
                        || s[it] == '2' || s[it] == '3' || s[it] == '4'
                        || s[it] == '5' || s[it] == '6' || s[it] == '7'
                        || s[it] == '8' || s[it] == '9' || s[it] == '-') {
                    strncat(s1, s + kt, 1);
                    kt++;
                } else if (pt == 7 && s[it] == ')') {
                    ix[pt] = atof(s1);
                    for (i = 0; i < 8; i += 2) {
                        xt[jp] = ix[i];
                        yt[jp] = ix[i + 1];
                        jp++;
                    }
                    pt++;
                    polygone(
                            ix[0],
                            ix[1],
                            ix[2],
                            ix[3],
                            ix[4],
                            ix[5],
                            ix[6],
                            ix[7]);
                } else {
                    printf("Wrong data type! Try again.\n");
                    break;
                }
                it++;
            }
            strcpy(s1, emp);
            it = 9;
            kt = 9;
            pt = 0;
        }

        else {
            printf("Wrong data type! Try again.\n");
        }
    }
    return 0;
}
