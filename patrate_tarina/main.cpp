#include <cstdio>
#include <cmath>
using namespace std;
FILE *f=fopen("patrate.in","r");
FILE *g=fopen("patrate.out","w");
double X,Y,L,H,rap,i;
long long rez;
int main()
{
    fscanf(f,"%lf %lf %lf %lf",&L,&H,&X,&Y);
    rap=X/Y;
    rez=ceil(X/L)+ceil(Y/H)-1;
    if(X/L<=Y/H)
    {
        for(i=1;i<=X/L;i++)
        {
            if(((1/rap)*L*i/H)==int((1/rap)*L*i/H))
                rez--;
        }
    }
    else
    {
        for(i=1;i<=Y/H;i++)
        {
            if(rap*H*i/L==int(rap*H*i/L))
                rez--;
        }
    }
    fprintf(g,"%lld",rez);
    fclose(f);
    fclose(g);
    return 0;
}