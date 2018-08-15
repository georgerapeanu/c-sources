#include <cstdio>
using namespace std;
FILE *f=fopen("pietre.in","r");
FILE *g=fopen("pietre.out","w");
int L[2000006];
int T,N,M;
int val=0;
int main()
{
    for(int i=0;i<=1000000;i++)
    {
        if(!L[i])
        {
            L[i]=i+val;
            L[i+val]=i;
            val++;
        }
    }
    fscanf(f,"%d",&T);
    while(T--)
    {
        fscanf(f,"%d %d",&N,&M);
        if(L[N]==M)fputc('2',g);
        else fputc('1',g);
        fputc('\n',g);
    }
    fclose(f);
    fclose(g);
    return 0;
}
