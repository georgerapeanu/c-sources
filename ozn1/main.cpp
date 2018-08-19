#include <cstdio>
using namespace std;
FILE *f=fopen("ozn1.in","r");
FILE *g=fopen("ozn1.out","w");
int x1,y1,nr,N,K;
int x2,y2;
int V[2000005];
int i;
int main()
{
    fscanf(f,"%d %d",&N,&K);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d %d %d %d %d",&x1,&y1,&x2,&y2,&nr);
        V[x1]+=nr;
        V[x2+1]-=nr;
    }
    for(i=1;i<=2000001;i++)
        V[i]+=V[i-1];
    for(i=1;i<=K;i++)
    {
        fscanf(f,"%d",&nr);
        fprintf(g,"%d\n",V[nr]);
    }
    fclose(f);
    fclose(g);
    return 0;
}
