#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("noroc.in","r");
FILE *g=fopen("noroc.out","w");
int X,M;
int main()
{
    fscanf(f,"%d %d",&X,&M);
    fprintf(g,"%.7f",max(1-(double)X/M,(double)0));
    fclose(f);
    fclose(g);
    return 0;
}
