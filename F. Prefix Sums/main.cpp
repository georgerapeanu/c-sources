#include <iostream>
#define LIM (1LL<<62)
using namespace std;
long long K;
int N;
long long A[200005];
long long add(long long a,long long b)
{
    if(a<LIM-b)
        return a+b;
    return LIM;
}
long long mult(long long a,long long b)
{
    if(a==0||b==0)return 0;
    if(a<LIM/b+(LIM%b==0))return a*b;
    return LIM;
}
struct matrix
{
    long long a[11][11];
    int n;
    matrix operator *(matrix & other)
    {
        matrix ans;
        ans.n=n;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                ans.a[i][j]=0;
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
                for(int k=1;k<=n;k++)
                    ans.a[i][j]=add(ans.a[i][j],mult(a[i][k],other.a[k][j]));
        return ans;
    }
};
matrix lgpow(matrix a,long long e)
{
    matrix p;
    p.n=a.n;
    for(int i=1;i<=p.n;i++)for(int j=1;j<=p.n;j++)p.a[i][j]=(i==j);
    while(e)
    {
        if(e&1)p=p*a;
        a=a*a;
        e>>=1;
    }
    return p;
}
int main()
{
    cin>>N>>K;
    for(int i=1;i<=N;i++)
    {
        cin>>A[i];
        if(A[i]>=K){cout<<0;return 0;}
    }
    int st=1;
    while(A[st]==0)st++;
    for(int i=st;i<=N;i++)A[i-st+1]=A[i];
    N=N-st+1;
    if(N>=10)
    {
        int nr=0;
        while(A[N]<K)
        {
            for(int i=1;i<=N;i++)A[i]=add(A[i-1],A[i]);
            nr++;
        }
        cout<<nr;
    }
    else
    {
        matrix ceva;
        ceva.n=N;
        for(int i=1;i<=N;i++)for(int j=1;j<=N;j++)ceva.a[i][j]=(j<=i);
        long long st=1,dr=K;
        while(st<dr)
        {
            long long mid=(st+dr)/2;
            matrix tmp=lgpow(ceva,mid);
            long long rez=0;
            for(int i=1;i<=N;i++)
            {
                rez=add(rez,mult(tmp.a[N][i],A[i]));
            }
            if(rez>=K)dr=mid;
            else st=mid+1;
        }
        cout<<dr;
    }
    return 0;
}
