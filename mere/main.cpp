#include <cstdio>
using namespace std;
FILE *f=fopen("mere.in","r");
FILE *g=fopen("mere.out","w");
int N,K,T;
int main()
{
    fscanf(f,"%d",&T);
    while(T)
    {
        fscanf(f,"%d%d",&N,&K);
        if((N/K)%2==0){
            if(N<K||N%K==0)
                fputs("Remiza\n",g);
            else fputs("Santa Klaus\n",g);
        }
        else fputs("Santa Klaus\n",g);
        T--;
    }
    fclose(f);
    fclose(g);
    return 0;
}
