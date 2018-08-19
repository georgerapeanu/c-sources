#include <cstdio>
#include <vector>
#include <queue>
#define pb push_back
#define mp make_pair
#define dist first
#define n second
using namespace std;
FILE *f=fopen("camionas.in","r");
FILE *g=fopen("camionas.out","w");
vector<pair<int,int> > Gr[50005];
priority_queue <pair<int,int> > H;
int N,M,G,x,y,gr;
int d[50005];
int main()
{
    fscanf(f,"%d%d%d",&N,&M,&G);
    for(int i=1;i<=M;i++)
    {
        fscanf(f,"%d%d%d",&x,&y,&gr);
        Gr[x].pb(mp(y,gr));
        Gr[y].pb(mp(x,gr));
    }
    for(int i=2;i<=N;i++) d[i]=(1<<30);
    H.push(mp(0,1));
    while(!H.empty())
    {
        int nod,cost;
        cost=-H.top().dist;
        nod=H.top().n;
        H.pop();
        if(cost!=d[nod])
            continue;
        for(auto it:Gr[nod])
        {
            if(it.second<G)
            {
                if(d[it.first]>cost+1)
                {
                    d[it.first]=cost+1;
                    H.push(mp(-d[it.first],it.first));
                }
            }
            else
            {
                if(d[it.first]>cost)
                {
                    d[it.first]=cost;
                    H.push(mp(-d[it.first],it.first));
                }
            }
        }
    }
    fprintf(g,"%d",d[N]);
    fclose(f);
    fclose(g);
    return 0;
}
