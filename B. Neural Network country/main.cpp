#include <cstdio>
#include <algorithm>
#include <cstring>
#define MOD 1000000007
using namespace std;
int N,L,M;
int tmp[1000005];
int fr[1005];
struct matrix{
    int n;
    int a[105][105];
    matrix()
    {
        n=0;
        memset(a,0,sizeof(a));
    }
    matrix(int N)
    {
        memset(a,0,sizeof(a));
        n=N;
        for(int i=0;i<N;i++)
        {
            for(int j=0;j<N;j++)
            {
                a[i][((i-j)%n+n)%n]=fr[j];
            }
        }
    }
    matrix operator * (const matrix &other)const
    {
        matrix ans;
        ans.n=n;
        for(int i=0;i<n;i++)
        {
            for(int j=0;j<n;j++)
            {
                for(int k=0;k<n;k++)
                {
                    ans.a[i][j]=(ans.a[i][j]+1LL*a[i][k]*other.a[k][j])%MOD;
                }
            }
        }
        return ans;
    }
};
matrix lgpow(matrix b,int e)
{
    matrix p;
    p.n=M;
    for(int i=0;i<M;i++)p.a[i][i]=1;
    while(e)
    {
        if(e&1)p=p*b;
        b=b*b;
        e>>=1;
    }
    return p;
}
int main()
{
    scanf("%d%d%d",&N,&L,&M);
    for(int i=1;i<=N;i++)
    {
        int val;
        scanf("%d",&val);
        fr[val%M]++;
    }
    matrix a(M);
    memset(fr,0,sizeof(fr));
    for(int i=1;i<=N;i++)
    {
        int val;
        scanf("%d",&val);
        fr[val%M]++;
        tmp[i]=val%M;
    }
    matrix b=matrix(M);
    a=a*lgpow(b,L-2);
    memset(fr,0,sizeof(fr));
    for(int i=1;i<=N;i++)
    {
        int val;
        scanf("%d",&val);
        tmp[i]+=val;if(tmp[i]>=M)tmp[i]-=M;
       fr[tmp[i]]++;
    }
    matrix c=matrix(M);
    a=a*c;
    printf("%d",a.a[0][0]);
    return 0;
}
