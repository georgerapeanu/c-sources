#include <cstdio>
#include <vector>
#include <unordered_set>
#include <algorithm>
#define x first
#define pb push_back
#define y second
using namespace std;
FILE *f=fopen("trenul.in","r");
FILE *g=fopen("trenul.out","w");
pair<int,int> V[100005];
vector<int> rez[100005];
int N,M;
int ramas;
unordered_set<int> S;
int main()
{
    fscanf(f,"%d%d",&N,&M);
    for(int i=1;i<=M;i++)
    {
        fscanf(f,"%d",&V[i].x);
        V[i].y=i;
    }
    sort(V+1,V+1+M);
    int i=M;
    int loc=1;
    while(V[i].x==3)
    {
        rez[V[i].y].pb(loc++);
        rez[V[i].y].pb(loc++);
        rez[V[i].y].pb(loc++);
        i--;
    }
    if(loc%2==0)
    {
        ramas=loc;
        loc++;
    }
    while(V[i].x==2)
    {
        rez[V[i].y].pb(loc++);
        rez[V[i].y].pb(loc++);
        i--;
    }
    while(V[i].x==1)
    {
        if(ramas){rez[V[i].y].pb(ramas);ramas=0;i--;continue;}
        rez[V[i].y].pb(loc++);
        i--;
    }
    for(int i=1;i<=M;i++)
    {
        for(auto it:rez[i])
            fprintf(g,"%d ",it);
        fputc('\n',g);
    }
    fclose(f);
    fclose(g);
    return 0;
}
