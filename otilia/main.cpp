#include <fstream>
#include <iostream>
#include <cstdlib>
#include <stack>
#include <vector>
using namespace std;
ifstream f("otilia.in");
ofstream g("otilia.out");
int dp[5000001];
int N,K,P,M;
int st[5000001];
int rez[30001];
struct data
{
    int pos,N,K;
};
vector<data> Q[11];
void builddp(int p)
{
    st[0]=1;st[1]=0;
    for(int i=1;i<=5000000;i++)
    {
        while(st[0]&&dp[st[st[0]]]-(i-st[st[0]])*p<=0)st[0]--;
        dp[i]=(st[0] ? (i-st[st[0]]):1<<30);st[++st[0]]=i;
    }
}
int main()
{
    f>>M;
    for(int i=1;i<=M;i++)
    {
        f>>N>>K>>P;
        Q[P].push_back({i,N,K});
    }
    for(int i=1;i<=10;i++)
    {
        builddp(i);
        for(auto it:Q[i])
            rez[it.pos]=(dp[it.N]<=it.K);
    }
    for(int i=1;i<=M;i++)g<<rez[i]<<"\n";
    f.close();
    g.close();
    return 0;
}
