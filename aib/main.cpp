#include <cstdio>
#define zeros(x) (x&(x^(x-1)))
using namespace std;
FILE *f=fopen("aib.in","r");
FILE *g=fopen("aib.out","w");
int N;
int M;
int AIB[100005];
void update(int poz,int val)
{
    for(int i=poz;i<=N;i+=zeros(i))
        AIB[i]+=val;
}
int query(int poz)
{
    int sum=0;
    for(int i=poz;i;i-=zeros(i))
        sum+=AIB[i];
    return sum;
}
int main()
{
    fscanf(f,"%d%d",&N,&M);
    for(int i=1;i<=N;i++)
    {
        int val;
        fscanf(f,"%d",&val);
        update(i,val);
    }
    for(int i=1;i<=M;i++)
    {
        int c,a,b;
        fscanf(f,"%d",&c);
        if(c==0){fscanf(f,"%d%d",&a,&b);update(a,b);}
        else if(c==1)
        {
            fscanf(f,"%d%d",&a,&b);
            fprintf(g,"%d\n",query(b)-query(a-1));
        }
        else
        {
            int poz=0,sum=0;
            fscanf(f,"%d",&a);
            for(int j=(1<<16);j;j>>=1)
                if(poz+j<=N&&sum+AIB[poz+j]<=a)
                {
                    sum+=AIB[poz+j];
                    poz+=j;
                }
            if(sum!=a||poz==0) fprintf(g,"-1\n");
            else fprintf(g,"%d\n",poz);
        }
    }
    fclose(f);
    fclose(g);
    return 0;
}
