#include <cstdio>
using namespace std;
FILE *f=fopen("chocolate.in","r");
FILE *g=fopen("chocolate.out","w");
int N,M,X,Y;
int T;
int main()
{
    fscanf(f,"%d",&T);
    while(T--)
    {
        fscanf(f,"%d %d %d %d",&N,&M,&X,&Y);
        if(((X-1)^(Y-1)^(N-X)^(M-Y))==0)
            fputs("0\n",g);
        else
            fputs("1\n",g);
    }
    fclose(f);
    fclose(g);
    return 0;
}
