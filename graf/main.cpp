#include <queue>
#include <cstdio>
#include <vector>
#include <bitset>
#include <set>
using namespace std;
FILE *f=fopen("graf.in","r");
FILE *g=fopen("graf.out","w");
int N,M,X,Y,a,b,i;
queue <int> Q;
int val[7505];
vector <int> V[7505];
set <int> S;
vector<int> dist[7505];
int VX[7505];
int VY[7505];
int main()
{
    fscanf(f,"%d %d %d %d",&N,&M,&X,&Y);
    for(i=1;i<=M;i++)
    {
        fscanf(f,"%d %d",&a,&b);
        V[a].push_back(b);
        V[b].push_back(a);
    }
    Q.push(X);
    VX[X]=1;
    while(!Q.empty())
    {
        a=Q.front();
        Q.pop();
        for(auto it:V[a])
        {
            if(!VX[it])
            {VX[it]=VX[a]+1;Q.push(it);}
        }
    }
    Q.push(Y);
    VY[Y]=1;
    while(!Q.empty())
    {
        a=Q.front();
        Q.pop();
        for(auto it:V[a])
        {
            if(!VY[it])
            {VY[it]=VY[a]+1;Q.push(it);}
        }
    }
    for(i=1;i<=N;i++)
    {
        if(VX[i]+VY[i]==VX[Y]+1)
        {
            dist[VX[i]].push_back(i);
        }
    }
    for(i=1;i<=N;i++)
    {
        if(dist[i].size()==1)
            S.insert(dist[i][0]);
    }
    fprintf(g,"%d\n",S.size());
    for(auto it:S)
        fprintf(g,"%d ",it);
    fclose(f);
    fclose(g);
    return 0;
}
