#include <cstdio>
using namespace std;
FILE *f=fopen("ron.in","r");
FILE *g=fopen("ron.out","w");
int k,nrc,nrl,nrs;
int main()
{
    fscanf(f,"%d\n%d %d",&k,&nrl,&nrs);
    while(k>2)
    {
        nrc++;
        k=k-(k/3)*2;
    }
    if(k==2)
    nrc++;
    if(nrl!=nrc&&nrs!=nrc)
        fprintf(g,"O");
    else if(nrl==nrc&&nrs!=nrc)
        fprintf(g,"L");
    else if(nrl!=nrc&&nrs==nrc)
        fprintf(g,"S");
    else
        fprintf(g,"O");
    fclose(f);
    fclose(g);
    return 0;
}
