#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("sumfact.in","r");
FILE *g=fopen("sumfact.out","w");
long long fact[20];
long long C[20],P;
int *tmp;
int i;
long long N;
int main()
{
    fact[0]=1;
    for(i=1;i<=13;i++)
        fact[i]=fact[i-1]*i;
    fscanf(f,"%lld",&N);
    P=1;
    while(fact[P]<=N)
        P++;
    P--;
    if(fact[P+1]==N)
        P++;
    for(i=P;i>0;i--)
    {
        C[i]=N/fact[i];
        N%=fact[i];
    }
    fprintf(g,"%lld\n",P);
    for(i=1;i<=P;i++)
        fprintf(g,"%lld\n",C[i]);
    fclose(f);
    fclose(g);
    return 0;
}
