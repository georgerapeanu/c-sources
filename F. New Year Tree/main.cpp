#include <cstdio>
#include <algorithm>
#define MAXB 20
using namespace std;
int T[MAXB][2*500006];
int lvl[2*500006];
int Q;
int v1=2,v2=3;
int N;
int len=2;
int dist(int u,int v)
{
    int x=u,y=v;
    if(lvl[x]>lvl[y])swap(x,y);
    for(int lg=MAXB-1;lg>=0;lg--)
    {
        if(lvl[y]-(1<<lg)>=lvl[x])
        {
            y=T[lg][y];
        }
    }
    for(int lg=MAXB-1;lg>=0;lg--)
    {
        if(T[lg][x]!=T[lg][y])
        {
            x=T[lg][x];
            y=T[lg][y];
        }
    }
    if(x!=y)
    {
        x=y=T[0][x];
    }
    return lvl[u]+lvl[v]-2*lvl[x];
}
int main()
{
    T[0][2]=T[0][3]=T[0][4]=1;
    lvl[1]=1;
    lvl[2]=lvl[3]=lvl[4]=2;
    scanf("%d",&Q);
    N=4;
    while(Q--)
    {
        int x;
        scanf("%d",&x);
        int tmp1,tmp2,ve1=v1,ve2=v2;
        tmp1=dist(v1,x);
        tmp2=dist(v2,x);
        //cout<<tmp1<<" "<<tmp2<<"\n";
        if(tmp1<tmp2)
        {
            tmp1=tmp2;
            ve1=ve2;
        }
        if(len<tmp1+1)
        {
            len=tmp1+1;
            v1=ve1;
            v2=N+1;
        }
        T[0][N+1]=T[0][N+2]=x;
        for(int i=1;i<MAXB;i++)T[i][N+1]=T[i-1][T[i-1][N+1]];
        for(int i=1;i<MAXB;i++)T[i][N+2]=T[i-1][T[i-1][N+2]];
        lvl[N+1]=lvl[N+2]=lvl[x]+1;
        N+=2;
        printf("%d\n",len);
    }
    return 0;
}
