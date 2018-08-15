#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("expresie.in","r");
FILE *g=fopen("expresie.out","w");
long long N,i,j;
long long V[1005];
long long M[3][1005];
int main()
{
    fscanf(f,"%lld",&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%lld",&V[i]);
        M[0][i]=M[0][i-1]+V[i];
          if(M[1][i-1]+V[i]>M[0][i-2]+V[i-1]*V[i])
            M[1][i]=M[1][i-1]+V[i];
        else
            M[1][i]=M[0][i-2]+V[i-1]*V[i];
        M[2][i]=M[2][i-1]+V[i];
        if(M[2][i]<M[1][i-2]+V[i-1]*V[i])
            M[2][i]=M[1][i-2]+V[i-1]*V[i];
        if(M[2][i]<M[0][i-3]+V[i-2]*V[i-1]*V[i])
            M[2][i]=M[0][i-3]+V[i-2]*V[i-1]*V[i];
    }
    fprintf(g,"%lld",M[2][N]);
    fclose(f);
    fclose(g);
    return 0;
}
