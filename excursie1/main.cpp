#include <cstdio>
using namespace std;
FILE *f=fopen("excursie1.in","r");
FILE *g=fopen("excursie1.out","w");
int N,suma;
int main()
{
    fscanf(f,"%d",&N);
    if((N%3)&1==1)
        fprintf(g,"NU");
    else
    {
        suma=N*(N+1)/6;

    }
    fclose(f);
    fclose(g);
    return 0;
}
