#include <cstdio>
#include <queue>
#include <vector>
#define nmax 15005
using namespace std;
FILE *f=fopen("easygraph.in","r");
FILE *g=fopen("easygraph.out","w");
queue <int> Q;
vector <int> V[nmax],rez,G[nmax];
int in[nmax],noduri[nmax];
long long dp[nmax];
int x,y,N,M,i,T;
long long R;
const long long inf=(1LL<<60);
int main()
{
    fscanf(f,"%d",&T);
    while(T--)
    {
         R=-inf;
        fscanf(f,"%d %d",&N,&M);
        for(i=1;i<=N;i++)
        {
            fscanf(f,"%d",&noduri[i]);
        }
        for(i=1;i<=M;i++)
        {
            fscanf(f,"%d %d",&x,&y);
            in[y]++;
            V[x].push_back(y);
            G[y].push_back(x);
        }
        for(i=1;i<=N;i++)
        {
            if(!in[i])
                Q.push(i);
        }
        while(!Q.empty())
        {
            rez.push_back(Q.front());
            for(auto it:V[Q.front()])
            {
                in[it]--;
                if(!in[it])
                    Q.push(it);
            }
            Q.pop();
        }
        for(auto index:rez)
        {
           dp[index]=noduri[index];
           for(auto it:G[index])
           {
               dp[index]=max(dp[index],dp[it]+noduri[index]);
           }
           R=max(R,dp[index]);
        }
        for(i=1;i<=N;i++)
        {V[i].clear();dp[i]=0;G[i].clear();}
        rez.clear();
        fprintf(g,"%lld\n",R);
    }
    fclose(f);
    fclose(g);
    return 0;
}
