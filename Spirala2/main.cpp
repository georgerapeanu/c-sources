#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
using namespace std;
FILE *f=fopen("spirala2.in","r");
FILE *g=fopen("spirala2.out","w");
int per[50*50+5];
int nxt[50*50+5];
int dp[50*50+5];
int X,Y,x,y;
int N,K,ind=1;
int dx[]={-1,0,1,0};
int dy[]={0,1,0,-1};
bool viz[55][55];
int matval(int x,int y)
{
    if(x%2==0)
    {
        return (x-1)*N+(N-y+1);
    }
    else
    {
        return (x-1)*N+y;
    }
}
void dfs(int nod,int &val)
{
    per[nod]=-1;val++;
    if(per[nxt[nod]]==0)
        dfs(nxt[nod],val);
    per[nod]=val;
}
int gcd(int a,int b)
{
    if(!b)return a;
    return gcd(b,a%b);
}
int lcm(int a,int b)
{
    return 1LL*a*b/gcd(a,b);
}
int main()
{
    X=Y=x=y=1;
    fscanf(f,"%d %d",&N,&K);
    for(int i=0;i<=N+1;i++)
        viz[i][0]=viz[i][N+1]=viz[0][i]=viz[N+1][i]=1;
    for(int i=1;i<=N*N;i++)
    {
        nxt[matval(X,Y)]=matval(x,y);
        Y=Y+(X%2==0 ? -1:1);
        if(Y==0){Y=1;X++;}
        else if(Y==N+1){Y=N;X++;}
        viz[x][y]=1;
        x+=dx[ind];
        y+=dy[ind];
        if(viz[x][y])
        {
            x-=dx[ind];
            y-=dy[ind];
            ind++;ind%=4;
            x+=dx[ind];
            y+=dy[ind];
        }
    }
    for(int i=1;i<=N*N;i++)
        if(!per[i])
        {
            int val=0;
            dfs(i,val);
        }
    for(int i=1;i<=N*N;i++)dp[i]=(1<<30);
    for(int i=1;i<=N*N;i++)
    {
        for(int j=min(K,i);j>1;j--)
        {
            dp[j]=min(dp[j],lcm(dp[j-1],per[i]));
        }
        if(dp[1]>per[i])
            dp[1]=per[i];
    }
    fprintf(g,"%d",dp[K]);
    fclose(f);
    fclose(g);
    return 0;
}
