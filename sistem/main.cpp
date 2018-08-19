#include <cstdio>
#include <cstring>
#define BASE 1000000
#define NMAX 35
using namespace std;
FILE *f=fopen("sistem.in","r");
FILE *g=fopen("sistem.out","w");
long long N,k,C[NMAX],i,V[105][NMAX],DP[105][NMAX],val;
long long tmp[NMAX];
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
    fscanf(f,"%lld",&N);
    V[2][1]=V[2][0]=1;
    for(i=3;i<N;i++)
    {
        add(V[i],V[i-1]);
        inms(V[i],i);
    }
    DP[0][0]=1;
    DP[0][1]=1;
    for(i=3;i<=N;i++)
    {
        val=((i-1)*(i-2))/2;
        reset(C);
        C[0]=C[1]=1;
        inms(C,val);
        for(k=3;k<i;k++)
        {
            reset(tmp);
            add(tmp,C);
            inm(tmp,V[k-1]);
            inm(tmp,DP[i-k]);
            add(DP[i],tmp);
            inms(C,i-k);
            imps(C,k);
        }
        add(DP[i],V[i-1]);
    }
    for(i=1;i<=DP[N][0];i++)
    {
        if(i>1)
        {
            if(DP[N][i]<100000)
                fprintf(g,"0");
            if(DP[N][i]<10000)
                fprintf(g,"0");
            if(DP[N][i]<1000)
                fprintf(g,"0");
            if(DP[N][i]<100)
                fprintf(g,"0");
            if(DP[N][i]<10)
                fprintf(g,"0");
        }
        fprintf(g,"%lld",DP[N][i]);
    }
    fclose(f);
    fclose(g);
    return 0;
}
