#include <fstream>
#include <algorithm>
#define MOD 30103
#define MAXV 700
#define x first
#define y second
#define pb push_back
#define mp make_pair
using namespace std;
ifstream f("evantai.in");
ofstream g("evantai.out");
int AIB[MAXV+5][MAXV+5];
int dp[MAXV+5][MAXV+5];
int N;
int A[705];
void update(int x,int y,int val)
{
    for(int i=x;i<=N;i+=(i&(-i)))
        for(int j=y;j<=N;j+=(j&(-j)))
            {AIB[i][j]+=val;if(AIB[i][j]>=MOD) AIB[i][j]-=MOD;}
}
int query(int x,int y)
{
    int nr=0;
    for(int i=x;i;i-=(i&(-i)))
        for(int j=y;j;j-=(j&(-j)))
            {nr+=AIB[i][j];if(nr>=MOD)nr-=MOD;}
    return nr;
}
pair<int,int> V[700*700+6];
bool cmp(pair<int,int> a,pair<int,int> b)
{
    return A[a.x]+A[a.y]<A[b.x]+A[b.y];
}
int suma(pair<int,int> a)
{
    return A[a.x]+A[a.y];
}
char buffer[10000];
int ind=10000;
int i32()
{
    int rez=0;
    while(buffer[ind]<'0'||buffer[ind]>'9')
        if(++ind>=10000)
            {f.read(buffer,10000);ind=0;}
    while(buffer[ind]>='0'&&buffer[ind]<='9')
    {
        rez=rez*10+buffer[ind]-'0';
        if(++ind>=10000)
            {f.read(buffer,10000);ind=0;}
    }
    return rez;
}
int main()
{
    N=i32();
    for(int i=1;i<=N;i++)
        A[i]=i32();
    int dim=0;
    for(int i=1;i<=N;i++) for(int j=i+1;j<=N;j++) V[++dim]=mp(i,j);
    sort(V+1,V+1+dim,cmp);
    int j=1;
    for(int i=1;i<=dim;i++)
    {
        if(suma(V[i])!=suma(V[j]))
        {
            for(int k=j;k<i;k++)update(V[k].x,V[k].y,dp[V[k].x][V[k].y]);
            j=i;
        }
        dp[V[i].x][V[i].y]=1+query(V[i].y-1,V[i].y-1)-query(V[i].x,V[i].y-1);
        if(dp[V[i].x][V[i].y]>=MOD)dp[V[i].x][V[i].y]-=MOD;
        while(dp[V[i].x][V[i].y]<0)dp[V[i].x][V[i].y]+=MOD;
    }
    for(int k=j;k<=dim;k++)update(V[k].first,V[k].second,dp[V[k].first][V[k].second]);
    g<<query(N,N);
    f.close();
    g.close();
    return 0;
}
