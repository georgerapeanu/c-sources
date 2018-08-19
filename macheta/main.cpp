#include <algorithm>
#define nmax 2005
#include <cstdio>
using namespace std;
FILE *f=fopen("macheta.in","r");
FILE *g=fopen("macheta.out","w");
pair <pair<int,int>,pair<int,pair<int,int> > > V[105];
int N,i,x,y,Ly,Lx,H,h[nmax],nr,j;
bool ok;
int rez[105];
int main()
{
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d %d %d %d %d",&x,&y,&Lx,&Ly,&H);
        V[i]=make_pair(make_pair(y,H),make_pair(x,make_pair(x+Lx-1,i)));
    }
    sort(V+1,V+1+N);
    for(i=1;i<=N;i++)
    {
        ok=0;
        for(j=V[i].second.first;j<=V[i].second.second.first;j++)
        {
            if(h[j]<V[i].first.second)
            {
                ok=1;
                h[j]=V[i].first.second;
            }
        }
        if(ok)
            rez[++rez[0]]=V[i].second.second.second;
    }
    sort(rez+1,rez+1+rez[0]);
    for(i=1;i<=rez[0];i++)
        fprintf(g,"%d ",rez[i]);
    fclose(f);
    fclose(g);
    return 0;
}
