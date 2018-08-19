#include <cstdio>
#include <algorithm>
#define NMAX 100001
using namespace std;
FILE *f=fopen("ks.in","r");
FILE *g=fopen("ks.out","w");
long long s,S[NMAX];
int V[NMAX];
long long st[NMAX],dr[NMAX];
long long K,N,rez=(1LL<<62);
int main()
{
    fscanf(f,"%lld%lld",&N,&K);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d",&V[i]);
        s+=V[i];
        if(i>=K)
            {s-=V[i-K];S[i-K+1]=s;st[i]=max(st[i-1],S[i-K+1]);}
    }
    for(int i=N-K+1;i;i--)
    {
        dr[i]=max(dr[i+1],S[i]);
    }
    for(int i=1;i<=N-K+1;i++)
    {
        rez=min(rez,max(st[i-1],dr[i+K]));
    }
    fprintf(g,"%lld",rez);
    fclose(f);
    fclose(g);
    return 0;
}
