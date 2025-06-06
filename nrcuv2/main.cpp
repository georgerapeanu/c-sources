#include <cstdio>
#include <cstring>
#include <cstdlib>
using namespace std;
FILE *f=fopen("nrcuv.in","r");
FILE *g=fopen("nrcuv.out","w");
int N,st,i,cn;
short *P,*Q,tmp;
short* shr(short *V)
{
    while(V[1]>9)
    {
        for(int i=V[0]+1;i>1;i--)
            V[i]=V[i-1];
        V[1]=V[2]/10;
        V[2]%=10;
        V[0]++;
    }
    return V;
}
short* inmultire(short *V,int nr)
{
    for(int i=1;i<=V[0];i++)
    {
        V[i]*=nr;
    }
    for(int i=V[0];i>1;i--)
    {V[i-1]+=V[i]/10;V[i]%=10;}
    V=shr(V);
    return V;
}
short* inmultirelog(short *A,short *B)
{
    short *C;
    C[0]=B[0]+A[0]-1;
    for(int i=1;i<=A[0];i++)
    {
        for(int j=1;j<=B[0];j++)
        {
            C[i+j-1]+=A[i]*B[j];
        }
    }
    for(int i=C[0];i>1;i--)
    {
        C[i-1]+=C[i]/10;
        C[i]%=10;
    }
    C=shr(C);
    return C;
}

short* logpow(short *V,int pow)
{
    short *C;
    C=(short*)malloc(2000);
    memset(C,0,1000);
    C[0]=C[1]=1;
    while(pow)
    {
        if(pow%2==1)
        {
            C=inmultirelog(V,C);
        }
        V=inmultirelog(V,V);
        pow/=2;
    }
    return C;
}
short* scadere(short A[],short B[])
{
    short *C;
    C=(short*)malloc(1000);
    C[0]=B[0];
    while(A[0]<B[0])
    {
        for(int i=A[0]+1;i>1;i--)
        {
            A[i]=A[i-1];
            A[1]=0;
        }
        A[0]++;
    }
    for(int i=1;i<=A[0];i++)
    {
        C[i]=B[i]-A[i];
    }
    st=1;
    while(C[i]==0&&st<=C[0])
    {
        st++;
    }
    return C;
}
int main()
{
    fscanf(f,"%d",&N);
    cn=N;
    P=(short*)malloc(1000);
    Q=(short*)malloc(1000);
    memset(P,0,1000);
    memset(Q,0,1000);
    while(cn)
    {
        P[0]++;
        P[P[0]]=cn%10;
        cn/=10;
    }
    for(i=1;i<=P[0]/2;i++)
    {
        tmp=P[i];
        P[i]=P[P[0]-i+1];
        P[P[0]-i+1]=tmp;
    }
    P=logpow(P,N);
    Q[0]=Q[1]=1;
    for(i=2;i<=N;i++)
    {
        Q=inmultire(Q,i);
    }
    Q=scadere(Q,P);
    for(i=st;i<=Q[0];i++)
        fprintf(g,"%hd",Q[i]);
    fclose(f);
    fclose(g);
    return 0;
}
