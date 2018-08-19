#include <cstdio>
using namespace std;
FILE *f=fopen("pagini.in","r");
FILE *g=fopen("pagini.out","w");
short c;
int nr,rez,tmp=9,i;
int main()
{
    fscanf(f,"%hd %d",&c,&nr);
    if(!(c-1))
    {
        i=1;
        while(nr>=tmp)
        {
         rez=rez+tmp*i;
         nr-=tmp;
         tmp*=10;
         i++;
        }
        rez=rez+nr*i;
    }
    else
    {
        i=1;
        while(nr>=tmp*i)
        {
            rez=rez+tmp;
            nr-=tmp*i;
            tmp=tmp*10;
            i++;
        }
        rez=rez+(nr/i);
    }
    fprintf(g,"%d",rez);
    return 0;
}
