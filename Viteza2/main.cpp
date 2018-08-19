#include <cstdio>
#include <algorithm>
#define dist first
#define a second.first
#define b second.second
#define inf 1000000000
using namespace std;
FILE *f=fopen("viteza2.in","r");
FILE *g=fopen("viteza2.out","w");
int dp[1005][1005];
int N,M;
pair <int,pair<int,int> > V[5005];
int main()
{
    fscanf(f,"%d%d",&N,&M);
    for(int i=1;i<=M;i++)
    {
        fscanf(f,"%d %d %d",&V[i].a,&V[i].b,&V[i].dist);
    }
    sort(V+1,V+1+M);
    for(int i=1;i<=N;i++)
        for(int j=1;j<=N;j++)
            dp[i][j]=inf;
    for(int i=1;i<=N;i++)
        dp[i][i]=0;
    for(int i=1;i<=M;i++)
    {
        for(int j=1;j<=N;j++)
        {
            dp[j][V[i].b]=min(dp[j][V[i].b],dp[j][V[i].a]+V[i].dist);
            dp[j][V[i].a]=min(dp[j][V[i].a],dp[j][V[i].b]+V[i].dist);
        }
    }
    for(int i=1;i<=N;i++,fprintf(g,"\n"))
        for(int j=1;j<=N;j++)
            fprintf(g,"%d ",dp[i][j]!=inf ? dp[i][j]:-1);
    fclose(f);
    fclose(g);
    return 0;
}
