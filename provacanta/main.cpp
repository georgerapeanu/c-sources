#include <cstdio>
#include <cstring>
#include <algorithm>
#define nmax 105
#define kmax 1005
#define inf 7500000
#define t first
#define c second
using namespace std;
FILE *f=fopen("provacanta.in","r");
FILE *g=fopen("provacanta.out","w");
int lucru[nmax][nmax][kmax];
int vacanta[nmax][nmax][kmax];
int domnuIohanis[nmax][nmax];
int T;
int N,M,K;
int rez;///il ador pe eudanip
pair<int,int> P[nmax],V[nmax];
int main()
{
    for(int i=1;i<nmax;i++)
        domnuIohanis[i][0]=(i*(i-1))/2;
    for(int i=1;i<nmax;i++)
    {
        for(int j=1;j<nmax;j++)
        {
            domnuIohanis[i][j]=(1<<30);
            for(int k=1;k<=i;k++)
            {
                domnuIohanis[i][j]=min(domnuIohanis[i-k][j-1]+(k*(k-1))/2,domnuIohanis[i][j]);
            }
        }
    }
    fscanf(f,"%d",&T);
    while(T--)
    {
        fscanf(f,"%d%d%d",&N,&M,&K);
        for(int i=1;i<=N;i++)
            fscanf(f,"%d%d",&P[i].t,&P[i].c);
        for(int i=1;i<=M;i++)
            fscanf(f,"%d%d",&V[i].t,&V[i].c);
        for(int i=1;i<nmax;i++)
            for(int j=0;j<nmax;j++)
                for(int k=0;k<kmax;k++)
                    lucru[i][j][k]=vacanta[i][j][k]=-(1<<30);
        for(int i=1;i<=N;i++)
        {
            for(int j=1;j<=N;j++)
            {
                for(int k=1;k<=K;k++)
                {
                    lucru[i][j][k]=max(lucru[i][j-1][k],lucru[i][j][k-1]);
                    if(k>=P[j].t)
                        lucru[i][j][k]=max(lucru[i][j][k],lucru[i-1][j-1][k-P[j].t]+P[j].c);
                }
            }
        }
        for(int i=1;i<=M;i++)
        {
            for(int j=1;j<=M;j++)
            {
                for(int k=1;k<=K;k++)
                {
                    vacanta[i][j][k]=max(vacanta[i][j-1][k],vacanta[i][j][k-1]);
                    if(k>=V[j].t)
                        vacanta[i][j][k]=max(vacanta[i][j][k],vacanta[i-1][j-1][k-V[j].t]+V[j].c);
                }
            }
        }
        rez=0;
        for(int i=0;i<=N;i++)
            for(int j=0;j<=M;j++)
                for(int k=domnuIohanis[i][j];k<=K;k++)
                    if(rez<vacanta[j][M][K-k]+lucru[i][N][k-domnuIohanis[i][j]])
                        rez=vacanta[j][M][K-k]+lucru[i][N][k-domnuIohanis[i][j]];
        fprintf(g,"%d\n",rez);
    }
    fclose(f);
    fclose(g);
    return 0;
}
