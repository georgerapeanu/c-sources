#include <cstdio>
#include <vector>
#include <cstring>
#include <queue>
using namespace std;
FILE *f=fopen("boom.in","r");
FILE *g=fopen("boom.out","w");
int cost[55];
int conf[55];
int N,M;
int dist[1<<20];
int ant[1<<20];
int op[1<<20];
int st[(1<<20)+5];
priority_queue<pair<int,int> ,vector<pair<int,int> >,greater<pair<int,int> > > H;
vector<pair<int,int> > G[1<<20];
int getconf(int conf)
{
    int rez=0;
    for(int j=0;j<N;j++)
    {
        if(j==0&&((conf>>1)&1))rez|=1;
        else if(j==N-1&&((conf>>(N-2))&1))rez|=(1<<(N-1));
        else if(((conf>>(j-1))&1)||((conf>>(j+1))&1))rez|=(1<<j);
    }
    return rez;
}
void getvec(int nod)
{
    if(G[nod].size())return;
    for(int i=1;i<=M;i++)
    {
        int ceva=nod&(((1<<N)-1)^conf[i]);
        G[nod].push_back({getconf(ceva),cost[i]});
    }
}
int main()
{
    fscanf(f,"%d%d",&N,&M);
    for(int i=1;i<=M;i++)
    {
        int nr;
        fscanf(f,"%d %d",&cost[i],&nr);
        for(int j=1;j<=nr;j++)
        {
            int val;
            fscanf(f,"%d",&val);
            conf[i]|=(1<<(val-1));
        }
    }
    for(int i=0;i<(1<<N);i++){dist[i]=(1<<30);ant[i]=-1;}
    dist[(1<<N)-1]=0;
    H.push({0,(1<<N)-1});
    while(!H.empty())
    {
        int cost,nod;
        cost=H.top().first;
        nod=H.top().second;
        H.pop();
        if(!nod)break;
        if(cost!=dist[nod])continue;
        getvec(nod);
        for(int i=0;i<G[nod].size();i++)
        {
            auto it=G[nod][i];
            if(dist[it.first]>dist[nod]+it.second)
            {
                dist[it.first]=dist[nod]+it.second;
                ant[it.first]=nod;op[it.first]=i+1;
                H.push({dist[it.first],it.first});
            }
        }
    }
    fprintf(g,"%d\n",dist[0]);
    int nod=0;
    while(nod!=(1<<N)-1)
    {
        st[++st[0]]=op[nod];
        nod=ant[nod];
    }
    fprintf(g,"%d\n",st[0]);
    while(st[0])fprintf(g,"%d\n",st[st[0]--]);
    fclose(f);
    fclose(g);
    return 0;
}
