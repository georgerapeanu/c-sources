#include <cstdio>
#include <cstring>
#include <map>
#include <algorithm>
using namespace std;
int N,M,Q;
long long AIB[2505][2505][3];
map<pair<pair<int,int>,pair<int,int> >,int > MA;
void u(int x,int y,int val,int semn)
{
    int i,j;
    i=x;
    j=y;
    for(x=i;x<=N;x+=(-x)&x)
        for(y=j;y<=M;y+=(-y)&y)
        {
            AIB[x][y][0]+=val*semn;
            AIB[x][y][1]+=1LL*val*val*semn;
            AIB[x][y][2]^=val;
        }
}
pair<pair<long long,long long>,long long> q(int x,int y)
{
    pair<pair<long long,long long>,long long> rez={{0,0},0};
    int i,j;
    i=x;
    j=y;
    for(x=i;x;x-=(-x)&x)
        for(y=j;y;y-=(-y)&y)
        {
            rez.first.first+=AIB[x][y][0];
            rez.first.second+=AIB[x][y][1];
            rez.second^=AIB[x][y][2];
        }
    return rez;
}
int t,x1,y1,x2,y2;
int main()
{
    scanf("%d %d %d",&N,&M,&Q);
    for(int i=1;i<=Q;i++)
    {
        scanf("%d %d %d %d %d",&t,&x1,&y1,&x2,&y2);
        if(t==1)
        {
            if(x1>x2)swap(x1,x2);
            if(y1>y2)swap(y1,y2);
            MA[{{x1,y1},{x2,y2}}]=i;
            u(x1,y1,i,1);
            u(x1,y2+1,i,-1);
            u(x2+1,y1,i,-1);
            u(x2+1,y2+1,i,1);
        }
        else if(t==2)
        {
            if(x1>x2)swap(x1,x2);
            if(y1>y2)swap(y1,y2);
            int i=MA[{{x1,y1},{x2,y2}}];
            MA[{{x1,y1},{x2,y2}}]=0;
            u(x1,y1,i,-1);
            u(x1,y2+1,i,1);
            u(x2+1,y1,i,1);
            u(x2+1,y2+1,i,-1);
        }
        else
        {
            printf("%s",(q(x1,y1)==q(x2,y2) ? "Yes\n":"No\n"));
        }
    }
    return 0;
}
