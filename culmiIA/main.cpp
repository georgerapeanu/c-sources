#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
FILE *f=fopen("culmi.in","r");
FILE *g=fopen("culmi.out","w");
typedef int tp;
const tp BASE=10;///daca folosesti impscalar,nu ar trebui sa o faci mare,ca te fute dupa timpul
const int LEN=1000;
void init(tp A[],tp val)
{
    memset(A,0,sizeof(tp)*(A[0]+1));
    if(val==0){A[0]=1;A[1]=0;return ;}
    while(val){A[++A[0]]=val%BASE;val/=BASE;}
}
void add(tp A[],tp B[])
{
    tp t=0;
    for(tp i=1;i<=A[0]||i<=B[0]||t;i++)
    {
        A[i]=(A[i]+t+B[i]);
        t=0;
        while(A[i]>=BASE){t++;A[i]-=BASE;}
        A[0]=max(A[0],i);
    }
}
short cmp(tp A[],tp B[])
{
    if(A[0]!=B[0])return A[0]<B[0] ? -1:1;
    int ind=A[0];
    while(ind&&A[ind]==B[ind])ind--;
    if(!ind)return 0;
    return A[ind]<B[ind] ? -1:1;

}
void scad(tp A[],tp B[])
{
    tp t=0;
    for(int i=1;i<=B[0]||t;i++)
    {
        A[i]=A[i]-t-B[i];
        t=0;
        if(A[i]<0){t=1;A[i]+=BASE;}
    }
    while(A[0]>1&&A[A[0]]==0)A[0]--;
}
tp C[LEN];
tp R[LEN];
void mult(tp A[],tp B[])
{
    memset(C,0,sizeof(C));
    C[0]=A[0]+B[0]-1;
    for(int i=1;i<=A[0];i++)
        for(int j=1;j<=B[0];j++)
            C[i+j-1]+=A[i]*B[j];
    tp t=0;
    for(tp i=1;i<=C[0]||t;i++)
    {
        C[i]+=t;
        t=C[i]/BASE;
        C[i]%=BASE;
        C[0]=max(C[0],i);
    }
    memcpy(A,C,sizeof(C));
}
void multscalar(tp A[],int val)
{
    tp t=0;
    for(tp i=1;i<=A[0]||t;i++)
    {
        A[i]=A[i]*val+t;
        t=A[i]/BASE;
        A[i]%=BASE;
        A[0]=max(A[0],i);
    }
}
void imp(tp A[],tp B[])
{
    init(C,0);
    init(R,0);
    for(int i=A[0];i;i--)
    {
        multscalar(R,BASE);
        R[1]=A[i];
        multscalar(C,BASE);
        while(cmp(R,B)>=0)
        {
            C[1]++;
            scad(R,B);
        }
    }
    memcpy(A,C,sizeof(C));
}
void impscalar(tp A[],tp val)
{
    tp r=0;
    init(C,0);
    for(int i=A[0];i;i--)
    {
        r=r*BASE+A[i];
        multscalar(C,BASE);
        C[1]=r/val;
        r%=val;
    }
    memcpy(A,C,sizeof(C));
}
tp fact[105][LEN];
tp rez[LEN];
int N,K;
int main()
{
    fscanf(f,"%d %d",&N,&K);
    init(fact[0],1);
    for(int i=1;i<=N;i++)
    {
        memcpy(fact[i],fact[i-1],sizeof(fact[i-1]));
        multscalar(fact[i],i);
    }
    add(rez,fact[N]);
    imp(rez,fact[K]);
    imp(rez,fact[N-K]);
    mult(rez,fact[N]);
    imp(rez,fact[K-1]);
    imp(rez,fact[N-K+1]);
    impscalar(rez,N);
    fprintf(g,"%d",rez[rez[0]]);
    for(int i=rez[0]-1;i;i--)
    {
        tp cb=BASE/10;
        while(cb>1&&rez[i]<cb){fputc('0',g);cb/=10;}
        fprintf(g,"%d",rez[i]);
    }
    fclose(f);
    fclose(g);
    return 0;
}
