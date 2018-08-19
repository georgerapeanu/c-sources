#include <cstdio>
#include <vector>
#include <bitset>
#include <cstring>
#define NMAX 100005
using namespace std;
FILE *f=fopen("pang.in","r");
FILE *g=fopen("pang.out","w");
int dp[NMAX];
int ant[NMAX];
int N,M,K;
int T,a,b;
bitset<NMAX> relic;
vector<int> G[NMAX];
bool ok;
int st;
int getdp(int nod)
{
    if(dp[nod]<0)
    {
        dp[nod]=relic[nod];
        for(auto it:G[nod])
            if(dp[nod]<relic[nod]+getdp(it))
                dp[nod]=relic[nod]+getdp(it),ant[nod]=it;
    }
    return dp[nod];
}
void printans(int nod)
{
    if(!nod)
    {
        fputc('\n',g);return ;
    }
    if(relic[nod])
        fprintf(g,"%d ",nod);
    printans(ant[nod]);
}
int main()
{
    fscanf(f,"%d",&T);
    while(T)
    {
        relic.reset();
        for(int i=1;i<=N;i++) G[i].clear();
        fscanf(f,"%d%d%d",&N,&M,&K);
        fill_n(dp+1,N,-1);
        memset(ant,0,sizeof(ant));
        for(int i=1;i<=M;i++)
        {
            fscanf(f,"%d%d",&a,&b);
            G[a].push_back(b);
        }
        for(int i=1;i<=K;i++)
        {
            fscanf(f,"%d",&a);
            relic[a]=1;
        }
        bool ok=0;
        for(int i=1;i<=N;i++)
        {
            if(getdp(i)==K)
            {
                ok=1;
                fputs("Da\n",g);
                printans(i);
                break;
            }
        }
        if(!ok)
            fputs("Nu\n",g);
        T--;
    }
    fclose(f);
    fclose(g);
    return 0;
}
