#include <cstdio>
using namespace std;
FILE *f=fopen("joc1.in","r");
FILE *g=fopen("joc1.out","w");
int M[150][150],i,j,N,M1,rez;
char c,r[150];
int figura1(int X,int Y)
{
    int nr=0;
    if(M[X][Y]&&M[X+1][Y]&&M[X+2][Y]&&M[X+2][Y+1]&&M[X+2][Y+2])
        nr++;
    if(M[X][Y]&&M[X+1][Y]&&M[X+2][Y]&&M[X][Y+1]&&M[X][Y+2])
        nr++;
    if(M[X][Y]&&M[X][Y+1]&&M[X][Y+2]&&M[X+1][Y+2]&&M[X+2][Y+2])
        nr++;
    if(Y>2&&M[X][Y]&&M[X+1][Y]&&M[X+2][Y]&&M[X+2][Y-1]&&M[X+2][Y-2])
        nr++;
    return nr;
}
int figura2(int X,int Y)
{
    int nr=0;
    if(M[X][Y]&&M[X+1][Y]&&M[X+1][Y+1]&&M[X+1][Y+2]&&M[X+2][Y])
        nr++;
    if(M[X][Y]&&M[X][Y+1]&&M[X][Y+2]&&M[X+1][Y+1]&&M[X+2][Y+1])
        nr++;
    if(Y>2&&M[X][Y]&&M[X+1][Y]&&M[X+2][Y]&&M[X+1][Y-1]&&M[X+1][Y-2])
       nr++;
    if(Y>1&&M[X][Y]&&M[X+1][Y]&&M[X+2][Y]&&M[X+2][Y-1]&&M[X+2][Y+1])
        nr++;
    return nr;
}
int figura3(int X,int Y)
{
    int nr=0;
    if(Y>1&&M[X][Y]&&M[X][Y+1]&&M[X+1][Y]&&M[X+1][Y-1]&&M[X+2][Y])
        nr++;
    if(Y>1&&M[X][Y]&&M[X+1][Y]&&M[X+1][Y-1]&&M[X+1][Y+1]&&M[X+2][Y+1])
       nr++;
    if(Y>1&&M[X][Y]&&M[X+1][Y]&&M[X+1][Y+1]&&M[X+2][Y]&&M[X+2][Y-1])
       nr++;
    if(M[X][Y]&&M[X+1][Y]&&M[X+1][Y+1]&&M[X+1][Y+2]&&M[X+2][Y+1])
       nr++;
    return nr;
}
int main()
{
    fscanf(f,"%d %d\n",&N,&M1);
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=M1;j++)
            {c=fgetc(f);M[i][j]=c-'0';}
        fscanf(f,"\n");
    }
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=M1;j++)
        {
            if(M[i][j])
                rez=rez+figura1(i,j)+figura2(i,j)+figura3(i,j);
        }
    }
    sprintf(r,"%d\n",rez);
    fputs(r,g);
    fclose(f);
    fclose(g);
    return 0;
}
