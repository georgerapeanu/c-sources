#include <cstdio>
#define ULL unsigned long long
using namespace std;
FILE *f=fopen("pic.in","r");
FILE *g=fopen("pic.out","w");
int N;
ULL V[55][55];
ULL C[55][55];
int cer;
int nvl,a,maxim;
ULL risipa;
ULL st,dr;
bool ok(ULL val)
{
    risipa=0;
    for(int i=1;i<=N;i++)
        for(int j=1;j<=N;j++)
            C[i][j]=0;
    C[1][1]=val;
    for(int i=1;i<N;i++)
    {
        for(int j=1;j<=i;j++)
        {
            if(C[i][j]<V[i][j])
                return 0;
            ULL r=C[i][j]-V[i][j];
            C[i][j]=V[i][j];
            C[i+1][j]+=r/2+r%2;
            C[i+1][j+1]+=r/2;
        }
    }
    for(int j=1;j<=N;j++)
    {
        if(C[N][j]<V[N][j])
            return 0;
        risipa+=C[N][j]-V[N][j];
    }
    return 1;
}
int main()
{
    fscanf(f,"%d%d",&cer,&N);
    if(cer==1)
    {
        for(int i=1;i<=N;i++)
            for(int j=1;j<=i;j++)
                {fscanf(f,"%llu",&V[i][j]);V[i][j]+=V[i][j-1];}
        nvl=N;
        while(nvl)
        {
            if(V[nvl][nvl]>=maxim)
            {
                maxim=V[nvl][nvl];
                a=nvl;
            }
            nvl--;
        }
        fprintf(g,"%d",a);
    }
    else
    {
        for(int i=1;i<=N;i++)
            for(int j=1;j<=i;j++)
                fscanf(f,"%llu",&V[i][j]);
        st=1;
        dr=-2;
        while(st<dr)
        {
            ULL mid=(st+dr)/2;
            if(ok(mid))
            {
                dr=mid;
            }
            else
            {
                st=mid+1;
            }
        }
        ok(st);
        fprintf(g,"%llu %llu",st,risipa);
    }
    return 0;
}
