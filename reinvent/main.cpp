#include <cstdio>
#include <queue>
#include <vector>
#define inf 100000000
using namespace std;
FILE *f=fopen("reinvent.in","r");
FILE *g=fopen("reinvent.out","w");
int N,M,X,i,viz[100005],x,y,dist[100005],rez,n;
bool ok=1;
vector <int> V[100005];
queue <int> noduri;
int main()
{
    fscanf(f,"%d %d %d",&N,&M,&X);
    for(i=1;i<=M;i++)
    {
        fscanf(f,"%d %d",&x,&y);
        V[x].push_back(y);
        V[y].push_back(x);
    }
    for(i=1;i<=X;i++)
    {
        fscanf(f,"%d",&x);
        noduri.push(x);
        viz[x]=x;
    }
    while(ok)
    {
        x=noduri.front();
        noduri.pop();
        n=V[x].size();
        for(i=0;i<n;i++)
        {
            if(viz[V[x][i]]!=viz[x])
            {
                if(viz[V[x][i]]==0)
                {
                    viz[V[x][i]]=viz[x];
                    dist[V[x][i]]=dist[x]+1;
                    noduri.push(V[x][i]);
                }
                else
                {
                    ok=0;
                    rez=dist[x]+dist[V[x][i]]+1;
                }
            }
        }
    }
    fprintf(g,"%d",rez);
    fclose(f);
    fclose(g);
    return 0;
}
