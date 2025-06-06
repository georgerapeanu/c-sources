#include <cstdio>
#include <algorithm>
#define er 0.00001
using namespace std;
FILE *f=fopen("radacina.in","r");
FILE *g=fopen("radacina.out","w");
double stval,st,dr,A[10],mid;
long double tmprez;
double rez;
int G,i;
bool ok(double x)
{
    double puteri[10];
    puteri[0]=1;
    for(int i=1;i<=G;i++)
        puteri[i]=puteri[i-1]*x;
    tmprez=0;
    for(i=0;i<=G;i++)
    {
        tmprez+=A[i]*puteri[i];
    }
    if(abs(0-tmprez)<er)
        return 1;
    return 0;
}
int main()
{
    fscanf(f,"%d",&G);
    for(i=0;i<=G;i++)
        fscanf(f,"%lf",&A[i]);
    st=-20;
    dr=20;
    if(ok(st)==1)
    {
        fprintf(g,"%f",st);
            fclose(f);
    fclose(g);
        return 0;
    }
    stval=tmprez;
    while(st<dr)
    {
        mid=(st+dr)/2;
        if(ok(mid)==1)
        {
            fprintf(g,"%f",mid);
                fclose(f);
                fclose(g);
            return 0;
        }
        if(tmprez<0)
        {
            if(stval<0)
            {
                st=mid;
                ok(st);
                stval=tmprez;
            }
            else
            {
                dr=mid;
            }
        }
        else
        {
             if(stval<0)
            {
               dr=mid;
            }
            else
            {
                 st=mid;
                ok(st);
                stval=tmprez;
            }
        }
    }
    fprintf(g,"%f",st);
    fclose(f);
    fclose(g);
    return 0;
}
