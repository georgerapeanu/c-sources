#include <cstdio>
#include <cstring>
#include <stack>
#include <bitset>
#define inf 1<<30
using namespace std;
FILE *f=fopen("adn.in","r");
FILE *g=fopen("adn.out","w");
int cst[20][20];
char rez[600005];
int ind;
int N;
char C[20][30005];
int dp[1<<18][19];
int ant[1<<18][19];
int L[20];
int F[30005];
bool inc;
int K;
int kmp(int a,int b)
{
    inc=0;
    F[1]=0;
    for(int i=2;i<=L[b];i++)
    {
        int k=F[i-1];
        while(k&&C[b][k+1]!=C[b][i])k=F[k];
        if(C[b][k+1]==C[b][i])k++;
        F[i]=k;
    }
    int j=0;
    for(int i=1;i<=L[a];i++)
    {
        while(j&&C[b][j+1]!=C[a][i])j=F[j];
        if(C[b][j+1]==C[a][i])j++;
        if(j==L[b])
        {
            inc=1;
            return 0;
        }
    }
    return j;
}
stack<int> S;
void solve()
{
    for(int i=1;i<=N;i++)
        for(int j=1;j<=N;j++)
        {
            if(i==j)continue;
            cst[i][j]=L[j]-kmp(i,j);
            if(inc&&(K&(1<<(i-1)))&&(K&(1<<(j-1))))K^=(1<<(j-1));
        }
    for(int i=0;i<=N;i++)
    {
        cst[i][0]=dp[0][i]=inf;
        cst[0][i]=L[i];
    }
    dp[0][0]=0;
    for(int i=1;i<=K;i++)
    {
        dp[i][0]=inf;
        for(int j=1;j<=N;j++)
        {
            dp[i][j]=inf;
            if(i&(1<<(j-1)))
            {
                for(int k=0;k<=N;k++)
                {
                    if((k==0||(i&(1<<(k-1))))&&k!=j&&dp[i][j]>dp[i^(1<<(j-1))][k]+cst[k][j])
                    {
                        dp[i][j]=dp[i^(1<<(j-1))][k]+cst[k][j];
                        ant[i][j]=k;
                    }
                }
            }
        }
    }
    int nod=1,pre=0,ind=0;
    for(int i=1;i<=N;i++)
        if(dp[K][i]<dp[K][nod])
            nod=i;
    while(K)
    {
        S.push(nod);
        K^=(1<<(nod-1));
        nod=ant[K^(1<<(nod-1))][nod];
    }
    while(!S.empty())
    {
        for(int i=L[S.top()]-cst[pre][S.top()]+1;i<=L[S.top()];i++)
            rez[ind++]=C[S.top()][i];
        pre=S.top();
        S.pop();
    }
}
int main()
{
    fscanf(f,"%d\n",&N);
    K=(1<<N)-1;
    for(int i=1;i<=N;i++){fgets(C[i]+1,30005,f);L[i]=strlen(C[i]+1);L[i]-=(C[i][L[i]]=='\n');}
    solve();
    fputs(rez,g);
    fclose(f);
    fclose(g);
    return 0;
}
