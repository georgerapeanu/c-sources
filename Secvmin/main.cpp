#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("secvmin.in","r");
FILE *g=fopen("secvmin.out","w");
int N,M;
int A[100005];
int DP[100005];
int B[100005];
int CX[1000005];
int U[1000005];
int rez=1<<30;
int cate[100005];
int main()
{
    fscanf(f,"%d%d",&N,&M);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d",&A[i]);
    }
    for(int i=1;i<=M;i++)
    {
        fscanf(f,"%d",&B[i]);
        CX[B[i]]=i;
    }
    for(int i=N;i>0;i--)
    {
        DP[i]=DP[U[B[CX[A[i]]+1]]]+U[B[CX[A[i]]+1]]-i;
        cate[i]=cate[U[B[CX[A[i]]+1]]]+1;
        if(DP[i]<=0) DP[i]=1,cate[i]=(CX[A[i]]!=0);
        U[A[i]]=i;
        if(cate[i]==M)
            rez=min(rez,DP[i]);
    }
    if(rez!=(1<<30))
        fprintf(g,"%d",rez);
    else
        fprintf(g,"-1");
    fclose(f);
    fclose(g);
    return 0;
}
