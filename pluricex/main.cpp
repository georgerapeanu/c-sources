#include <cstdio>
using namespace std;
FILE *f=fopen("pluricex.in","r");
FILE *g=fopen("pluricex.out","w");
int N,K,D;
int V[30];
int A[10];
void btr(int pas,int config)
{
    if(pas>K)
    {
        if(config==(1<<D)-1)
        {
            for(int i=1;i<=K;i++) fprintf(g,"%d ",A[i]);
            fputc('\n',g);
        }
        return ;
    }
    for(int i=A[pas-1]+1;i<=N-K+pas;i++)
    {
        A[pas]=i;
        btr(pas+1,config|V[i]);
    }
}
int main()
{
    fscanf(f,"%d%d%d",&N,&K,&D);
    for(int i=1;i<=N;i++)
    {
        int nr,val;
        fscanf(f,"%d",&nr);
        for(int j=1;j<=nr;j++)
        {
            fscanf(f,"%d",&val);
            V[i]|=(1<<(val-1));
        }
    }
    btr(1,0);
    fclose(f);
    fclose(g);
    return 0;
}
