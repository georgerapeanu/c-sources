#include <cstdio>
#include <iostream>
#include <algorithm>
using namespace std;
FILE *f=fopen("harrypotter.in","r");
FILE *g=fopen("harrypotter.out","w");
int V[2405];
int dp[2405][2405];
int pos[2405][5];
int N;
int rez=0;
int nxt[2405];
int ant[2405];
bool in(int st,int dr,int pos)
{
    if(st<=dr)return (st<pos&&pos<dr);
    else      return (st<pos||pos<dr);
}
int solve()
{
    N=V[0];
    for(int i=1;i<=N;i++)dp[i][i]=0;
    for(int i=1;i<=N;i++)dp[i][i+1]=(V[i]==V[nxt[i]]);
    for(int l=2;l<N;l++)
    {
        for(int i=1;i<=N;i++)
        {
            int j=(i+l-1)%N+1;
            dp[i][j]=max((V[i]==V[j])+dp[nxt[i]][ant[j]],max(dp[nxt[i]][j],dp[i][ant[j]]));
            for(int k=1;k<=4;k++)
            {
                if(in(i,j,pos[V[i]][k]))dp[i][j]=max(dp[i][j],dp[i][pos[V[i]][k]]+dp[nxt[pos[V[i]][k]]][j]);
                if(in(i,j,pos[V[j]][k]))dp[i][j]=max(dp[i][j],dp[i][ant[pos[V[j]][k]]]+dp[pos[V[j]][k]][j]);
            }
        }
    }
    int rez=0;
    for(int i=1;i<=N;i++)rez=max(rez,dp[i][ant[i]]);
    return rez;
}
int main()
{
    fscanf(f,"%d",&N);
    for(int i=1;i<5;i++)for(int j=1;j<=N;j++){fscanf(f,"%d",&V[++V[0]]);pos[V[V[0]]][i]=V[0];}
    for(int i=1;i<=4*N;i++){nxt[i]=i+1;ant[i]=i-1;}
    nxt[4*N]=1;
    ant[1]=4*N;
    rez=solve();
    fprintf(g,"%d",rez);
    fclose(f);
    fclose(g);
    return 0;
}
