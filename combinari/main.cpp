#include <cstdio>
using namespace std;
FILE *f=fopen("combinari.in","r");
FILE *g=fopen("combinari.out","w");
int N,K,rez[20];
int comb(int pas,int l,int maxim)
{
    if(pas==maxim+1)
    {
        for(int i=1;i<=maxim;i++)
            fprintf(g,"%d ",rez[i]);
        fprintf(g,"\n");
    }
    else
    {
       for(int i=rez[pas-1]+1;i<=l;i++)
       {
           rez[pas]=i;
           comb(pas+1,l,maxim);
       }
    }
}
int main()
{
    fscanf(f,"%d %d",&N,&K);
    comb(1,N,K);
    fclose(f);
    fclose(g);
    return 0;
}
