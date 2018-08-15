#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("elimin.in","r");
FILE *g=fopen("elimin.out","w");
long long N,M,R,C,s,maxim,TS,i,j;
long long c[7300];
long long r[7300];
long long V[7300];
long long S[7300];
void eval()
{
    int sum[7300];
    for(int i=1;i<=M;i++)
    {
        sum[i]=c[i];
        for(int j=1;j<=R;j++)
        {
            sum[i]-=S[V[j]*M+i-M];
        }
    }
    sort(sum+1,sum+1+M);
    int tmps=s;
    for(int i=1;i<=C;i++)
        tmps+=sum[i];
    if(TS-tmps>maxim)
        maxim=TS-tmps;
}
void getVec(int nr,int left)
{
    if(nr<=R)
    {
        for(int i=left;i<=N-R+nr;i++)
        {
            V[nr]=i;
            s+=r[i];
            getVec(nr+1,i+1);
            s-=r[i];
        }
    }
    else
    {
        eval();
    }
}
int main()
{
    fscanf(f,"%lld %lld %lld %lld",&N,&M,&R,&C);
    for(i=1;i<=N*M;i++)
    {
        fscanf(f,"%lld",&S[i]);
        TS+=S[i];
        c[(i-1)%M+1]+=S[i];
        r[(i-1)/M+1]+=S[i];
    }
    getVec(1,1);
    fprintf(g,"%lld",maxim);
    fclose(f);
    fclose(g);
    return 0;
}
