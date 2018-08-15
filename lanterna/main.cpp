#include <cstdio>
#include <vector>
#include <queue>
#define nod first.first
#define dist first.second
#define wati second
using namespace std;
FILE *f=fopen("lanterna.in","r");
FILE *g=fopen("lanterna.out","w");
int D[55][1005];
bool B[55];
int a,c,b,d,N,M,K;
vector<pair<pair<int,int>,int> > G[55];
int ch(int W)
{
    queue<pair<int,int> > Q;
    while(!Q.empty()) Q.pop();
    for(int i=1;i<=N;i++)
        for(int j=0;j<=W;j++)
            D[i][j]=(1<<30);
    Q.push(make_pair(1,W));
    D[1][W]=0;
    while(!Q.empty())
    {
        pair<int,int> p=Q.front();
        Q.pop();
        for(auto it:G[p.first])
        {
            if(p.second>=it.wati)
            {
                if(B[it.nod])
                {
                    if(D[it.nod][W]>D[p.first][p.second]+it.dist)
                    {D[it.nod][W]=D[p.first][p.second]+it.dist;Q.push(make_pair(it.nod,W));}
                }
                else
                {
                    if(D[it.nod][p.second-it.wati]>D[p.first][p.second]+it.dist)
                        {D[it.nod][p.second-it.wati]=D[p.first][p.second]+it.dist;Q.push(make_pair(it.nod,p.second-it.wati));}
                }
            }
        }
    }
    int minim=(1<<30);
    for(int i=0;i<=W;i++)
        minim=min(minim,D[N][i]);
    return minim;
}
int main()
{
    fscanf(f,"%d%d",&N,&K);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d",&a);B[i]=a;
    }
    fscanf(f,"%d",&M);
    for(int i=1;i<=M;i++)
    {
        fscanf(f,"%d%d%d%d",&a,&b,&c,&d);
        G[a].push_back(make_pair(make_pair(b,c),d));
        G[b].push_back(make_pair(make_pair(a,c),d));
    }
    int val=ch(K),st=0,dr=K;
    while(st<dr)
    {
        int mid=(st+dr)/2;
        if(ch(mid)>val)
            st=mid+1;
        else
            dr=mid;
    }
    fprintf(g,"%d %d",ch(st),st);
    fclose(f);
    fclose(g);
    return 0;
}
