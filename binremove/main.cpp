#include <cstdio>
using namespace std;
FILE *f=fopen("binremove.in","r");
FILE *g=fopen("binremove.out","w");
int V[50005];
int N,M,nr,i,val;
int main()
{
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d",&V[i]);
    }
    fscanf(f,"%d",&M);
    while(M--)
    {
        fscanf(f,"%d",&nr);
        for(i=N-nr;i<=N;i++)
        {
            V[i]=V[i+1];
        }
        N--;
        val=0;
        for(i=1;i<=N;i++)
        {
            val+=V[i]*(i&1 ? -1:1);
        }
        val%=3;
        fprintf(g,"%d\n",!val);
    }
    fclose(f);
    fclose(g);
    return 0;
}
