#include <cstdio>
using namespace std;
FILE *f=fopen("scaune.in","r");
FILE *g=fopen("scaune.out","w");
int i,N,prod=1;
int main()
{
    fscanf(f,"%d",&N);
    for(i=3;i<=2*N-1;i+=2)
        prod=(prod*(i%30103))%30103;
    fprintf(g,"%d",prod);
    fclose(f);
    fclose(g);
    return 0;
}
