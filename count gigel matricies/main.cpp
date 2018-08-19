#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
using namespace std;
priority_queue<pair<int,int> > H;
int N,M;
int D[2005][2005];
int R[2005][2005];
int U[2005][2005];
int L[2005][2005];
char C[2005][2005];
long long rez;
int AIB[2005];
void u(int pos,int val)
{
    for(;pos<=N;pos+=(-pos)&pos)AIB[pos]+=val;
}
int q(int pos)
{
    int rez=0;
    for(;pos;pos-=(-pos)&pos)rez+=AIB[pos];
    return rez;
}
long long procsegm(int stx,int sty,int drx,int dry)
{
    while(!H.empty())H.pop();
    long long rez=0;
    for(int i=stx;i<=drx;i++)
    {
        while(!H.empty()&&i>-H.top().first){u(H.top().second,-1);H.pop();}
        H.push({-(i+min(D[i][sty+i-stx],R[i][sty+i-stx])),i});
        u(i,1);
        rez+=q(i)-q(max(i-min(L[i][sty+i-stx],U[i][sty+i-stx]),stx-1));
    }
    return rez;
}
int main() {
    scanf("%d %d\n",&N,&M);
    for(int i=1;i<=N;i++)fgets(C[i]+1,2005,stdin);
    for(int i=N;i;i--)
    {
        for(int j=M;j;j--)
        {
            if(C[i][j]=='1')
            {
                R[i][j]=1+R[i][j+1];
                D[i][j]=1+D[i+1][j];
            }
        }
    }
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=M;j++)
        {
            if(C[i][j]=='1')
            {
                U[i][j]=1+U[i-1][j];
                L[i][j]=1+L[i][j-1];
            }
        }
    }
    for(int x=N;x;x--)
    {
        int stx=x,sty=1;
        memset(AIB,0,sizeof(AIB));
        for(int i=x,j=1;i<=N&&j<=M;i++,j++)
        {
            if(C[i][j]=='0')
            {
                if(stx!=i)rez+=procsegm(stx,sty,i-1,j-1);
                stx=i+1;sty=j+1;
            }
            else if(i==N||j==M)
            {
                rez+=procsegm(stx,sty,i,j);
            }
        }
    }
    for(int y=2;y<=M;y++)
    {
        memset(AIB,0,sizeof(AIB));
        int stx=1,sty=y;
        for(int i=1,j=y;i<=N&&j<=M;i++,j++)
        {
            if(C[i][j]=='0')
            {
                if(stx!=i)rez+=procsegm(stx,sty,i-1,j-1);
                stx=i+1;sty=j+1;
            }
            else if(i==N||j==M)
            {
                rez+=procsegm(stx,sty,i,j);
            }
        }
    }
    printf("%lld",rez);
    return 0;
}
