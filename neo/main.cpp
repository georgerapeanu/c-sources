#include <cstdio>
using namespace std;
FILE *f=fopen("neo.in","r");
FILE *g=fopen("neo.out","w");
int produs=1,st,dr,i,N,x,y;
long long maxim,prneg,prpoz;
long long V[10005];
int main()
{
    fscanf(f,"%d",&N);
    V[0]=1;
    y=0;
    prpoz=1;
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%lld",&V[i]);
        V[i]*=V[i-1];
        if(V[i]<0)
        {
            if(prneg)
            {
                if(maxim<V[i]/prneg)
                    {st=x+1;maxim=V[i]/prneg;dr=i;}
            }
            else
                {x=i;prneg=V[i];}
        }
        else if(V[i]>0)
        {
            if(prpoz)
            {
                if(maxim<V[i]/prpoz)
                {
                    st=y+1;
                    dr=i;
                    maxim=V[i]/prpoz;
                }
            }
            else
            {
                y=i;
                prpoz=V[i];
            }
        }
        else
        {
            prneg=0;
            x=0;
            y=i;
            prpoz=1;
            V[i]=1;
        }
    }
    fprintf(g,"%lld\n%d %d",maxim,st,dr);
    fclose(f);
    fclose(g);
    return 0;
}
