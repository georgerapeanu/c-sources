#include <cstdio>
#include <map>
using namespace std;
FILE *f,*g;
int t,n,m,c[5001],val[7],i,smax,j,k,val0[]={0,1,5,10,50,100,500};
bool ok;
void citire()
{
    for(int i=1;i<=6;i++)
    {
        fscanf(f,"%d",&val[i]);
    }
    fscanf(f,"%d",&n);
    for(int i=1;i<=n;i++)
    {
        fscanf(f,"%d",&c[i]);
    }
}
void afisare()
{
    fprintf(g,ok==1 ? "YES\n":"NO\n");
}
int main()
{
    f=fopen("bancomat.in","r");
    g=fopen("bancomat.out","w");
    fscanf(f,"%d",&t);
    for(i=1;i<=t;i++)
    {
        citire();
        ok=1;
        for(j=1;j<=n&&ok==1;j++)
        {
            for(k=6;k>0;k--)
            {
                if(c[j]/val0[k]>val[k])
                {
                    c[j]-=val0[k]*val[k];
                    val[k]=0;
                }
                else
                {
                    val[k]-=c[j]/val0[k];
                    c[j]%=val0[k];
                }
            }
            if(c[j]!=0)
            ok=0;
        }
        afisare();
    }
    fclose(f);
    fclose(g);
    return 0;
}