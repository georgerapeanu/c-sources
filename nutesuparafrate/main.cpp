#include <fstream>
using namespace std;
FILE *f,*g;
int i,v[101],n,nr_arunc,aruncare,punct_a,punct_b,poz_a,poz_b;
bool rand;
short castigator;
int main()
{
    f=fopen("joc.in","r");
    fscanf(f,"%d",&n);
    for(i=1;i<=n;i++)
    fscanf(f,"%d",&v[i]);
    fscanf(f,"%d",&nr_arunc);
    poz_a=poz_b=1;
    for(i=1;i<=nr_arunc;i++)
    {
         fscanf(f,"%d",&aruncare);
         if(rand==0)
         {
             poz_a+=aruncare;
             if(poz_a>n)
             poz_a-=n;
             if(poz_a==1)
             {
                 castigator=1;
                 punct_a+=1;
                 break;
             }
             else if(v[poz_a]==0||poz_a==poz_b)
             {
                 poz_a=1;
                 punct_a=0;
             }
             else
             {
                 punct_a+=v[poz_a];
             }
         }
         else
         {
             poz_b+=aruncare;
             if(poz_b>n)
             poz_b-=n;
             if(v[poz_b]==0||poz_a==poz_b)
             {
                 poz_b=1;
                 punct_b=0;
             }
             else if(poz_b==1)
             {
                 castigator=2;
                 punct_b+=1;
                 break;
             }
             else
             {
                 punct_b+=v[poz_b];
             }
         }
         rand=1-rand;
    }
    fclose(f);
    if(castigator==0)
    {
        castigator= poz_a>poz_b ? 1:2;
    }
    g=fopen("joc.out","w");
    fprintf(g,"%d\n%d %d\n%d %d",castigator,poz_a,punct_a,poz_b,punct_b);
    return 0;
}
