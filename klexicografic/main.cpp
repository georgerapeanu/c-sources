#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("klexico.in","r");
FILE *g=fopen("klexico.out","w");
int K,D[100010],i,N,j;
char A[100010];
int main()
{
    fscanf(f,"%d %d\n",&N,&K);
    fgets(A+1,100005,f);
    D[N+1]=1;
    D[N+2]=1;
    A[N+1]=A[N+2]='z'-A[N]+'a'-1;
    for(i=N;i>N-K+1;i--)
        {
            D[i]=(D[i+1]*26)%666013;
            D[N-K+1]+=('z'-A[i-1])*D[i];
            D[N-K+1]%=666013;
        }
    D[N-K+1]+='z'-A[N];
    D[N-K+1]%=666013;
    for(i=N-K;i>=1;i--)
    {
         D[i] =( ('z' - A[i]) * D[i + 1] + D[i + 1] - ('z' - A[i + K]) * D[i + K + 1] )%666013;
    }
    if(D[1]<0)
        D[1]+=666013;
    fprintf(g,"%d",D[1]);
    fclose(f);
    fclose(g);
    return 0;
}
