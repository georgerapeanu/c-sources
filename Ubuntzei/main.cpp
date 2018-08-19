#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <vector>
using namespace std;
FILE *f=fopen("ubuntzei.in","r");
FILE *g=fopen("ubuntzei.out","w");
int dist[2005][2005];
vector<pair<int,int> > G[2005];
priority_queue<pair<int,int> ,vector<pair<int,int> > ,greater<pair<int,int> > > H;
int N,M,K;
int dp[1<<15][17];
int ceva[20];
int main()
{
    fscanf(f,"%d%d%d",&N,&M,&K);
    for(int i=1;i<=K;i++)fscanf(f,"%d",&ceva[i]);
    for(int i=1;i<=M;i++)
    {
        int x,y,z;
        fscanf(f,"%d %d %d",&x,&y,&z);
        G[x].push_back({y,z});
        G[y].push_back({x,z});
    }
    ceva[0]=1;
    ceva[K+1]=N;
    for(int i=0;i<=K+1;i++)
    {
        for(int j=1;j<=N;j++)dist[ceva[i]][j]=1<<28;
        dist[ceva[i]][ceva[i]]=0;
        H.push({0,ceva[i]});
        ///cout<<i<<"\n";
        while(!H.empty())
        {
            int nod=H.top().second;
            int cost=H.top().first;
            H.pop();
            if(cost!=dist[ceva[i]][nod])continue;
            for(auto it:G[nod])
                if(dist[ceva[i]][it.first]>dist[ceva[i]][nod]+it.second)
                {
                    dist[ceva[i]][it.first]=dist[ceva[i]][nod]+it.second;
                    H.push({dist[ceva[i]][it.first],it.first});
                }
        }
    }
    if(!K)
    {
        fprintf(g,"%d",dist[1][N]);
        return 0;
    }
    for(int i=0;i<(1<<K);i++)for(int j=0;j<=K;j++)dp[i][j]=1<<28;
    for(int i=1;i<=K;i++)
    {
        dp[1<<(i-1)][i]=dist[1][ceva[i]];
    }
    for(int conf=2;conf<(1<<K);conf++)
    {
        for(int j=1;j<=K;j++)
        {
            if((conf>>(j-1))&1)
            {
                for(int k=1;k<=K;k++)
                {
                    dp[conf][j]=min(dp[conf][j],dp[conf^(1<<(j-1))][k]+dist[ceva[k]][ceva[j]]);
                }
            }
        }
    }
    int rez=1<<28;
    for(int i=1;i<=K;i++)rez=min(rez,dp[(1<<K)-1][i]+dist[ceva[i]][N]);
    fprintf(g,"%d",rez);
    fclose(f);
    fclose(g);
    return 0;
}
