#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("snowball.in","r");
FILE *g=fopen("snowball.out","w");
int st=1,dr=0;
int A[500005];
int B[10005];
int poz[10005];
int unde[10005];
int N,M;
int val;
long long nrmod,lmax;
int main()
{
    fscanf(f,"%d %d",&M,&N);
    for(int i=1;i<=M;i++)
        {fscanf(f,"%d",&B[i]);poz[B[i]]=i;}
    for(int i=1;i<=N;i++)
        fscanf(f,"%d",&A[i]);
    fill_n(unde+1,M,N+1);
    for(int i=N;i;i--)
    {
        if(poz[A[i]])
        {
            if(A[i]==B[M])
                unde[M]=i;
            else
                unde[poz[A[i]]]=unde[poz[A[i]]+1];
        }
        lmax=max(1LL*unde[1]-i,lmax);
        nrmod+=unde[1]-i;
    }
    fprintf(g,"%lld %lld",lmax,nrmod);
    fclose(f);
    fclose(g);
    return 0;
}
