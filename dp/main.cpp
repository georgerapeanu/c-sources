#include <cstdio>
#include <cstring>
using namespace std;
char c[200];
FILE *f=fopen("dp.in","r");
FILE *g=fopen("dp.out","w");
int N,i,st,nr;
int main()
{
    fgets(c+1,200,f);
    c[0]='.';
    N=strlen(c);
    i=1;
    while(i<N)
    {
        st=0;
        nr=0;
        fprintf(g,"(");
        while(c[i]=='0')
        {
                i++;
                st++;
                fprintf(g,"0");
        }
        while(nr<=st&&i<N)
        {
            if(c[i]=='0')
                {
                    nr++;
                    if(nr<=st)
                    fprintf(g,"0");
                    else i--;
                }
            else
                fprintf(g,"1");
            i++;
        }
        fprintf(g,")");
    }
    fclose(f);
    fclose(g);
    return 0;
}
