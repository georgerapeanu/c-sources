#include <cstdio>
#define LIM 1000000000000000000LL
using namespace std;
int N;
int T;
long long V[2005];
int rez;
long long gcd(long long a,long long b)
{
    if(!b)return a;
    return gcd(b,a%b);
}
long long lcm(long long a,long long b)
{
    long long tmp=gcd(a,b);
    if(a/tmp>LIM/b)return -1;
    return a/tmp*b;
}
int main()
{
    scanf("%d",&T);
    while(T--)
    {
        rez=0;
        scanf("%d",&N);
        for(int i=1;i<=N;i++){scanf("%I64d",&V[i]);V[i]+=V[i-1];}
        for(int i=1;i<=N;i++)
        {
            rez++;
            long long ceva=V[i]-V[i-1];
            for(int j=i+1;j<=N;j++)
            {
                ceva=lcm(ceva,V[j]-V[j-1]);
                if(ceva==-1)break;
                rez+=((V[j]-V[i-1])%ceva==0);
            }
        }
        printf("%d\n",rez);
    }
    return 0;
}
