#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
FILE *f=fopen("drumuri5.in","r");
FILE *g=fopen("drumuri5.out","w");
vector<vector<int> > comp;
vector<int> G[150005];
vector<int> gr[150005];
vector<int> gt[150005];
pair<int,int> edges[300005];
bool instiva[150005];
int stiva[150005];
int low[150005];
int id[150005];
int which[150005];
int ind[150005];
int lastid;
int N,M;
int in[150005];
int d[150005][2];
vector<int> order;
void dfs(int nod)
{
    low[nod]=id[nod]=++lastid;
    stiva[++stiva[0]]=nod;
    instiva[nod]=1;
    for(auto it:G[nod])
    {
        if(!id[it])dfs(it);
        if(instiva[it])low[nod]=min(low[nod],low[it]);
    }
    if(low[nod]==id[nod])
    {
        vector<int> V;
        while(stiva[stiva[0]]!=nod)
        {
            which[stiva[stiva[0]]]=comp.size()+1;
            instiva[stiva[stiva[0]]]=0;
            V.push_back(stiva[stiva[0]]);
            stiva[0]--;
        }
        which[nod]=comp.size()+1;
        instiva[nod]=0;
        V.push_back(nod);
        stiva[0]--;
        comp.push_back(V);
    }
}
void ctc()
{
    for(int i=1;i<=N;i++)if(!id[i])dfs(i);
    for(int i=1;i<=M;i++)
    {
        if(which[edges[i].first]!=which[edges[i].second])
        {
            gr[which[edges[i].first]].push_back(which[edges[i].second]);
            gt[which[edges[i].second]].push_back(which[edges[i].first]);
            in[which[edges[i].second]]++;
        }
    }
    N=comp.size();
}
void sortaret()
{
    queue<int> Q;
    for(int i=1;i<=N;i++)if(!in[i])Q.push(i);
    while(!Q.empty())
    {
        int nod=Q.front();Q.pop();
        order.push_back(nod);
        for(auto it:gr[nod])
        {
            in[it]--;
            if(!in[it])Q.push(it);
        }
    }
}
void compute(vector<int> v,vector<int> gr[150005],bool tmp)
{
    for(int i=0;i<v.size();i++)
        ind[v[i]]=i;
    for(int i=0;i<v.size();i++)
    {
        d[v[i]][tmp]++;
        int where=-1;
        for(auto it:gr[v[i]])
        {
            if(where==-1||ind[it]<ind[where])where=it;
        }
        if(where!=-1)
        {
            d[where][tmp]+=d[v[i]][tmp];
        }
    }
}
vector<int> res;
int main()
{
    fscanf(f,"%d %d",&N,&M);
    for(int i=1;i<=M;i++)
    {
        int x,y;
        fscanf(f,"%d %d",&x,&y);
        G[x].push_back(y);
        edges[i]={x,y};
    }
    ctc();
    sortaret();
    compute(order,gr,0);
    reverse(order.begin(),order.end());
    compute(order,gt,1);
    for(int i=1;i<=N;i++)
    {
        if(d[i][0]+d[i][1]==N+1)
        {
            for(auto it:comp[i-1])res.push_back(it);
        }
    }
    fprintf(g,"%d\n",res.size());sort(res.begin(),res.end());
    for(auto it:res)fprintf(g,"%d ",it);
    fclose(f);
    fclose(g);
    return 0;
}
