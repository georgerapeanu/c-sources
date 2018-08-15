#include <cstdio>
#include <algorithm>
#include <cmath>
#define MOD 666013
using namespace std;
FILE *f=fopen("emax.in","r");
FILE *g=fopen("emax.out","w");
int V[100005];
int N;
double dp[100005];
int best[100005];
int main()
{
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d",&V[i]);
        if(V[i]<0)V[i]*=-1;
    }
    int k=0;
    for(int i=1;i<=N;i++)
        if(V[i])
            V[++k]=V[i];
    N=k;
    for(int i=1;i<=N;i++)
    {
        int val=V[i];
        for(int j=i-1;j>=0&&j>=i-3;j--)
        {
            if(dp[i]<dp[j]+log(val))
            {
                dp[i]=dp[j]+log(val);
                best[i]=j;
            }
            val+=V[j];
        }
    }
    int ind=N;
    int rez=1;
    while(ind)
    {
        int sum=0;
        for(int i=ind;i>best[ind];i--)
            sum+=V[i];
        rez=(1LL*rez*sum)%MOD;
        ind=best[ind];
    }
    fprintf(g,"%d",rez);
    fclose(f);
    fclose(g);
    return 0;
}
