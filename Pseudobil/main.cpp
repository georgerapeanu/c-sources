#include <cstdio>
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
FILE *f=fopen("pseudobil.in","r");
FILE *g=fopen("pseudobil.out","w");
int N,M,K;
int D;
int P;
int V[3005][3005];
void ord(int &x,int &y)
{
    int nx=x+y-1;
    int ny=N+y-x;
    x=nx;y=ny;
}
int main()
{
    fscanf(f,"%d",&P);
    fscanf(f,"%d%d%d",&N,&K,&D);
    if(P==1)
    {
        int nr=0;
        int val=1;
        for(int i=1;i<D/2;i++)
        {
            nr+=2*val;val+=2;
        }
        nr+=val;
        fprintf(g,"%d",nr);
    }
    else
    {
        for(int i=1;i<=K;i++)
        {
            int x,y,nx,ny;
            fscanf(f,"%d %d",&x,&y);nx=x;ny=y;
            ord(nx,ny);
            V[nx][ny]++;
        }
        for(int i=1;i<=2*N+1;i++)
            for(int j=1;j<=2*N+1;j++)
                {
                    V[i][j]+=(V[i][j-1]+V[i-1][j]-V[i-1][j-1]);
                }
        fscanf(f,"%d",&M);
        for(int i=1;i<=M;i++)
        {
            int x,y,nx,ny;
            fscanf(f,"%d %d",&x,&y);nx=x;ny=y;
            ord(nx,ny);
            int l=D+1;
            ny=ny-(l-1);
            fprintf(g,"%d\n",V[nx+l-1][ny+l-1]-V[nx+l-1][ny-1]-V[nx-1][ny+l-1]+V[nx-1][ny-1]);
        }
    }
    fclose(f);
    fclose(g);
    return 0;
}
