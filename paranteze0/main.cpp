#include <cstdio>
using namespace std;
FILE *f,*g;
int i,j,n,l,cap0,cap2,v[501],x[501];
bool corect=1;
int main()
{
    f=fopen("paranteze.in","r");
    fscanf(f,"%d",&n);
    g=fopen("paranteze.out","w");
    for(i=1;i<=n;i++)
    {
        fscanf(f,"%d",&l);
        for(j=1;j<=l;j++)
        fscanf(f,"%d",&x[j]);
        corect=1;
        j=1;
        cap0=cap2=0;
        while(corect&&j<=l)
        {
            if(x[j]==0)
            {
                v[j]=cap0;
                cap0=j;
            }
            else if(x[j]==2)
            {
                v[j]=cap2;
                cap2=j;
            }
            else if(x[j]==1)
            {
                if(cap0==0) corect=0;
                else if(cap2>cap0) corect=0;
                else cap0=v[cap0];
            }
            else
            {
                if(cap2==0) corect=0;
                else if(cap0>cap2) corect=0;
                else cap2=v[cap2];
            }
            j++;
        }
        if(!(cap0==0&&cap2==0))
        corect=0;
        fprintf(g,"%d\n",corect);
    }
    fclose(f);
    fclose(g);
    return 0;
}