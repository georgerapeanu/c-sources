#include <cstdio>
using namespace std;
FILE *f=fopen("numar1.in","r");
FILE *g=fopen("numar1.out","w");
int N,a,i,suma,b,c;
bool fr[10],ok;
int main()
{
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d",&b);
        if(a<=b)
        {
            suma+=b;
        }
        else
        {
            while(suma>9)
            {
                while(suma)
                {
                    c+=suma%10;
                    suma/=10;
                }
                suma=c;
                c=0;
            }
            fr[suma]=1;
            suma=b;
        }
        a=b;
    }
     while(suma>9)
            {
                while(suma)
                {
                    c+=suma%10;
                    suma/=10;
                }
                suma=c;
                c=0;
            }
            fr[suma]=1;
            suma=b;
    i=9;
    while(i>=0)
    {
        if(!fr[i])
        {
            ok=1;
            fprintf(g,"%d",i);
        }
        i--;
    }
    if(!ok)
        fprintf(g,"-1");
        fclose(f);
        fclose(g);
    return 0;
}
