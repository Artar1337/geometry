#ifndef INTER_GUARD
#define INTER_GUARD
int Intersects(
        int type,
        float rad[],
        float xc[],
        float yc[],
        float xt[],
        float yt[],
        float xp[],
        float yp[],
        int count[]);
int IntersectCC(float rad[], float xc[], float yc[], int count[]);
int IntersectCT(
        float rad[],
        float xc[],
        float yc[],
        float xt[],
        float yt[],
        int count[]);
int IntersectCP(
        float rad[],
        float xc[],
        float yc[],
        float xp[],
        float yp[],
        int count[]);
int IntersectTC(
        float rad[],
        float xc[],
        float yc[],
        float xt[],
        float yt[],
        int count[]);
int IntersectTT(float xt[], float yt[], int count[]);
int IntersectTP(float xt[], float yt[], float xp[], float yp[], int count[]);
int IntersectPC(
        float rad[],
        float xc[],
        float yc[],
        float xp[],
        float yp[],
        int count[]);
int IntersectPT(float xt[], float yt[], float xp[], float yp[], int count[]);
int IntersectPP(float xp[], float yp[], int count[]);
#endif
