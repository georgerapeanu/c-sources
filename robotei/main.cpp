#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
using namespace std;
long long N,M,X,Y;
long long MODX,MODY;
long long OFFX,OFFY;
long long W[1001][1001];
long long dist[1001][1001];
long long len;
long long rez[666734];
bool viz[1001][1001];
bool ok[1001][1001];
long long grX[1000005];
long long grY[1000005];
pair<long long,long long> adv(long long x,long long y)
{
    return {(1LL*x*x+OFFX)%MODX,(1LL*y*y+OFFY)%MODY};
}
void dfs(long long x,long long y)
{
    viz[x][y]=1;
    pair<long long,long long> tmp=adv(x,y);
    if(!viz[tmp.first][tmp.second])dfs(tmp.first,tmp.second);
    ok[x][y]|=ok[tmp.first][tmp.second];
    dist[x][y]=1+dist[tmp.first][tmp.second];
}
long long cate(long long dist,long long len,long long M)
{
    M-=dist;
    if(M<0)return 0;
    return 1+M/len;
}
int main()
{
    freopen("robotei.in","r",stdin);
    freopen("robotei.out","w",stdout);
    cin>>N>>M>>X>>Y>>MODX>>MODY>>OFFX>>OFFY;
    if(X>=MODX||Y>=MODY)
    {
        if(N!=1)cout<<"0 "<<N*N-1<<"\n";
        cout<<"1 1";
        return 0;
    }
    if(X>=N||Y>=N){cout<<"0 "<<N*N;return 0;}
    M--;
    for(long long i=0;i<N;i++)grX[(1LL*i*i+OFFX)%MODX]++;
    for(long long i=0;i<N;i++)grY[(1LL*i*i+OFFY)%MODY]++;
    for(long long i=0;i<MODX;i++)
    {
        for(long long j=0;j<MODY;j++)
        {
            W[i][j]=grX[i]*grY[j];
            ///cerr<<W[i][j]<<" ";
        }
        ///cerr<<"\n";
    }
    long long x=X,y=Y;
    do
    {
        viz[x][y]=1;
        pair<long long,long long> tmp=adv(x,y);
        x=tmp.first;
        y=tmp.second;
        len++;
    }
    while(!viz[x][y]);
    if(x!=X||y!=Y)
    {
        rez[1]++;
        rez[0]--;
        ok[X][Y]=1;viz[X][Y]=1;
        for(long long i=0;i<MODX;i++)
        {
            for(long long j=0;j<MODY;j++)
            {
                if(!viz[i][j])dfs(i,j);
            }
        }
        for(long long i=0;i<MODX;i++)
        {
            for(long long j=0;j<MODY;j++)
            {
                if(ok[i][j]&&dist[i][j]<=M)rez[1]+=W[i][j];
                else rez[0]+=W[i][j];
            }
        }
        for(long long i=0;i<=M+1;i++)if(rez[i])cout<<i<<" "<<rez[i]<<"\n";
    }
    else
    {
        memset(viz,0,sizeof(viz));
        ok[X][Y]=1;viz[X][Y]=1;
        dfs(X,Y);
        dist[X][Y]=0;
        for(long long i=0;i<MODX;i++)
        {
            for(long long j=0;j<MODY;j++)
            {
                if(!viz[i][j])dfs(i,j);
            }
        }
        for(long long i=0;i<MODX;i++)
        {
            for(long long j=0;j<MODY;j++)
            {
                if(ok[i][j])rez[cate(dist[i][j],len,M)]+=W[i][j];
                else rez[0]+=W[i][j];
            }
        }
        rez[cate(0,len,M+1)]++;
        rez[cate(len-1,len,M)]--;
        for(long long i=0;i<=M+1;i++)if(rez[i])cout<<i<<" "<<rez[i]<<"\n";
    }
    return 0;
}
