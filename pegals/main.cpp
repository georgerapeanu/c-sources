#include <cstdio>
using namespace std;
FILE *f=fopen("pegals.in","r");
FILE *g=fopen("pegals.out","w");
int N;
int main()
{
    fscanf(f,"%d",&N);
    if(N%2==0)
        fprintf(g,"3\n1 %d %d",(N/2)-1,N);
    else
        fprintf(g,"3\n1 %d %d",N/2,N-1);
    fclose(f);
    fclose(g);
    return 0;
}
