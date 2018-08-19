#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
FILE *f=fopen("tournament.in","r");
FILE *g=fopen("tournament.out","w");
long long C[50*51/2+5][50*51/2+5];
long long F[50*51/2+5][50*51/2+5];
int T[50*51/2+5];
bool viz[50*51/2+5];
int q[50*51/2+5];
int stq,drq;
int N;
long long W[55];
long long R[55][55];
vector<int> G[50*51/2+5];
int S,D;
vector<int> rez;
bool bfs(int S,int D)
{
    stq=1;drq=1;q[1]=S;
    memset(viz,0,sizeof(viz));
    viz[S]=1;
    while(stq<=drq)
    {
        int nod=q[stq++];
        if(nod==D)continue;
        for(auto it:G[nod])
        {
            if(F[nod][it]<C[nod][it]&&!viz[it])
            {
                viz[it]=1;
                T[it]=nod;
                q[++drq]=it;
            }
        }
    }
    return viz[D];
}
long long maxflow(int S,int D)
{
    memset(F,0,sizeof(F));
    long long flux=0;
    while(bfs(S,D))
    {
        for(auto it:G[D])
        {
            if(F[it][D]<C[it][D]&&viz[it])
            {
                T[D]=it;
                long long fmin=1LL<<62;
                for(int nod=D;nod!=S;nod=T[nod])
                {
                    fmin=min(fmin,C[T[nod]][nod]-F[T[nod]][nod]);
                }
                if(fmin<=0)continue;
                for(int nod=D;nod!=S;nod=T[nod])
                {
                    F[T[nod]][nod]+=fmin;
                    F[nod][T[nod]]-=fmin;
                }
                flux+=fmin;
            }
        }
    }
    return flux;
}
int main()
{
    fscanf(f,"%d",&N);S=0;D=N*(N+1)/2+1;
    for(int i=1;i<=N;i++)fscanf(f,"%lld",&W[i]);
    for(int i=1;i<=N;i++)for(int j=1;j<=N;j++)fscanf(f,"%lld",&R[i][j]);
    for(int i=1;i<=N;i++)
    {
        memset(C,0,sizeof(C));for(int j=S;j<=D;j++)G[j].clear();
        long long WT=W[i],meciuri=0;
        for(int j=1;j<=N;j++)WT+=R[i][j];
        int nod=1;
        for(int j=1;j<=N;j++)
        {
            if(j!=i)
            {
                for(int k=j+1;k<=N;k++)
                {
                    if(k!=i)
                    {
                        meciuri+=R[j][k];
                        G[S].push_back(nod);G[nod].push_back(S);
                        C[S][nod]=R[j][k];
                        G[nod].push_back((N-1)*(N)/2+j);G[(N-1)*(N)/2+j].push_back(nod);
                        G[nod].push_back((N-1)*(N)/2+k);G[(N-1)*(N)/2+k].push_back(nod);
                        C[nod][(N-1)*(N)/2+j]=(1LL<<62);
                        C[nod][(N-1)*(N)/2+k]=(1LL<<62);
                        nod++;
                    }
                }
            }
        }
        for(int j=1;j<=N;j++)
        {
            if(i!=j)
            {
                C[(N-1)*(N)/2+j][D]=WT-W[j];
                G[(N-1)*(N)/2+j].push_back(D);G[D].push_back((N-1)*(N)/2+j);
            }
        }
        long long tmp=maxflow(S,D);
        if(tmp>=meciuri)
        {
            rez.push_back(i-1);
        }
    }
    fprintf(g,"%d\n",rez.size());
    for(auto it:rez)fprintf(g,"%d ",it);
    fclose(f);
    fclose(g);
    return 0;
}
