#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
using namespace std;
FILE *f=fopen("ecuatii.in","r");
FILE *g=fopen("ecuatii.out","w");
short S=1,s=1;
int nr1,nr2,coef,j,M;
char c[260],rez[260];
short N,i;
double x;
int main()
{
    fscanf(f,"%hd\n",&N);
    for(i=1;i<=N;i++)
    {
        fgets(c,260,f);
        M=strlen(c);
        S=s=1;
        nr1=coef=0;
        for(j=0;j<M-1;j++)
        {
            if(c[j]=='=') {S=-1;s=1;}
            else if(c[j]=='-') s=-1;
            else if(c[j]=='+') s=1;
            else
            {
                nr2=0;
                while(isdigit(c[j])&&j<M-1)
                    {nr2=nr2*10+c[j]-'0';j++;}
                if(c[j]=='x'){nr2=max(1,nr2);coef+=S*s*nr2;}
                else nr1+=S*s*nr2;
                 if(c[j]=='=') {S=-1;s=1;}
            else if(c[j]=='-') s=-1;
            else if(c[j]=='+') s=1;
            }
        }
        ///nr1+coef*x=0
        ///x=-nr1/coef
        if(coef==0)
        {
            if(nr1==0)
                fprintf(g,"infinit\n");
            else
                fprintf(g,"imposibil\n");
        }
        else
        {
                x=double(-nr1)/coef;
                fprintf(g,"%.4f\n",x);
        }
    }
    fclose(f);
    fclose(g);
    return 0;
}
