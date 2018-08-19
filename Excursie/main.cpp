#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#define EPS 0.000001
using namespace std;
FILE *f=fopen("excursie.in","r");
FILE *g=fopen("excursie.out","w");
double dp[2501][51][51];
double D[2501][51][51];
int N,M,L=100,stx,sty,drx,dry;
int C[51][51];
int dx[]={-1,0,1,0};
int dy[]={0,1,0,-1};
double rez=10000000,dist,lmax;
int main()
{
    fscanf(f,"%d %d %lf",&N,&M,&lmax);
    for(int i=1;i<=N;i++)
        for(int j=1;j<=M;j++)
            fscanf(f,"%d",&C[i][j]);
    fscanf(f,"%d%d%d%d",&stx,&sty,&drx,&dry);
    for(int l=0;l<=L;l++)
        for(int i=1;i<=N;i++)
            for(int j=1;j<=M;j++)
                dp[l][i][j]=10000000;
    dp[0][stx][sty]=0;
    for(int l=1;l<=L;l++)
    {
        for(int i=1;i<=N;i++)
        {
            for(int j=1;j<=M;j++)
            {
                for(int k=0;k<4;k++)
                {
                    int nx=i+dx[k],ny=j+dy[k];
                    if(nx&&ny&&nx<=N&&ny<=M)
                    {
                        double d=sqrt(pow(C[i][j]-C[nx][ny],2)+1);
                        if(C[nx][ny]>C[i][j])
                        {
                            if(dp[l][i][j]>dp[l-1][nx][ny]+d*abs(C[i][j]-C[nx][ny])/2)
                            {
                                dp[l][i][j]=dp[l-1][nx][ny]+d*abs(C[i][j]-C[nx][ny])/2;
                                D[l][i][j]=D[l-1][nx][ny]+d;
                            }
                        }
                        else if(C[nx][ny]<C[i][j])
                        {
                            if(dp[l][i][j]>dp[l-1][nx][ny]+d*abs(C[i][j]-C[nx][ny]))
                            {
                                dp[l][i][j]=dp[l-1][nx][ny]+d*abs(C[i][j]-C[nx][ny]);
                                D[l][i][j]=D[l-1][nx][ny]+d;
                            }
                        }
                        else
                        {
                            if(dp[l][i][j]>dp[l-1][nx][ny]+1)
                            {
                                dp[l][i][j]=dp[l-1][nx][ny]+1;
                                D[l][i][j]=D[l-1][nx][ny]+d;
                            }
                        }
                    }
                }
            }
        }
    }
    for(int l=0;l<=L;l++)
        if(rez>dp[l][drx][dry]&&D[l][drx][dry]<=lmax){rez=dp[l][drx][dry];dist=D[l][drx][dry];}
    fprintf(g,"%.3f %.3f",rez,dist);
    fclose(f);
    fclose(g);
    return 0;
}
