#include <cstdio>
#include <unordered_set>
using namespace std;
FILE *f=fopen("numcol.in","r");
FILE *g=fopen("numcol.out","w");
char c[33]="0123456789ABCDEF";
int N;
int main()
{
    fscanf(f,"%d",&N);
    for(int i=1,ind=-1;i<=N;i++)
    {
        if((i&(i-1))==0) ind++;
        fputc(c[ind],g);
    }
    fclose(f);
    fclose(g);
    return 0;
}
