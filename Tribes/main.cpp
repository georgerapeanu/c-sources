#include <cstdio>
#include <unordered_set>
#include <vector>
#include <queue>
#define rad 50
using namespace std;
FILE *f=fopen("tribes.in","r");
FILE *g=fopen("tribes.out","w");
unordered_set<int> S[100005];
unordered_set<long long> E;
vector<int> G[100005];
int viz[100005];
int T[100005];
int N,K,M;
queue<int> Q;
const int LEN=10000;
char buff[LEN];
int ind=LEN-1;
int i32()
{
    int nr=0;
    while(buff[ind]<'0'||buff[ind]>'9'){
        if(++ind>=LEN){
            fread(buff,1,LEN,f);
            ind=0;
        }
    }
    while(buff[ind]>='0'&&buff[ind]<='9'){
        nr=nr*10+buff[ind]-'0';
        if(++ind>=LEN){
            fread(buff,1,LEN,f);
            ind=0;
        }
    }
    return nr;
}
int main()
{
    N=i32();M=i32();K=i32();
    for(int i=1;i<=N;i++)T[i]=i32();
    for(int i=1;i<=M;i++)
    {
        int x,y;
        x=i32();y=i32();
        G[x].push_back(y);
        G[y].push_back(x);
        E.insert(1LL*x*(N+1)+y);
        E.insert(1LL*y*(N+1)+x);
    }
    for(int i=1;i<=N;i++)
    {
        S[T[i]].insert(i);
        for(auto it:G[i])
            S[T[i]].insert(it);
    }
    for(int i=1;i<=K;i++)
    {
        int nr=0;
        if(S[i].size()<=rad)
        {
            for(auto it:S[i])
            {
                if(viz[it]!=i)
                {
                    nr++;
                    Q.push(it);
                    viz[it]=i;
                    while(!Q.empty())
                    {
                        int nod=Q.front();Q.pop();
                        for(auto it:S[i])
                        {
                            if(E.find(1LL*nod*(N+1)+it)!=E.end()&&viz[it]!=i)
                            {
                                viz[it]=i;
                                Q.push(it);
                            }
                        }
                    }
                }
            }
        }
        else
        {
            for(auto it:S[i])
            {
               if(viz[it]!=i)
               {
                    nr++;
                Q.push(it);
                viz[it]=i;
                while(!Q.empty())
                {
                    int nod=Q.front();Q.pop();
                    for(auto it:G[nod])
                    {
                        if(S[i].find(it)!=S[i].end()&&viz[it]!=i)
                        {
                            viz[it]=i;
                            Q.push(it);
                        }
                    }
                }
               }
            }
        }
        fprintf(g,"%d\n",nr);
    }
    fclose(f);
    fclose(g);
    return 0;
}
