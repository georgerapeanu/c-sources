#include <cstdio>
#include <vector>
#include <cstring>
using namespace std;
FILE *f=fopen("zuma.in","r");
FILE *g=fopen("zuma.out","w");
int x,i,N,j,k;
char c[300],d,rez[300];
int main()
{
    fscanf(f,"%d\n",&x);
    x=x-1;
    fgets(c,300,f);
    N=strlen(c);
    if(c[x-1]==c[x]&&c[x]==c[x+1])
    {
        i=x;
        j=x+1;
        while(c[i]==c[j]&&(c[j]==c[j+1]||c[i]==c[i-1]))
        {
            d=c[i];
            while(c[i]==d)
            {
                i--;
            }
            while(c[j]==d)
            {
                j++;
            }
        }
        for(k=0;k<=i;k++)
                rez[k]=c[k];
        for(k=j;k<N;k++)
        {
            rez[i+k-j+1]=c[k];
        }
    }
    else
    {
       for(i=0;i<N;i++)
        rez[i]=c[i];
    }
    fputs(rez,g);
    fclose(f);
    fclose(g);
    return 0;
}
