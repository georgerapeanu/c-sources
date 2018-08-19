#include <cstdio>
using namespace std;
FILE *f=fopen("maxunice.in","r");
FILE *g=fopen("maxunice.out","w");
long long N,val,i;
int main()
{
    val=1;
    fscanf(f,"%lld",&N);
    while(val<=N)
    {
        N-=val;
        val++;
    }
    fprintf(g,"%lld\n",val-1);
    for(i=1;i<val;i++)
        fprintf(g,"%lld\n",i+(val-i<=N ? 1:0));
    fclose(f);
    fclose(g);
    return 0;
}
