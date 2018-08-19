#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
FILE *f=fopen("pastile.in","r");
FILE *g=fopen("pastile.out","w");
typedef long long tp;
const tp BASE=1000000;///daca folosesti impscalar sau imp,nu ar trebui sa o faci mare
///daca vrei sa folosesti functia rad,base trebuie neaparat sa fie 10
const int LEN=1000000;
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
    while(A[0]>1&&A[A[0]]==0)A[0]--;
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
    while(A[0]>1&&A[A[0]]==0)A[0]--;
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
tp tmp[LEN];
tp CRad[LEN];
tp RRad[LEN];
void rad(tp A[])
{
    init(RRad,0);
    int l=A[0];
    RRad[1]=A[l--];
    if(A[0]%2==0){multscalar(RRad,BASE);RRad[1]=A[l--];}
    init(CRad,BASE-1);
    while(1)
    {
        memcpy(tmp,CRad,sizeof(CRad));
        mult(tmp,tmp);
        if(cmp(tmp,RRad)<=0)
            break;
        CRad[1]--;
    }
    scad(RRad,tmp);
    for(;l;l-=2)
    {
        multscalar(RRad,BASE*BASE);
        RRad[0]=max(RRad[0],(tp)2);
        RRad[2]=A[l];
        RRad[1]=A[l-1];
        multscalar(CRad,BASE);
        int cf=BASE-1;
        while(cf>0)
        {
            memcpy(tmp,CRad,sizeof(CRad));
            multscalar(tmp,2);
            tmp[1]=cf;
            multscalar(tmp,cf);
            if(cmp(tmp,RRad)<=0)break;
            cf--;
        }
        CRad[1]=cf;
        if(cf!=0)scad(RRad,tmp);
    }
    while(CRad[0]>1&&CRad[CRad[0]]==0)CRad[0]--;
    memcpy(A,CRad,sizeof(CRad));
}
tp A[LEN];
int N;
int main()
{
    fscanf(f,"%d",&N);
    init(A,1);
    for(int i=N+1;i<=2*N;i++)
    {
        multscalar(A,i);
    }
    for(int i=N+1;i<=2*N;i++)
        impscalar(A,i-N);
    impscalar(A,N+1);
    fprintf(g,"%lld",A[A[0]]);
    for(int i=A[0]-1;i;i--)
    {
        tp cb=BASE/10;
        while(cb>1&&cb>A[i])fputc('0',g);
        fprintf(g,"%lld",A[i]);
    }
    fclose(f);
    fclose(g);
    return 0;
}
