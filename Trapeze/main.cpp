#include <cstdio>
#include <cstring>
#include <bitset>
#include <algorithm>
using namespace std;
FILE *f=fopen("trapeze.in","r");
FILE *g=fopen("trapeze.out","w");
typedef long long tp;
const tp BASE=10000;
const int LEN=60;
void init(tp A[],tp val)
{
    memset(A,0,sizeof(tp)*(A[0]+1));
    if(val==0){A[0]=1;A[1]=0;return ;}
    while(val){A[++A[0]]=val%BASE;val/=BASE;}
}
short cmp(tp A[],tp B[])
{
    if(A[0]!=B[0])return A[0]<B[0] ? -1:1;
    int ind=A[0];
    while(ind&&A[ind]==B[ind])ind--;
    if(!ind)return 0;
    return A[ind]<B[ind] ? -1:1;

}
tp C[LEN];
tp tmp[LEN];
void mult(tp A[],tp B[])
{
    memset(C,0,sizeof(C));
    C[0]=A[0]+B[0]-1;
    for(int i=1;i<=A[0];i++)
        for(int j=1;j<=B[0];j++)
            C[i+j-1]+=A[i]*B[j];
    tp t=0;
    for(tp i=1;i<=C[0]||t;i++)
    {
        C[i]+=t;
        t=C[i]/BASE;
        C[i]%=BASE;
        C[0]=max(C[0],i);
    }
    memcpy(A,C,sizeof(C));
    while(A[0]>1&&A[A[0]]==0)A[0]--;
}
void multscalar(tp A[],int val)
{
    tp t=0;
    for(tp i=1;i<=A[0]||t;i++)
    {
        A[i]=A[i]*val+t;
        t=A[i]/BASE;
        A[i]%=BASE;
        A[0]=max(A[0],i);
    }
    while(A[0]>1&&A[A[0]]==0)A[0]--;
}
int primes[45];
bitset<10005> E;
tp dp[105][105][LEN];
tp pw[LEN];
int K;
int main()
{
    for(int i=2;i<=10000;i++)
    {
        if(!E[i])
        {
            if(i!=2)primes[++primes[0]]=i;
            if(primes[0]==44)break;
            for(int j=i*i;j<=10000;j+=i)
                E[j]=1;
        }
    }
    init(dp[0][1],1);
    for(int i=0;i<44;i++)
    {
        for(int j=1;j<=100;j++)
        {
            if(dp[i][j][0])
            {
                init(pw,1);
                for(int k=1;k*j<=100;k++)
                {
                    memcpy(tmp,pw,sizeof(pw));
                    mult(tmp,dp[i][j]);
                    if(dp[i+1][j*k][0]==0||cmp(dp[i+1][j*k],tmp)>0)
                        memcpy(dp[i+1][j*k],tmp,sizeof(tmp));
                    multscalar(pw,primes[i+1]);
                }
            }
        }
    }
    fscanf(f,"%d",&K);
    fprintf(g,"%d",dp[44][K][dp[44][K][0]]);
    for(int i=dp[44][K][0]-1;i;i--)
    {
        int cb=BASE/10;
        if(i!=dp[44][K][0])while(cb>dp[44][K][i]&&(!(cb==1&&dp[44][K][i]==0))){fprintf(g,"0");cb/=10;}
        fprintf(g,"%d",dp[44][K][i]);
    }
    fclose(f);
    fclose(g);
    return 0;
}
