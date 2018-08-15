#include <cstdio>
#include <cstdlib>
using namespace std;
FILE *f=fopen("submultimi.in","r");
FILE *g=fopen("submultimi.out","w");
int nrl,N,A,K,nr;
void bt(int u,int subm,int S)
{
    if(u==N||u==-1)
    {
        if(S%2==0&&subm!=0)
        {
            nr++;
            if(nr==A)
            {
                for(int i=1;i<=N;i++)
                    if((subm&(1<<i))!=0)
                        fprintf(g,"%d ",i);
                fprintf(g,"\n");
                fscanf(f,"%d",&A);
                K--;
                if(K==0)
                    exit(0);
            }
        }
    }
    else
    {
        bt(-1,subm,S);
        for(int i=u+1;i<=N;i++)
            bt(i,subm+(1<<i),S+i);
    }
}
int main()
{
    fscanf(f,"%d %d\n%d",&N,&K,&A);
    bt(0,0,0);
    return 0;
}
