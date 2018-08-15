#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
FILE *f=fopen("joc13.in","r");
FILE *g=fopen("joc13.out","w");
int D[3][5005][11];
int N,K;
int V[3][5005];
int main()
{
    fscanf(f,"%d%d",&N,&K);
    for(int i=1;i<=2;i++)
        for(int j=1;j<=N;j++)
            fscanf(f,"%d",&V[i][j]);
    D[1][1][1]=V[1][1];
    D[2][1][1]=V[1][1]+V[2][1];
    for(int i=2;i<=N;i++)
    {
        for(int k=min(K,i);k;k--)
        {
            if(k==1)
            {
                int ma=-(1<<30),mb=-(1<<30);
                for(int j=2;j<=K&&j<=i;j++)
                {
                    ma=max(ma,D[1][i][j]);
                    mb=max(mb,D[2][i][j]);
                }
                D[1][i][k]=mb+V[1][i];
                D[2][i][k]=ma+V[2][i];
            }
            else
            {
                D[1][i][k]=D[1][i-1][k-1]+V[1][i];
                D[2][i][k]=D[2][i-1][k-1]+V[2][i];
            }
        }
    }
    int rez=-(1<<30);
    for(int i=1;i<=K;i++)
        rez=max(rez,D[2][N][i]);
    fprintf(g,"%d",rez);
    fclose(f);
    fclose(g);
    return 0;
}
