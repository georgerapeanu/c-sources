#include <cstdio>
using namespace std;
int n,nr,x,y,z,nr0,i;
FILE *f=fopen("fibo1.in","r"),*g=fopen("fibo1.out","w");
int main()
{
    fscanf(f,"%d",&n);
    fclose(f);
    if(n%2==0)
    {
        nr=(n-2)/2;
        nr0=nr+2;
        fprintf(g,"0\n%d %d",nr,nr+2);
    }
    else
    {
        nr=(n-1)/2;
        nr0=nr+1;
        fprintf(g,"1\n%d %d",nr,nr+1);
    }
    i=1;
    x=y=0;
    z=1;
    while(i<=n)
    {
        if(i==nr)
        {
            fprintf(g,"\n%d ",z);
        }
        else if(i==nr0)
        {
            fprintf(g,"\n%d",z);
        }
        else if(i==n)
        {
            fprintf(g,"\n%d",z);
        }
        x=y;
        y=z;
        z=(x+y)%46337;
        i++;
    }
    fclose(g);
    return 0;
}
