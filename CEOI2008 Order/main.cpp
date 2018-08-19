#include <vector>
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
int N,M;
vector<int> G[3005];
int S=0,D=3000;
long long C[3005][3005];
long long F[3005][3005],rez;
int T[3005];
bool viz[3005];
int Q[3005];
int stq,drq;
bool BFS(int S,int D)
{
    memset(viz,0,sizeof(viz));
    stq=1;drq=1;
    Q[stq]=S;
    viz[S]=1;
    while(stq<=drq)
    {
        int nod=Q[stq++];
        if(nod==D)continue;
        for(auto it:G[nod])
        {
            if(!viz[it]&&F[nod][it]<C[nod][it])
            {
                viz[it]=1;
                T[it]=nod;
                Q[++drq]=it;
            }
        }
    }
    return viz[D];
}
long long maxflow(int S,int D)
{
    long long flow=0;
    while(BFS(S,D))
    {
        for(auto it:G[D])
        {
            if(viz[it]&&F[it][D]<C[it][D])
            {
                long long fmin=1LL<<62;
                T[D]=it;
                for(int nod=D;nod!=S;nod=T[nod])fmin=min(fmin,C[T[nod]][nod]-F[T[nod]][nod]);
                if(!fmin)continue;
                flow+=fmin;
                for(int nod=D;nod!=S;nod=T[nod]){F[T[nod]][nod]+=fmin;F[nod][T[nod]]-=fmin;}
            }
        }
    }
    return flow;
}
int main()
{
    freopen("in","r",stdin);
    freopen("out","w",stdout);
    cin>>N>>M;
    for(int i=1;i<=N;i++)
    {
        G[i].push_back(S);
        G[S].push_back(i);
        int v,m;
        cin>>v>>m;
        C[S][i]=v;
        rez+=v;
        for(int j=1;j<=m;j++)
        {
            int r,m;
            cin>>m>>r;
            C[i][m+1200]=r;
            G[i].push_back(m+1200);
            G[m+1200].push_back(i);
        }
    }
    for(int i=1;i<=M;i++)
    {
        int s;
        cin>>s;
        G[i+1200].push_back(D);
        G[D].push_back(i+1200);
        C[i+1200][D]=s;
    }
    cout<<rez-maxflow(S,D);
    return 0;
}
