#include <cstdio>
#include <bitset>
using namespace std;
FILE *f=fopen("perioada2.in","r");
FILE *g=fopen("perioada2.out","w");
int N,nr;
char C[10000005];
int  F[10000005];
int main()
{
    fscanf(f,"%d\n",&N);
    fread(C+1,1,N,f);
    for(int i=2;i<=N;i++)
    {
        int k=F[i-1];
        while(k&&C[k+1]!=C[i])k=F[k];
        if(C[k+1]==C[i])k++;
        F[i]=k;
    }
    for(int i=F[N];i;i=F[i])nr+=(N%(N-i)==0);
    fprintf(g,"%d",nr);
    fclose(f);
    fclose(g);
    return 0;
}
