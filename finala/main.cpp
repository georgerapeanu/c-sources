#include <cstdio>
using namespace std;
FILE *f=fopen("finala.in","r");
FILE *g=fopen("finala.out","w");
int N,M,K;
int main()
{
    fscanf(f,"%d %d %d",&N,&M,&K);
    if((N+M+K-1)/K<=M/2)
        fprintf(g,"%d",(N+M+K-1)/K);
    else
        fprintf(g,"%d",0);
    fclose(f);
    fclose(g);
    return 0;
}
