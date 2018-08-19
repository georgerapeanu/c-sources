#include <cstdio>
#include <algorithm>
using namespace std;
int primes[2000000];
bool E[2000000];
int ciur[1000005];
long long cost;
int A[500005];
int N,x,y;
int nr;
int gcd(int a,int b)
{
    if(!b)return a;
    return gcd(b,a%b);
}
int main()
{
    for(int i=2;1LL*i*i<2000000;i++)
    {
        if(!E[i])
        {
            for(int j=i*i;j<2000000;j+=i)E[j]=1;
        }
    }
    for(int i=2;i<2000000;i++)if(!E[i])primes[++nr]=i;
    scanf("%d %d %d",&N,&x,&y);cost=1LL*N*x;
    int g=0;
    for(int i=1;i<=N;i++)
    {
        int a;
        scanf("%d",&a);
        ciur[a]++;
        A[i]=a;
        g=gcd(a,g);
    }
    if(g!=1)
    {
        printf("0");
        return 0;
    }
    random_shuffle(primes+10,primes+1+nr);
    int ceva=0;
    for(int i=1;i<=nr&&ceva<=500;i++)
    {
        int it=primes[i];
        int nr=N;
        for(int j=it;j<=1000000;j+=it)nr-=ciur[j];
        if(1LL*nr*min(x,y)<cost)
        {
            ceva++;
            long long ceva=0;
            for(int i=1;i<=N;i++)ceva+=min(x+0LL,1LL*(it-(A[i]%it==0 ? it:A[i]%it))*y);
            cost=min(cost,ceva);
        }
    }
    printf("%I64d",cost);
    return 0;
}
