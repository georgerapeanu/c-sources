#include <cstdio>
#include <vector>
#include <queue>
#include <bitset>
#define nod first
#define pre second.first
#define unde second.second
#define mp make_pair
using namespace std;
FILE *f=fopen("statiuni.in","r");
FILE *g=fopen("statiuni.out","w");
queue<pair<int,pair<int,int> > > Q;
vector<int> G[100005];
int val[100005];
int N,K;
int x,y;
int D[100005][2];
int main()
{
    fscanf(f,"%d%d",&N,&K);
    for(int i=1;i<N;i++)
    {
        fscanf(f,"%d %d",&x,&y);
        G[x].push_back(y);
        G[y].push_back(x);
    }
    for(int i=1;i<=N;i++)
    {
        D[i][0]=D[i][1]=(1<<30);
        if(G[i].size()==1)
        {
            Q.push(make_pair(i,mp(0,0)));
            D[i][0]=0;
        }
    }
    while(!Q.empty())
    {
        pair<int,pair<int,int> > p=Q.front();
        Q.pop();
        for(auto it:G[p.nod])
        {
            if(it==p.pre) continue;
            if(D[it][0]>D[p.nod][p.unde]+1)
            {
                D[it][0]=D[p.nod][p.unde]+1;
                Q.push(mp(it,mp(p.nod,0)));
            }
            else if(D[it][1]>D[p.nod][p.unde]+1)
            {
                D[it][1]=D[p.nod][p.unde]+1;
                Q.push(mp(it,mp(p.nod,1)));
            }
        }
    }
    int rez=0;
    for(int i=1;i<=N;i++)
    {
        rez+=(D[i][1]<=K);
    }
    fprintf(g,"%d",rez);
    fclose(f);
    fclose(g);
    return 0;
}
