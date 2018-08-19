#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("kds.in","r");
FILE *g=fopen("kds.out","w");
int A[10005];
int bst[10005];
int tmp[10005];
int N,K;
int rez=(1<<30);
int sum;
int solve(int st,int dr,int K)
{
    for(int i=0;i<=10000;i++) bst[i]=0;
    for(int j=1;j<=K;j++)
    {
        tmp[st+j-2]=(1<<30);
        for(int i=st+j-1;i<=dr;i++)
            if(tmp[i-1]<bst[i-2]+A[i])
                tmp[i]=tmp[i-1];
            else
                tmp[i]=bst[i-2]+A[i];
        for(int i=st-1;i<=dr;i++)
            bst[i]=tmp[i];
    }
    return bst[dr];
}
int main()
{
    fscanf(f,"%d%d",&N,&K);
    for(int i=1;i<=N;i++)
        fscanf(f,"%d",&A[i]),sum+=A[i];
    rez=min(solve(2,N,K),solve(3,N-1,K-1)+A[1]);
    fprintf(g,"%d",sum-rez);
    fclose(f);
    fclose(g);
    return 0;
}
