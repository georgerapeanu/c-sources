#include <cstdio>
#include <iostream>
#include <vector>
#include <cmath>
#define LEN 3000
#define LL int
using namespace std;
FILE *f=fopen("xp.in","r");
FILE *g=fopen("xp.out","w");
int a1,b1;
LL apr,a;
LL bpr,b;
int N;
int P,Q;
int val[LEN+5];
int Pr[LEN+5];
int st[LEN+5];
LL A(LL apr,LL bpr)
{
    return ((apr+P-1)^(bpr+1))%P;
}
LL B(LL apr,LL bpr)
{
    return ((apr+P-1)|(bpr+1))%P;
}
int gval(LL a,LL b,int i)
{
    return max(1,((i % P) ^ (((a + 1) & (b + 1)) % P)) % P);
}
int nr;
int main()
{
    fscanf(f,"%d%d%d%d%d",&N,&a1,&b1,&P,&Q);
    nr=N/LEN+(N%LEN!=0);
    a=a1;
    b=b1;
    for(int i=1;i<=nr;i++)
    {
        int start=LEN*(i-1)+1;
        int finish=min(LEN*i,N);
        Pr[i]=1;
        for(int j=start;j<=finish;j++)
        {
            apr=a;
            bpr=b;
            val[j-start+1]=gval(a,b,j);
            a=A(apr,bpr);
            b=B(apr,bpr);
            Pr[i]=(1LL*Pr[i]*val[j-start+1])%Q;
        }
    }
    a=a1;
    b=b1;
    long long rez=0;
    for(int i=1;i<=nr;i++)
    {
        int start=LEN*(i-1)+1;
        int finish=min(LEN*i,N);
        st[0]=1;
        for(int j=start;j<=finish;j++)
        {
            apr=a;
            bpr=b;
            val[j-start+1]=gval(a,b,j);
            a=A(apr,bpr);
            b=B(apr,bpr);
            st[j-start+1]=(1LL*st[j-start]*val[j-start+1])%Q;
        }
        int pext=1;
        for(int j=1;j<=nr;j++)
            if(j!=i)
                pext=(1LL*pext*Pr[j])%Q;
        int pin=1;
        for(int j=finish;j>=start;j--)
        {
            long long produs=(1LL*((1LL*pin*st[j-start])%Q)*pext)%Q;
            rez=rez^produs;
            pin=(1LL*pin*val[j-start+1])%Q;
        }
    }
    fprintf(g,"%lld",rez);
    fclose(f);
    fclose(g);
    return 0;
}
