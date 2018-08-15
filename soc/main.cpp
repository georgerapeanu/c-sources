#include <cstdio>
#include <cstring>
#include <queue>
#include <map>
using namespace std;
FILE *f=fopen("soc.in","r");
FILE *g=fopen("soc.out","w");
int N,M;
map<pair<int,int>,int> E;
int V[300];
void bfs(int nod,bool *ceva,bool *s,int sw)
{
    queue<int> Q;
    Q.push(nod);
    ceva[nod]=1;
    while(!Q.empty())
    {
        nod=Q.front();Q.pop();
        for(int i=1;i<=N;i++)
        {
            if(s[i]==1&&ceva[i]==0&&E[{nod,i}]!=sw)
            {
                ceva[i]=1;
                Q.push(i);
            }
        }
    }
}
pair<int,vector<int> > solve(bool *s,bool sw,bool op)
{
    vector<int> v;v.clear();
    int tmp=0;
    for(int i=1;i<=N;i++)if(s[i])tmp++;
    if(tmp==1)for(int i=1;i<=N;i++)if(s[i])return {V[i],{i}};
    bool ceva[300];
    bool viz[300];
    int nr=0,rez=0;
    memset(viz,0,sizeof(viz));
    for(int i=1;i<=N;i++)
    {
        if(s[i]&&!viz[i])
        {
            memset(ceva,0,sizeof(ceva));
            bfs(i,ceva,s,sw);
            for(int i=1;i<=N;i++)viz[i]|=ceva[i];
            nr++;
        }
    }
    if(nr==1)
        return solve(s,sw^1,op^1);
    memset(viz,0,sizeof(viz));
    for(int i=1;i<=N;i++)
    {
        if(s[i]&&!viz[i])
        {
            memset(ceva,0,sizeof(ceva));            bfs(i,ceva,s,sw);
            for(int i=1;i<=N;i++)viz[i]|=ceva[i];
            if(op)
            {
                pair<int,vector<int> > t=solve(ceva,sw,op);
                rez+=t.first;
                for(auto it:t.second)v.push_back(it);
            }
            else
            {
                pair<int,vector<int> > t=solve(ceva,sw,op);
                if(rez<t.first)
                {
                    rez=t.first;
                    v.clear();
                    for(auto it:t.second)v.push_back(it);
                }
            }
        }
    }
    return {rez,v};
}
bool s[300];
int main()
{
    fscanf(f,"%d %d",&N,&M);
    for(int i=1;i<=N;i++)
    {
        s[i]=1;
        fscanf(f,"%d",&V[i]);
    }
    for(int i=1;i<=M;i++)
    {
        int x,y;
        fscanf(f,"%d %d",&x,&y);
        E[{x,y}]=1;
        E[{y,x}]=1;
    }
    pair<int,vector<int> > rez=solve(s,0,0);
    fprintf(g,"%d\n%d\n",rez.first,rez.second.size());
    for(auto it:rez.second)fprintf(g,"%d ",it);
    fclose(f);
    fclose(g);
    return 0;
}
