#include <cstdio>
#include <cstring>
using namespace std;
FILE *f=fopen("palc.in","r");
FILE *g=fopen("palc.out","w");
char C[500];
int i,N,j,x=19000000;
bool ok,corect;
int main()
{
    fgets(C,300,f);
    N=strlen(C);
    N--;
    for(i=0;i<N;i++)
    {
        C[i+N]=C[i];
    }
    for(i=0;i<N;i++)
    {
        corect=1;
        for(j=i;j<=i+N/2-1;j++)
        {
            if(C[j]!=C[i+N-1-j+i])
                corect=0;
        }
        if(corect)
        {
            ok=1;
            if(N-i<x)
                x=i;
        }
    }
    if(ok)
        if(x<N-x)
            fprintf(g,"%d",x);
        else
            fprintf(g,"%d",N-x);
    else
        fprintf(g,"-1");
    fclose(f);
    fclose(g);
    return 0;
}
