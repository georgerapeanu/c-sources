#include <cstdio>
using namespace std;
FILE *f=fopen("cutie1.in","r");
FILE *g=fopen("cutie1.out","w");
int c,nr;
int N,M,K,T,val;
int D[10005];
int B[10005];
int i,j,l;
int main()
{
    fscanf(f,"%d",&T);
    for(i=1;i<=T;i++)
    {
        fscanf(f,"%d %d %d",&N,&K,&M);
        nr=0;
        c=0;
        for(j=1;j<=K;j++)
        {
            fscanf(f,"%d",&val);
            D[j]=val;
        }
        l=1;
          for(j=1;j<=M;j++)
        {
            fscanf(f,"%d",&val);
            while(D[l]<=val&&D[l+1]<=val&&l<=K)
                l++;
            if(D[l]>val)
                c+=(D[l]-val);
            else if(l==K+1)
                c+=(val-D[l-1]);
           else if((val-D[l])%2==(D[l+1]-val)%2)
                c=c+(val-D[l]);
            else
                nr++;
        }
        if(nr==0)
        {
            if(c%2==0)
                fprintf(g,"0");
            else
                fprintf(g,"1");
        }
        else if(c==0)
        {
            if(nr%2==1)
                fprintf(g,"1");
            else
                fprintf(g,"0");
        }
        else if(nr%2==1)
        {
           // if(c==1)
                fprintf(g,"1");
           // else if(c%2==0)
           //     fprintf(g,"1");
           // else
             //   fprintf(g,"0");
        }
        else if(nr%2==0)
        {
            if(c%2==0)
                fprintf(g,"0");
            else
                fprintf(g,"1");
        }
    }
    fclose(f);
    fclose(g);
    return 0;
}
