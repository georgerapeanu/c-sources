#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
unsigned long long N,fact[20];
unsigned long long frecv[10],nrcf,thenumber,tmp[100],numitor=1,a;
unsigned long long rez[100];
void shr(unsigned long long V[])
{
    for(int i=V[0]+1;i>1;i--)
        V[i]=V[i-1];
    V[1]=0;
    V[0]++;
}
void init(unsigned long long nr,unsigned long long V[])
{
    V[0]=0;
    while(nr)
    {
        shr(V);
        V[1]=nr%10;
        nr/=10;
    }
}
void mul(unsigned long long V[],unsigned long long val)
{
    for(int i=1;i<=V[0];i++)
        V[i]*=val;
    for(int i=V[0];i>1;i--)
    {
        V[i-1]+=V[i]/10;
        V[i]%=10;
    }
    while(V[1]>=10)
    {
        shr(V);
        V[1]=V[2]/10;
        V[2]%=10;
    }
}
void add(unsigned long long A[],unsigned long long B[])
{
    while(A[0]<B[0])
        shr(A);
    while(B[0]<A[0])
        shr(B);
    for(int i=A[0];i>1;i--)
    {
        A[i]+=B[i];
        A[i-1]+=A[i]/10;
        A[i]%=10;
    }
    A[1]+=B[1];
    while(A[1]>=10)
    {
        shr(A);
        A[1]=A[2]/10;
        A[2]%=10;
    }
}
int main()
{
    freopen("sumall.in","r",stdin);
    freopen("sumall.out","w",stdout);
    fact[0]=1;
    for(int i=1;i<=19;i++)
        fact[i]=i*fact[i-1];
    cin>>N;
    while(N)
    {
        thenumber=thenumber*10+1;
        frecv[N%10]++;
        nrcf++;
        N/=10;
    }
    for(int i=0;i<=9;i++)
        numitor*=max(1ULL,fact[frecv[i]]);
    for(int i=1;i<=9;i++)
    {
        a=numitor;
        if(frecv[i])
        {
            a/=frecv[i];
            init(fact[nrcf-1]/a,tmp);
            mul(tmp,i);
            mul(tmp,thenumber);
            add(rez,tmp);
        }
    }
    for(int i=1;i<=rez[0];i++)
        cout<<rez[i];
    return 0;
}
