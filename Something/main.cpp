#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;
FILE *f=fopen("something.in","r");
FILE *g=fopen("something.out","w");
int cul[100005];
int lvl[100005];
int st[100005];
int N,M;
vector<int> G[100005];
queue<int> Q;
void dfs(int nod,int nvl)
{
    lvl[nod]=nvl;
    st[++st[0]]=nod;
    for(auto it:G[nod])
    {
        if(!lvl[it])dfs(it,nvl+1);
        else if(lvl[it]<lvl[nod]-1)
        {
            int len=lvl[nod]-lvl[it]+1;
            for(int i=lvl[it];i<lvl[it]+len/3;i++){cul[st[i]]=1;Q.push(st[i]);}
            for(int i=lvl[it]+len/3;i<lvl[it]+2*len/3;i++){cul[st[i]]=2;Q.push(st[i]);}
            for(int i=lvl[it]+2*len/3;i<=lvl[nod];i++){cul[st[i]]=3;Q.push(st[i]);}
            while(!Q.empty())
            {
                int nod=Q.front();Q.pop();
                for(auto it:G[nod])
                {
                    if(!cul[it])
                    {
                        cul[it]=cul[nod];
                        Q.push(it);
                    }
                }
            }
            for(int i=1;i<=N;i++){fprintf(g,"%d ",cul[i]);}exit(0);
        }
    }
    st[0]--;
}
int main()
{
    fscanf(f,"%d%d",&N,&M);
    for(int i=1;i<=M;i++)
    {
        int x,y;
        fscanf(f,"%d %d",&x,&y);
        G[x].push_back(y);
        G[y].push_back(x);
    }
    dfs(1,1);
    fprintf(g,"-1");
    fclose(f);
    fclose(g);
    return 0;
}
