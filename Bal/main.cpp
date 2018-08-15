#include <cstdio>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
FILE *f=fopen("bal.in","r");
FILE *g=fopen("bal.out","w");
vector<int> G[200005];
int gr[200005];
bool U[200005];
int ans[200005];
vector<pair<int,int> > ed;
int N,M;
const int LEN=10000;
char buff[LEN];
int ind=LEN-1;
queue<int> Q;
int i32()
{
    int rez=0;
    while(buff[ind]<'0'||buff[ind]>'9')
    {
        if(++ind>=LEN)
        {
            ind=0;
            fread(buff,1,LEN,f);
        }
    }
    while(buff[ind]>='0'&&buff[ind]<='9')
    {
        rez=rez*10+buff[ind]-'0';
        if(++ind>=LEN)
        {
            ind=0;
            fread(buff,1,LEN,f);
        }
    }
    return rez;
}
int main()
{
    N=i32();M=i32();
    for(int i=1;i<=M;i++)
    {
        int x,y;
        x=i32();
        y=i32();
        ed.push_back({x,y});
    }
    sort(ed.begin(),ed.end());
    G[ed[0].first].push_back(ed[0].second+N);M=1;
    G[ed[0].second+N].push_back(ed[0].first);
    gr[ed[0].first]=gr[ed[0].second+N]=1;
    for(int i=1;i<ed.size();i++)
    {
        if(ed[i]!=ed[i-1])
        {
            G[ed[i].first].push_back(ed[i].second+N);
            G[ed[i].second+N].push_back(ed[i].first);
            gr[ed[i].first]++;
            gr[ed[i].second+N]++;
            M++;
        }
    }
    //if(M>=2*N){fprintf(g,"NU");return 0;}
    for(int i=1;i<=N;i++)
    {
        if(!gr[i])
        {
            fprintf(g,"NU");return 0;
        }
        if(gr[i]==1)
        {
            Q.push(i);
        }
    }
    while(!Q.empty())
    {
        int nod=Q.front();Q.pop();
        for(auto it:G[nod])
        {
            if(!U[it])
            {
                U[it]=1;
                ans[nod]=it;
                for(auto it2:G[it])
                {
                    gr[it2]--;
                    if(gr[it2]==1)Q.push(it2);
                }
                break;
            }
        }
    }
    for(int i=1;i<=N;i++)
    {
        if(!ans[i]){fprintf(g,"NU");return 0;}
    }
    fprintf(g,"DA\n");
    for(int i=1;i<=N;i++)fprintf(g,"%d\n",ans[i]-N);
    fclose(f);
    fclose(g);
    return 0;
}
