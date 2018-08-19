#include <cstdio>
#include <cstring>
using namespace std;
FILE *f=fopen("sr.in","r");
FILE *g=fopen("sr.out","w");
char A[100005];
char B[100005];
int i,j,N,M;
int main()
{
    fgets(A+1,100005,f);N=strlen(A+1);
    if(A[N]=='\n')
        N--;
    fgets(B+1,100005,f);M=strlen(B+1);
        if(B[M]=='\n')
            M--;
    j=1;
    i=1;
    while(j<=M)
    {
        if(A[i]==B[j])
        {fprintf(g,"%d ",i);j++;}
        i++;
    }
    fclose(f);
    fclose(g);
    return 0;
}
