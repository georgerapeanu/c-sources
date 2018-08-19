#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
FILE *f=fopen("resturi.in","r");
FILE *g=fopen("resturi.out","w");
const int LEN=30;
int BASE=10000;
typedef int tp;
tp C[LEN];
void del(tp A[])
{
    memset(A,0,(A[0]+1)*sizeof(tp));
}
void init(tp A[],tp val)
{
    del(A);
    while(val)
    {
        A[++A[0]]=val%BASE;
        val/=BASE;
    }
    if(!A[0])A[0]=1;
}
int cmp(tp A[],tp B[])
{
    if(A[0]!=B[0])return A[0]<B[0] ? -1:1;
    int ind=A[0];
    while(ind&&A[ind]==B[ind])ind--;
    if(!ind)return 0;
    return A[ind]<B[ind] ? -1:1;
}
void add(tp A[],tp B[])
{
    tp t=0;
    for(int i=1;i<=A[0]||i<=B[0]||t;i++)
    {
        A[i]=(A[i]+B[i]+t);
        t=A[i]/BASE;
        A[i]%=BASE;
        A[0]=max(i,A[0]);
    }
}
void scad(tp A[],tp B[])
{
    int t=0;
    for(int i=1;i<=B[0]||t;i++)
    {
        A[i]=A[i]-B[i]-t;
        t=0;
        if(A[i]<0)
        {
            A[i]+=BASE;
            t=1;
        }
    }
    while(A[0]>1&&!A[A[0]])A[0]--;
}
void mults(tp A[],tp val)
{
    tp t=0;
    for(int i=1;i<=A[0]||t;i++)
    {
        A[i]=(A[i]*val+t);
        t=A[i]/BASE;
        A[i]%=BASE;
        A[0]=max(A[0],i);
    }
    while(A[0]>1&&!A[A[0]])A[0]--;
}
void mult(tp A[],tp B[])
{
    del(C);
    C[0]=A[0]+B[0]-1;
    for(int i=1;i<=A[0];i++)
        for(int j=1;j<=B[0];j++)
            C[i+j-1]+=A[i]*B[j];
    tp t=0;
    for(int i=1;i<=C[0]||t;i++)
    {
        C[i]+=t;
        t=C[i]/BASE;
        C[i]%=BASE;
        C[0]=max(i,C[0]);
    }
    memcpy(A,C,sizeof(C));
    while(A[0]>1&&!A[A[0]])A[0]--;
}
void mod(tp A[],tp B[])
{
    if(cmp(A,B)<0)return ;
    init(C,0);
    for(int i=A[0];i;i--)
    {
        mults(C,BASE);
        C[1]=A[i];
        while(cmp(C,B)>=0)scad(C,B);
    }
    memcpy(A,C,sizeof(C));
}
tp mod2(tp A[],tp val)
{
    tp r=0;
    for(int i=A[0];i;i--)
    {
        r=(r*BASE+A[i])%val;
    }
    return r;
}
tp lgpow(tp b,tp e,tp val)
{
    tp p=1;
    while(e)
    {
        if(e&1)p=(1LL*p*b)%val;
        b=(1LL*b*b)%val;
        e>>=1;
    }
    return p;
}
int T,N;
int p[31],r[31];
tp tmp[LEN];
tp M[LEN];
tp P[LEN],rez[LEN];
int main()
{
    fscanf(f,"%d",&T);
    while(T--)
    {
        fscanf(f,"%d",&N);
        for(int i=1;i<=N;i++)fscanf(f,"%d %d",&p[i],&r[i]);
        init(P,1);init(rez,0);
        for(int i=1;i<=N;i++)
            mults(P,p[i]);
        for(int i=1;i<=N;i++)
        {
            init(M,1);
            init(tmp,r[i]);
            for(int j=1;j<=N;j++)if(i!=j){mults(M,p[j]);}
            mult(tmp,M);mod(tmp,P);
            mults(tmp,lgpow(mod2(M,p[i]),p[i]-2,p[i]));
            mod(tmp,P);
            add(rez,tmp);mod(rez,P);
        }
        fprintf(g,"%d",rez[rez[0]]);
        for(int i=rez[0]-1;i;i--)
        {
            int cb=BASE/10;
            while(rez[i]<cb&&cb>1)
            {
                fprintf(g,"0");
                cb/=10;
            }
            fprintf(g,"%d",rez[i]);
        }
        fprintf(g,"\n");
    }
    fclose(f);
    fclose(g);
    return 0;
}
