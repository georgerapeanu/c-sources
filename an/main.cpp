#include <cstdio>
using namespace std;
FILE *f=fopen("and.in","r");
FILE *g=fopen("and.out","w");
int V,frecv[100],N,i,b,maxim,bitmaxim,j;
int main()
{
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d",&V);
        b=0;
        while(V)
        {
            if(V%2==0)
                frecv[b]=0;
            else
            {
                frecv[b]++;
                if(frecv[b]>maxim)
                    maxim=frecv[b];
            }
            b++;
            V/=2;
        }
        if(b>=bitmaxim)
            bitmaxim=b;
        else
            for(j=b;j<=bitmaxim;j++)
            frecv[j]=0;
    }
    fprintf(g,"%d",maxim);
    fclose(f);
    fclose(g);
    return 0;
}
