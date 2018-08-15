#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
vector<int> G[105];
int N;
long long V[105];
long long C[105][105];
long long F[105][105];
int T[105];
bool viz[105];
int S=0,D=104;
int stq,drq;
int Q[105];
bool BFS(int S,int D)
{
    memset(viz,0,sizeof(viz));
    viz[S]=1;
    Q[stq=drq=1]=S;
    while(stq<=drq)
    {
        int nod=Q[stq++];
        if(nod==D)continue;
        for(auto it:G[nod])
        {
            if(!viz[it]&&F[nod][it]<C[nod][it])
            {
                T[it]=nod;
                viz[it]=1;
                Q[++drq]=it;
            }
        }
    }
    return viz[D];
}
long long flux(int S,int D)
{
    long long maxflow=0;
    while(BFS(S,D))
    {
        for(auto it:G[D])
        {
            if(F[it][D]==C[it][D])continue;
            long long fmin=1LL<<60;
            for(int nod=D;nod!=S;nod=T[nod])
            {
                fmin=min(fmin,C[T[nod]][nod]-F[T[nod]][nod]);
            }
            if(!fmin)continue;
            maxflow+=fmin;
            for(int nod=D;nod!=S;nod=T[nod])
            {
                F[T[nod]][nod]+=fmin;
                F[nod][T[nod]]-=fmin;
            }
        }
    }
    return maxflow;
}
long long rez=0;
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>V[i];
        if(V[i]>=0)
        {
            rez+=V[i];
            C[i][D]=V[i];
            G[i].push_back(D);
            G[D].push_back(i);
        }
        else
        {
            C[S][i]=-V[i];
            G[S].push_back(i);
            G[i].push_back(S);
        }
    }
    for(int i=1;i<=N;i++)
    {
        for(int j=i*2;j<=N;j+=i)
        {
            C[i][j]=1LL<<50;
            G[i].push_back(j);
            G[j].push_back(i);
        }
    }
    rez-=flux(S,D);
    cout<<rez;
    return 0;
}
