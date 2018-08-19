#include <cstdio>
#include <cstring>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
FILE *f=fopen("critice.in","r");
FILE *g=fopen("critice.out","w");
int stq,drq;
int N,M;
int Q[1005];
vector<int> G[1005];
int C[1005][1005];
int F[1005][1005];
int T[1005];
int rez=0;
bool viz[1005];
bool vizD[1005];
pair<int,int> E[10005];
set<int> S;
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
            if(!viz[it]&&C[nod][it]!=F[nod][it])
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
            if(viz[it]&&C[it][D]!=F[it][D])
            {
                T[D]=it;
                int fmin=1<<30;
                for(int nod=D;nod!=S;nod=T[nod])fmin=min(fmin,C[T[nod]][nod]-F[T[nod]][nod]);
                if(!fmin)continue;
                for(int nod=D;nod!=S;nod=T[nod])
                {
                    F[T[nod]][nod]+=fmin;
                    F[nod][T[nod]]-=fmin;
                }
                flow+=fmin;
            }
        }
    }
    return flow;
}
void dfs(int nod)
{
    vizD[nod]=1;
    for(auto it:G[nod])if(!vizD[it]&&C[it][nod]>F[it][nod])dfs(it);
}
int main()
{
    fscanf(f,"%d %d",&N,&M);
    for(int i=1;i<=M;i++)
    {
        int x,y,z;
        fscanf(f,"%d %d %d",&x,&y,&z);
        C[x][y]=z;C[y][x]=z;
        G[x].push_back(y);
        G[y].push_back(x);
        E[i]={x,y};
    }
    maxflow(1,N);BFS(1,N);dfs(N);
    for(int i=1;i<=M;i++)
    {
        int x=E[i].first,y=E[i].second;
        if((viz[x]&&vizD[y])||(viz[y]&&vizD[x]))S.insert(i);
    }
    fprintf(g,"%d\n",S.size());
    for(auto it:S)fprintf(g,"%d\n",it);
    fclose(f);
    fclose(g);
    return 0;
}
