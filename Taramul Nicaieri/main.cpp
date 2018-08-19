#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
FILE *f=fopen("harta.in","r");
FILE *g=fopen("harta.out","w");
int C[205][205];
int F[205][205];
int q[205];
int T[205];
int stq,drq,N;
int S=0;
int D=204;
bool viz[205];
vector<int> G[205];
int muchii=0;
bool BFS(int S,int D)
{
    stq=drq=1;
    q[1]=S;
    memset(viz,0,sizeof(viz));
    while(stq<=drq)
    {
        int nod=q[stq++];
        if(nod==D)continue;
        for(auto it:G[nod])
        {
            if(!viz[it]&&F[nod][it]!=C[nod][it])
            {
                viz[it]=1;
                T[it]=nod;
                q[++drq]=it;
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
            if(viz[it]&&F[it][D]!=C[it][D])
            {
                int fmin=1<<30;
                T[D]=it;
                for(int nod=D;nod!=S;nod=T[nod])
                {
                    fmin=min(fmin,C[T[nod]][nod]-F[T[nod]][nod]);
                }
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
int main()
{
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++)
    {
        int a,b;
        fscanf(f,"%d %d",&a,&b);
        G[S].push_back(i);G[i].push_back(S);C[S][i]=a;
        G[D].push_back(i+N);G[i+N].push_back(D);C[N+i][D]=b;
        muchii+=a+b;
    }
    muchii>>=1;
    for(int i=1;i<=N;i++)for(int j=1;j<=N;j++)if(i!=j){G[i].push_back(j+N);G[j+N].push_back(i);C[i][j+N]=1;}
    maxflow(S,D);
    fprintf(g,"%d\n",muchii);
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=N;j++)
        {
            if(C[i][j+N]==F[i][j+N]&&C[i][j+N])
                fprintf(g,"%d %d\n",i,j);
        }
    }
    fclose(f);
    fclose(g);
    return 0;
}
