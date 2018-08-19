#include <cstdio>
#include <algorithm>
#define LEN 30000192
#define inf (1LL<<60)
using namespace std;
FILE *f=fopen("ksecv.in","r");
FILE *g=fopen("ksecv.out","w");
int ind=LEN-1;
char buff[LEN];
int i32()
{
    int nr=0;
    while(buff[ind]<'0'||buff[ind]>'9')
        if(++ind>=LEN){
            fread(buff,1,LEN,f);
            ind=0;
        }
    while(buff[ind]>='0'&&buff[ind]<='9')
    {
        nr=nr*10+buff[ind]-'0';
        if(++ind>=LEN){
            fread(buff,1,LEN,f);
            ind=0;
        }
    }
    return nr;
}
int N,K;
long long dp[2][100005];
int len;
int st[100005];
long long sd[100005];
int V[100005];
int main()
{
    N=i32();K=i32();
    for(int i=1;i<=N;i++){V[i]=i32();dp[1][i]=max(dp[1][i-1],1LL*V[i]);}
    dp[1][0]=inf;
    V[0]=inf;
    int l=1,pl=0;
    for(int i=2;i<=K;i++)
    {
        pl=l;
        l=1-l;
        len=0;
        st[++len]=i-1;
        sd[len]=dp[pl][i-1];
        dp[l][i-1]=dp[l][i-2]=inf;
        for(int j=i;j<=N;j++)
        {
            long long tmp=inf;
            while(len&&V[j]>V[st[len]]){tmp=min(sd[len],tmp);len--;}
            dp[l][j]=tmp+V[j];
            if(len)dp[l][j]=min(dp[l][st[len]],min(dp[l][j],dp[pl][st[len]]+V[j]));
            st[++len]=j;
            sd[len]=min(dp[pl][j],tmp);
        }
    }
    fprintf(g,"%lld",dp[l][N]);
    fclose(f);
    fclose(g);
    return 0;
}
