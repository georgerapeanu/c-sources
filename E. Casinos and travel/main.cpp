#include <cstdio>
#include <vector>
#define MOD 1000000007
using namespace std;
int N;
vector<int> G[100005];
int dp[100005][2];
void dfs1(int nod,int tata)
{

}
int main()
{
    d2[0][0]=d2[0][1]=1;
    scanf("%d",&N);
    for(int i=2;i<=N;i++)
    {
        int x,y;
        scanf("%d %d",&x,&y);
        G[x].push_back(y);
        G[y].push_back(x);
    }
    dfs1(1,0);
    dfs2(1,0);
    int rez=0;
    for(int i=1;i<=N;i++)
    {
        rez+=d2[i][0];
        if(rez>=MOD)rez-=MOD;
    }
    printf("%d",rez);
    return 0;
}
