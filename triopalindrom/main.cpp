#include <cstdio>
#include <cstring>
using namespace std;
FILE *f=fopen("triopalindrom.in","r");
FILE *g=fopen("triopalindrom.out","w");
int N,k,nr,rez,i;
char C[5005];
int main()
{
    fgets(C+1,5005,f);
    N=strlen(C+1);
    for(k=1;k<=N/3;k++)
    {
        nr=0;
        for(i=1;i+k<=N;i++)
        {
            if(C[i]!=C[i+k])
                nr=0;
            else
                nr++;
            if(nr>=2*k)
                rez++;
        }
    }
    fprintf(g,"%d",rez);
    fclose(f);
    fclose(g);
    return 0;
}
