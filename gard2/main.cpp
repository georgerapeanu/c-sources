#include <cstdio>
#include <algorithm>
#define BASE 10000000
#define NMAX 20
using namespace std;
FILE *f=fopen("gard2.in","r");
FILE *g=fopen("gard2.out","w");
long long DP[55][55][NMAX],C[55][55][NMAX],tmp[NMAX];
long long i,j,p,N,K;
void reset(long long V[])
{
    for(int i=0;i<NMAX;i++)
        V[i]=0;
}
void shl(long long V[])
{
    for(int i=1;i<V[0];i++)
        V[i]=V[i+1];
    V[V[0]]=0;
    V[0]--;
}
void shr(long long V[])
{
    for(int i=V[0];i>=1;i--)
        V[i+1]=V[i];
    V[0]++;
    V[1]=0;
}
void add(long long A[],long long B[])
{
    while(A[0]>B[0])
        shr(B);
    while(A[0]<B[0])
        shr(A);
    for(int i=1;i<=A[0];i++)
        A[i]+=B[i];
    for(int i=A[0];i>1;i--)
    {
        A[i-1]+=A[i]/BASE;
        A[i]%=BASE;
    }
    while(A[1]>BASE)
    {
        shr(A);
        A[1]=A[2]/BASE;
        A[2]%=BASE;
    }
    while(B[0]>1&&B[1]==0)
        shl(B);
}
void inms(long long A[],long long S)
{
    for(int i=1;i<=A[0];i++)
        A[i]*=S;
    for(int i=A[0];i>1;i--)
    {
        A[i-1]+=A[i]/BASE;
        A[i]%=BASE;
    }
    while(A[1]>BASE)
    {
        shr(A);
        A[1]=A[2]/BASE;
        A[2]%=BASE;
    }
}
void inm(long long A[],long long B[])
{
    long long C[NMAX];
    reset(C);
    C[0]=A[0]+B[0]-1;
    for(int i=1;i<=A[0];i++)
        for(int j=1;j<=B[0];j++)
            C[i+j-1]+=A[i]*B[j];
    for(int i=C[0];i>1;i--)
    {
        C[i-1]+=C[i]/BASE;
        C[i]%=BASE;
    }
    while(C[1]>BASE)
    {
        shr(C);
        C[1]=C[2]/BASE;
        C[2]%=BASE;
    }
    reset(A);
    for(int i=0;i<=C[0];i++)
        A[i]=C[i];
}
void imps(long long V[],long long x)
{
    long long r=0;
    long long C[NMAX];
    reset(C);
    C[0]=V[0];
    for(int i=1;i<=V[0];i++)
    {
        C[i]=(r+V[i])/x;
        r=(r+V[i])%x;
        r*=BASE;
    }
    while(!C[1])
        shl(C);
    for(int i=0;i<=C[0];i++)
        V[i]=C[i];
}
int main()
{
    fscanf(f,"%lld %lld",&N,&K);
    DP[0][0][0]=DP[0][0][1]=1;
    for(i=1;i<=N;i++)
       C[i][0][1]=C[i][0][0]=C[i][i][0]=C[i][i][1]=1;
    for(i=1;i<=N;i++)
    {
        for(j=1;j<i;j++)
        {
            add(C[i][j],C[i-1][j-1]);
            add(C[i][j],C[i-1][j]);
        }
    }
    for(i=1;i<=K;i++)
        DP[i][1][0]=DP[i][1][1]=1;
    for(i=1;i<=N;i++)
    {
        for(j=2;j<=i;j++)
        {
            int ntmp=min(K,i-1);
            for(p=1;p<=ntmp;p++)
            {
                reset(tmp);
                add(tmp,DP[i-p][j-1]);
                inm(tmp,C[i][i-p]);
                add(DP[i][j],tmp);
            }
        }
    }
    reset(tmp);
    for(i=1;i<=N;i++)
    {
        add(tmp,DP[N][i]);
    }
    for(i=1;i<=tmp[0];i++)
    {
        if(i>1)
        {
            if(tmp[i]<1000000)
                fprintf(g,"0");
            if(tmp[i]<100000)
                fprintf(g,"0");
            if(tmp[i]<10000)
                fprintf(g,"0");
            if(tmp[i]<1000)
                fprintf(g,"0");
            if(tmp[i]<100)
                fprintf(g,"0");
            if(tmp[i]<10)
                fprintf(g,"0");
        }
        fprintf(g,"%lld",tmp[i]);
    }
    fclose(f);
    fclose(g);
    return 0;
}
