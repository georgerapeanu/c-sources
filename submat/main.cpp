#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("submat.in","r");
FILE *g=fopen("submat.out","w");
short N,M,i,j;
int maxim;
short nr;
int V[1005];
short val;
int main()
{
    fscanf(f,"%d %d",&N,&M);
    for(i=1;i<=N;i++)
    {
        nr=0;
        for(j=1;j<=M;j++)
        {
            fscanf(f,"%hd",&val);
            if(val==0)
                nr++;
        }
        V[i]=nr;
    }
    sort(V+1,V+1+N);
    for(i=1;i<=N;i++)
    {
        if(V[i]*(N-i+1)>maxim)
            maxim=V[i]*(N-i+1);
    }
    fprintf(g,"%d",maxim);
    fclose(f);
    fclose(g);
    return 0;
}
