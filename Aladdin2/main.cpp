#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("aladdin2.in","r");
FILE *g=fopen("aladdin2.out","w");
int N,M;
int A[10005];
int B[10005];
const int BASE=1000000;
int main()
{
    fscanf(f,"%d %d",&N,&M);
    A[0]=A[1]=1;
    for(int i=1;i<=N;i++)
    {
        int t=0;
        for(int i=1;i<=A[0]||t;i++)
        {
            A[i]=2*A[i]+t;
            t=A[i]/BASE;
            A[i]%=BASE;
            A[0]=max(i,A[0]);
        }
    }
    B[0]=B[1]=1;
    for(int i=1;i<=M;i++)
    {
        int t=0;
        for(int i=1;i<=B[0]||t;i++)
        {
            B[i]=2*B[i]+t;
            t=B[i]/BASE;
            B[i]%=BASE;
            B[0]=max(i,B[0]);
        }
    }
    A[1]-=2;
    int t=0;
    for(int i=1;i<=A[0]||i<=B[0]||t;i++)
    {
        A[i]+=B[i]+t;
        t=A[i]/BASE;
        A[i]%=BASE;
        A[0]=max(A[0],i);
    }
    fprintf(g,"%d",A[A[0]]);
    for(int i=A[0]-1;i;i--)
    {
        int cmod=BASE/10;
        while(cmod>1&&cmod>A[i])
        {
            cmod/=10;
            fputc('0',g);
        }
        fprintf(g,"%d",A[i]);
    }
    fclose(f);
    fclose(g);
    return 0;
}
