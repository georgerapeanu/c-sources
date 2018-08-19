#include <cstdio>
using namespace std;
FILE *f=fopen("xerox.in","r");
FILE *g=fopen("xerox.out","w");
int T,N,dx,dy,M;
int xo;
int main()
{
    fscanf(f,"%d",&T);
    while(T--)
    {
        xo=0;
        fscanf(f,"%d%d%d",&N,&dx,&dy);
        for(int i=1;i<=N;i++)
        {
            fscanf(f,"%d",&M);for(int j=1;j<=M;j++)fscanf(f,"%d %d",&dx,&dy);
            xo^=M;
        }
        fprintf(g,"%d\n",(xo!=0));
    }
    fclose(f);
    fclose(g);
    return 0;
}
