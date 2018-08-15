#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
FILE *f=fopen("maxflow.in","r");
FILE *g=fopen("maxflow.out","w");
int F[1005][1005];
int C[1005][1005];
int T[1005];
bool viz[1005];
int stq,drq;
int Q[1005];
int fr[1005];
vector<int> G[1005];
int K;
int N,M,tmp;
bool BFS(int S,int D)
{
    stq=drq=1;
    Q[1]=S;
    memset(viz,0,sizeof(viz));
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
int maxflow(int S,int D)
{
    int flow=0;
    while(BFS(S,D))
    {
        for(auto it:G[D])
        {
            if(viz[it]&&F[it][D]<C[it][D])
            {
                int fmin=1<<30;
                T[D]=it;
                for(int nod=D;nod!=S;nod=T[nod])fmin=min(fmin,C[T[nod]][nod]-F[T[nod]][nod]);
                if(!fmin)continue;
                for(int nod=D;nod!=S;nod=T[nod]){F[T[nod]][nod]+=fmin;F[nod][T[nod]]-=fmin;}
                flow+=fmin;
            }
        }
    }
    return flow;
}
int main()
{
    fscanf(f,"%d %d",&N,&M);
    for(int i=1;i<=M;i++)
    {
        int x,y,c;
        fscanf(f,"%d %d %d",&x,&y,&c);
        G[x].push_back(y);
        G[y].push_back(x);
        C[x][y]+=c;
    }
    fprintf(g,"%d",maxflow(1,N));
    return 0;
}
