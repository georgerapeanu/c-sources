#include <cstdio>
using namespace std;
FILE *f=fopen("cartonase.in","r");
FILE *g=fopen("cartonase.out","w");
int T,N;
char c;
int main()
{
    fscanf(f,"%d",&T);
    while(T--)
    {
        fscanf(f,"%d ",&N);
        int rez=0;
        for(int i=1;i<=N;i++)
        {
            fscanf(f,"%c ",&c);
            if(c=='R')rez^=i;
        }
        if(rez)fputs("DA\n",g);
        else fputs("NU\n",g);
    }
    fclose(f);
    fclose(g);
    return 0;
}
