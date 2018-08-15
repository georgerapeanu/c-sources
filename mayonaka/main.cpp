#include <cstdio>
#include <cstring>
#include <vector>
#include <cmath>
#include <map>
using namespace std;
FILE *f=fopen("mayonaka.in","r");
FILE *g=fopen("mayonaka.out","w");
int x,y,l,gr;
int N,M;
int rad;
int V[320][320];
int rez[100001];
struct q
{
    int l,gr;
};
vector<q> Ev[100001];
int main()
{
    fscanf(f,"%d %d",&N,&M);
    rad=sqrt(N);
    for(int i=1;i<=M;i++)
    {
        fscanf(f,"%d %d %d %d",&x,&y,&l,&gr);
        if(l>=rad)
        {
            for(int j=x;j<=y;j+=l)
                rez[j]+=gr;
        }
        else
        {
            Ev[x].push_back({l,gr});
            if(y-(y-x)%l+l<=N)
                Ev[y-(y-x)%l+l].push_back({l,-gr});
        }
    }
    for(int i=1;i<=N;i++)
    {
        memset(V[i%rad],0,sizeof(V[i%rad]));
        for(auto it:Ev[i])
            V[i%rad][it.l]+=it.gr;
        for(int j=1;j<=rad;j++)
        {
            if(i-j>0)
                V[i%rad][j]+=V[(i-j+rad)%rad][j];
            rez[i]+=V[i%rad][j];
        }
    }
    for(int i=1;i<=N;i++)
        fprintf(g,"%d ",rez[i]);
    fclose(f);
    fclose(g);
    return 0;
}
