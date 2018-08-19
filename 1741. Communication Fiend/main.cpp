#include <cstdio>
#include <algorithm>
#define inf (1LL<<62)-1
using namespace std;
long long N,M,DP[10005][2];
char C[60];
typedef struct {long long st,dr,cost,tip;} program;
program V[10005];
bool cmp(program a,program b)
{
    return a.dr<b.dr;
}
int main()
{
    scanf("%lld %lld\n",&N,&M);
    for(long long i=1;i<=M;i++)
    {
        scanf("%lld %lld %lld %s",&V[i].st,&V[i].dr,&V[i].cost,C);
        if(C[0]=='P')
            V[i].tip=0;
        else if(C[0]=='C')
            V[i].tip=1;
        else
            V[i].tip=2;
    }
    for(long long i=1;i<=N;i++)
        DP[i][0]=DP[i][1]=inf;
    sort(V+1,V+1+M,cmp);
    DP[1][1]=0;
    for(long long i=1;i<=M;i++)
    {
        if(V[i].tip==0)
        {
            DP[V[i].dr][0]=min(DP[V[i].dr][0],DP[V[i].st][0]+V[i].cost);
            DP[V[i].dr][0]=min(DP[V[i].dr][0],DP[V[i].st][1]+V[i].cost);
        }
        else if(V[i].tip==1)
        {
            DP[V[i].dr][0]=min(DP[V[i].dr][0],DP[V[i].st][0]+V[i].cost);
            DP[V[i].dr][0]=min(DP[V[i].dr][0],DP[V[i].st][1]+V[i].cost);
            DP[V[i].dr][1]=min(DP[V[i].dr][1],DP[V[i].st][1]+V[i].cost);
        }
        else
        {
            DP[V[i].dr][1]=min(DP[V[i].dr][1],DP[V[i].st][1]+V[i].cost);
        }
    }
    if(min(DP[N][0],DP[N][1])==inf)
        printf("Offline");
    else
    {
        printf("Online\n");
        printf("%lld",min(DP[N][0],DP[N][1]));
    }
    return 0;
}
