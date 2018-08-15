#include <cstdio>
using namespace std;
double e,rez;
int n,i,j;
FILE *f,*g;
int main()
{
    f=fopen("zaruri.in","r");
    fscanf(f,"%d",&n);
    fclose(f);
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=6;j++)
        {
            if(e>=j)
            {
                rez+=e;
            }
            else
            {
                rez+=j;
            }
        }
        rez/=6;
        e=rez;
        rez=0;
    }
    g=fopen("zaruri.out","w");
    fprintf(g,"%.8f",e);
    fclose(g);
    return 0;
}
