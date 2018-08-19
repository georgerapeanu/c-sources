#include <cstdio>
#include <cstring>
#include <algorithm>
#include <bitset>
#define LEN 10005
#define BASE 10000
using namespace std;
FILE *f=fopen("indep.in","r");
FILE *g=fopen("indep.out","w");
int F[LEN];
bitset<LEN> P,PP;
int sgn[LEN];
int N;
int p[LEN];
int b[LEN];
int C[LEN];
int R[LEN];
int mval,val;
void init(int val,int V[])
{
    memset(V,0,sizeof(int)*(V[0]+1));
    if(!val){V[0]=1;return;}
    while(val)
    {
        V[++V[0]]=val%BASE;
        val/=BASE;
    }
}
void add(int A[],int B[])
{
    int t=0;
    for(int i=1;i<=A[0]||i<=B[0]||t;i++)
    {
        A[0]=max(A[0],i);
        A[i]=A[i]+B[i]+t;
        t=A[i]/BASE;
        A[i]%=BASE;
    }
}
void scad(int A[],int B[])
{
    int t=0;
    for(int i=1;i<=B[0]||t;i++)
    {
        A[i]=A[i]-B[i]-t;
        if(A[i]<0)
        {
            A[i]+=BASE;
            t=1;
        }
        else
            t=0;
    }
    while(A[0]>1&&!A[A[0]])A[0]--;
}
void mult(int A[],int B[])
{
    init(0,C);
    C[0]=A[0]+B[0]-1;
    for(int i=1;i<=A[0];i++)
        for(int j=1;j<=B[0];j++)
            C[i+j-1]+=A[i]*B[j];
    int t=0;
    for(int i=1;i<=C[0]||t;i++)
    {
        C[i]+=t;
        t=C[i]/BASE;
        C[i]%=BASE;
        C[0]=max(C[0],i);
    }
    memcpy(A,C,sizeof(C));
}
void lgpow(int e)
{
    init(1,p);
    init(2,b);
    while(e)
    {
        if(e&1)mult(p,b);
        mult(b,b);
        e>>=1;
    }
}
int getval(int nr)
{
    int rez=0;
    for(int i=nr;i<=mval;i+=nr)
        rez+=F[i];
    return rez;
}
int u[LEN];
int main()
{
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d",&val);
        F[val]++;
        mval=max(mval,val);
    }
    init(1,u);
    P[1]=1;
    for(int i=1;i<=mval;i++)
    {
        if(PP[i])continue;
        if(!P[i])
        {
            for(int j=i;j<=mval;j+=i)
                {P[j]=1;sgn[j]^=1;}
            for(int j=i*i;j<=mval;j+=i*i)
                PP[j]=1;
        }
        lgpow(getval(i));
        scad(p,u);
        if(sgn[i])scad(R,p);
        else add(R,p);
    }
    for(int i=R[0];i;i--)
    {
        int cb=BASE/10;
        if(i!=R[0])while(cb>R[i]&&(!(cb==1&&R[i]==0))){fprintf(g,"0");cb/=10;}
        fprintf(g,"%d",R[i]);
    }
    fclose(f);
    fclose(g);
    return 0;
}
