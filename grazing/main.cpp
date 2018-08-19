#include <cstdio>
#include <cstring>
using namespace std;
FILE *f=fopen("grazing.in","r");
FILE *g=fopen("grazing.out","w");
typedef long long tp;
const int LEN=80;
const int BASE=100000000;
tp C[301][301][LEN];
tp dp[301][LEN];
tp fact[301][LEN];
tp tmp[LEN];
tp tmp2[LEN];
tp D[LEN];
int N;
void init(tp A[],int val)
{
    while(val){A[++A[0]]=val%BASE;val/=BASE;}
    if(!A[0])A[0]=1;
}
void add(tp A[],tp B[])
{
    tp t=0;
    for(int i=1;i<=A[0]||i<=B[0]||t;i++)
    {
        A[i]=A[i]+B[i]+t;
        if(A[i]>=BASE){t=1;A[i]-=BASE;}
        else t=0;
        if(A[0]<i)A[0]=i;
    }
}
void multscalar(tp A[],int nr)
{
    tp t=0;
    for(int i=1;i<=A[0]||t;i++)
    {
        A[i]=A[i]*nr+t;
        t=A[i]/BASE;
        A[i]%=BASE;
        if(A[0]<i)A[0]=i;
    }
}
void mult(tp A[],tp B[])
{
     memset(D,0,(D[0]+1)*sizeof(tp));
    D[0]=A[0]+B[0]-1;
    for(int i=1;i<=A[0];i++)
        for(int j=1;j<=B[0];j++)
            D[i+j-1]+=A[i]*B[j];
    tp t=0;
    for(int i=1;i<=D[0]||t;i++)
    {
        D[i]=D[i]+t;
        t=D[i]/BASE;
        D[i]%=BASE;
        if(D[0]<i)D[0]=i;
    }
    memcpy(A,D,sizeof(tp)*(D[0]+1));
}
void afis(int N)
{
    fprintf(g,"\"");
    fprintf(g,"%lld",dp[N][dp[N][0]]);
    for(int i=dp[N][0]-1;i;i--)
    {
        int cb=BASE/10;
        while(cb>1&&cb>dp[N][i]){fputc('0',g);cb/=10;}
        fprintf(g,"%lld",dp[N][i]);
    }
    fprintf(g,"\"");
    fprintf(g,",\n");
}
int main()
{
    init(C[0][0],1);
    init(fact[0],1);
    for(int i=1;i<=300;i++)
    {
        memcpy(fact[i],fact[i-1],sizeof(tp)*(fact[i-1][0]+1));
        if(i>2)multscalar(fact[i],i);
        init(C[i][i],1);
        init(C[i][0],1);
        for(int j=1;j<i;j++)
        {
            memcpy(C[i][j],C[i-1][j],sizeof(tp)*(C[i-1][j][0]+1));
            add(C[i][j],C[i-1][j-1]);
        }
    }
    init(dp[0],1);
    init(dp[1],1);
    init(dp[2],2);
    fscanf(f,"%d",&N);
    for(int i=3;i<=N;i++)
    {
        for(int j=0;j<i;j++)
        {
            memcpy(tmp,C[i-1][j],sizeof(C[i-1][j]));
            mult(tmp,dp[i-1-j]);
            memcpy(tmp2,fact[j+1],sizeof(fact[j+1]));
            if((j+1)%3!=0&&j>2)add(tmp2,fact[j]);
            mult(tmp,tmp2);
            add(dp[i],tmp);
        }
    }
    for(int N=1;N<=300;N++)afis(N);
    fclose(f);
    fclose(g);
    return 0;
}
