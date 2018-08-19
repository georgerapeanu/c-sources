#include <cstdio>
#define VMAX 100000
#define zeros(x) (x&(-x))
using namespace std;
FILE *f=fopen("amedie.in","r");
FILE *g=fopen("amedie.out","w");
int AIB[100005],N,M,Q;
int V[801][801],len;
void u(int pos,int val)
{
    for(int i=pos;i<=VMAX;i+=zeros(i))
        AIB[i]+=val;
}
int q()
{
    int pos=0,nr=0;
    for(int i=(1<<30);i;i>>=1)
        if(pos+i<=VMAX&&nr+AIB[pos+i]<len/2+len%2)
        {
            nr+=AIB[pos+i];
            pos+=i;
        }
    return pos+1;
}
int main()
{
    fscanf(f,"%d %d %d\n",&N,&M,&Q);
    for(int i=1;i<=N;i++)
        for(int j=1;j<=M;j++)
            {fscanf(f,"%d",&V[i][j]);u(V[i][j],1);}
    len=N*M;
    fscanf(f,"\n");
    for(int i=1;i<=Q;i++)
    {
        char t;
        int x;
        fscanf(f,"%c",&t);
        if(t=='L')
        {
            fscanf(f,"%d\n",&x);
            for(int j=1;j<=M;j++)
            {
                if(V[x][j]!=0)
                {
                    u(V[x][j],-1);
                    V[x][j]=0;
                    len--;
                }
            }
        }
        else if(t=='C')
        {
            fscanf(f,"%d",&x);
            for(int j=1;j<=N;j++)
            {
                if(V[j][x]!=0)
                {
                    u(V[j][x],-1);
                    V[j][x]=0;
                    len--;
                }
            }
        }
        else
        {
            fscanf(f,"\n");
            fprintf(g,"%d\n",q());
        }
    }
    fclose(f);
    fclose(g);
    return 0;
}
