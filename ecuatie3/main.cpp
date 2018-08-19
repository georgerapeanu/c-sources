#include <cstdio>
#include <algorithm>
#define BASE 1000000
#define LEN 200000
#define dim rez[0]
using namespace std;
FILE *f=fopen("ecuatie3.in","r");
FILE *g=fopen("ecuatie3.out","w");
long long dp[70][12];
int N;
long long T;
long long rez[LEN];
void mul(long long sc)
{
    long long t=0;
    for(int i=1;i<=dim||t;i++)
    {
        dim=max(1LL*i,dim);
        rez[i]=(rez[i]*sc+t);t=rez[i]/BASE;rez[i]%=BASE;
    }
}
int main()
{
    rez[0]=rez[1]=1;
    for(int i=0;i<=10;i++) dp[0][i]=1;
    for(int i=1;i<=64;i++)
    {
        for(int j=1;j<=10;j++)
            dp[i][j]=dp[i][j-1]+dp[i-1][j];
    }
    fscanf(f,"%d %lld",&N,&T);
    for(long long i=2;i*i<=T;i++)
    {
        int exp=0;
        while(T%i==0)
            exp++,T/=i;
        if(exp)
            mul(dp[exp][N]);
    }
    if(T!=1)
       mul(dp[1][N]);
    fprintf(g,"%d",rez[dim]);
    for(int i=dim-1;i;i--)
    {
        int cb=BASE/10;
        while(cb>rez[i])
        {
            fprintf(g,"0");
            cb/=10;
        }
        if(rez[i])
            fprintf(g,"%d",rez[i]);
    }
    fclose(f);
    fclose(g);
    return 0;
}
