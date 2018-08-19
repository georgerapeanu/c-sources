#include <iostream>
#define MOD 1000000007
using namespace std;
long long p[16][16];
long long b[16][16];
long long tmp[16][16];
void inm(long long a[][16],long long b[][16])
{
    for(long long i=0;i<16;i++)
        for(long long j=0;j<16;j++)
        {
            tmp[i][j]=0;
            for(long long k=0;k<16;k++)
                tmp[i][j]=(tmp[i][j]+1LL*a[i][k]*b[k][j])%MOD;
        }
    for(long long i=0;i<16;i++)for(long long j=0;j<16;j++)a[i][j]=tmp[i][j];
}
long long lgpow(long long e)
{
    while(e)
    {
        if(e&1)inm(p,b);
        inm(b,b);
        e>>=1;
    }
}
void baga(long long lim)
{
    for(long long i=0;i<16;i++)for(long long j=0;j<16;j++)b[i][j]=0;
    for(long long i=0;i<=lim;i++)
    {
        for(long long j=0;j<=lim;j++)
        {
            b[i][j]=(j-1<=i&&i<=j+1);
        }
    }
}
long long N,K;
long long A[105],B[105],C[105];
int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    for(long long i=0;i<16;i++)for(long long j=0;j<16;j++)p[i][j]=(i==j);
    cin>>N>>K;
    for(long long i=1;i<=N;i++)
    {
        cin>>A[i]>>B[i]>>C[i];
        B[i]=min(K,B[i]);
        baga(C[i]);
        lgpow(B[i]-A[i]);
    }
    cout<<p[0][0];
    return 0;
}
