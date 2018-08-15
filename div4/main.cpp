#include <cstdio>
#include <cstring>
#define MOD 1000003
using namespace std;
FILE *f=fopen("div4.in","r");
FILE *g=fopen("div4.out","w");
long long i,N,K,rez,tmp;
long long frecv[2];
char C[100005];
long long fact[100005];
long long INV[1000005];
void euclid(long long a,long long b,long long *x,long long *y)
{
    if(b==0)
    {
        *x=1;
        *y=0;
    }
    else
    {
        long long x0,y0;
        euclid(b,a%b,&x0,&y0);
        *x=y0;
        *y=x0-y0*(a/b);
    }
}
int main()
{
    fgets(C+1,100005,f);
    fscanf(f,"%lld",&K);
    N=strlen(C+1);
    if(C[N]=='\n')
        N--;
    if(K==N-1)
    {
        for(i=1;i<=N;i++)
            rez+=(C[i]-'0')%4==0;
        fprintf(g,"%lld",rez);
        return 0;
    }
    fact[0]=1;
    for(i=1;i<=N;i++)
        fact[i]=(fact[i-1]*i)%MOD;
    euclid(fact[N-K-2],MOD,&INV[fact[N-K-2]],&tmp);
    INV[fact[N-K-2]]%=MOD;
    if(INV[fact[N-K-2]]<0)
        INV[fact[N-K-2]]+=MOD;
    INV[INV[fact[N-K-2]]]=fact[N-K-2];
    for(i=N;i>=N-K-1;i--)
    {
        if(!INV[fact[K-N+i+1]])
        {
            euclid(fact[K-N+i+1],MOD,&INV[fact[K-N+i+1]],&tmp);
            INV[fact[K-N+i+1]]%=MOD;
            if(INV[fact[K-N+i+1]]<0)
                INV[fact[K-N+i+1]]+=MOD;
            INV[INV[fact[K-N+i+1]]]=fact[K-N+i+1];
        }
        rez=(rez+(((((fact[i-1]*INV[fact[N-K-2]])%MOD)*INV[fact[K-N+i+1]])%MOD)*frecv[(C[i]-'0')%2])%MOD)%MOD;
        if((C[i]-'0')%2==0)
        {
            if((C[i]-'0')%4==0)
                frecv[0]++;
            else
                frecv[1]++;
        }
    }
    fprintf(g,"%lld",rez);
    fclose(f);
    fclose(g);
    return 0;
}
