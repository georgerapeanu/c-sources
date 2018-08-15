#include <cstdio>
using namespace std;
FILE *f=fopen("balulbobocilor.in","r");
FILE *g=fopen("balulbobocilor.out","w");
int v1,v2,D,V,h1,g1,h2,g2;
double rez;
int main()
{
    fscanf(f,"%d",&D);
    rez=D;
    fscanf(f,"%d%d%d",&v1,&h1,&g1);
    fscanf(f,"%d%d%d",&v2,&h2,&g2);
    fscanf(f,"%d",&V);
    rez=V*(rez/(v1+v2));
    fprintf(g,"%.6f",rez);
    fclose(f);
    fclose(g);
    return 0;
}
