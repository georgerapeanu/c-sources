#include <cstdio>
using namespace std;
FILE *f=fopen("stramosi.in","r");
FILE *g=fopen("stramosi.out","w");
int D[250005][20];
int N,M,P,Q,rez;
int main()
{
    fscanf(f,"%d%d",&N,&M);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d",&P);
        D[i][0]=P;
    }
    for(int i=1;i<=N;i++)
    {
        for(int p=1;p<=18;p++)
            D[i][p]=D[D[i][p-1]][p-1];
    }
    for(int i=1;i<=M;i++)
    {
        fscanf(f,"%d%d",&P,&Q);
        rez=P;
        int nr=0;
        while(Q)
        {
            if(Q&1)
            {
                rez=D[rez][nr];
            }
            nr++;
            Q>>=1;
        }
        fprintf(g,"%d\n",rez);
    }
    fclose(f);
    fclose(g);
    return 0;
}
