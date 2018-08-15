#include <cstdio>
#include <bitset>
using namespace std;
FILE *f=fopen("coins.in","r");
FILE *g=fopen("coins.out","w");
bitset<(1<<22)> D;
int N;
int z(int conf)
{
    if(!conf) return 0;
    return (conf&1)+z(conf>>1);
}
int main()
{
    D[0]=0;
    for(int i=1;i<(1<<22);i++)
    {
        if((i&(i+1))==0)
        {
            D[i]=1;continue;
        }
        int l0=-1;
        for(int j=0;j<22;j++)
        {
            if((i&(1<<j)))
            {
                if(l0>=0)
                    if(!D[i-(1<<j)+(1<<l0)])
                        {D[i]=1;break;}
            }
            else l0=j;
        }
    }
    fscanf(f,"%d",&N);
    int rez=0;
    for(int i=1;i<=N;i++)
    {
        int conf=0,val;
        for(int j=0;j<22;j++)
        {
            fscanf(f,"%d",&val);
            conf=conf+(val<<j);
        }
        if(D[conf])
            rez+=z(conf);
    }
    fprintf(g,"%d",rez);
    fclose(f);
    fclose(g);
    return 0;
}
