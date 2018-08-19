#include <iostream>
#include <vector>
using namespace std;
long long d1[5005][5005][2];
long long d2[2][5005][2];
long long l[5005];
vector<int> G[5005];
int N;
long long C[5005],D[5005];
long long a,b,t;
void dfs(int nod)
{
    l[nod]=1;
    for(int i=0;i<=N;i++)d2[0][i][0]=d2[0][i][1]=1LL<<56;
    d2[0][0][0]=0;
    d2[0][0][1]=0;
    int last=0;
    int sz=0,r=1;
    for(auto it:G[nod])
    {
        dfs(it);
    }
    for(auto it:G[nod])
    {
        for(int i=1;i<=N;i++)d2[r][i][0]=d2[r][i][1]=1LL<<56;
        l[nod]+=l[it];
        for(int i=0;i<=sz;i++)
            for(int j=0;j<=l[it];j++)
            {
                d2[r][i+j][0]=min(d2[r][i+j][0],d2[1-r][i][0]+d1[it][j][0]);
                d2[r][i+j][1]=min(d2[r][i+j][1],d2[1-r][i][1]+min(d1[it][j][0],d1[it][j][1]));
            }
        sz+=l[last=it];
        r^=1;
    }
    for(int i=1;i<=l[nod];i++){d1[nod][i][0]=min(d2[1-r][i][0],C[nod]+d2[1-r][i-1][0]);d1[nod][i][1]=C[nod]-D[nod]+min(d2[1-r][i-1][0],d2[1-r][i-1][1]);}
}
long long B;
long long rez=0;
int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    cin>>N>>B;
    for(int i=1;i<=N;i++)
    {
        cin>>a>>b;
        C[i]=a;D[i]=b;
        if(i>1)
        {
            cin>>t;
            G[t].push_back(i);
        }
    }
    dfs(1);
    while(rez<N&&(d1[1][rez+1][0]<=B||d1[1][rez+1][1]<=B))rez++;
    cout<<rez;
    return 0;
}
