#include <cstdio>
using namespace std;
FILE *f=fopen("concurs1.in","r");
FILE *g=fopen("concurs1.out","w");
int V[50005];
int val[50005];
int i,j,N;
int main()
{
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d",&val[i]);
        if(val[i]>N-i)
        {
            fprintf(g,"NU ARE SOLUTIE");
            return 0;
        }

    }
    for(i=N;i>0;i--)
    {
        for(j=N-i+1;j>val[i]+1;j--)
        {
            V[j]=V[j-1];
        }
        V[val[i]+1]=i;

    }
    for(i=1;i<=N;i++)
    {
        val[V[i]]=i;
    }
    for(i=1;i<=N;i++)
        fprintf(g,"%d ",val[i]);
    fclose(f);
    fclose(g);
    return 0;
}
