#include <cstdio>
#include <set>
using namespace std;
FILE *f,*g;
set <int> co;
set <char> ap;
char c;
int n,i,nrmax,nr=1,cnr;
int main()
{
     f=fopen("text2.in","r");
     fscanf(f,"%d ",&n);
     for(i=1;i<=n;i++)
     {
         fscanf(f,"%c",&c);
         if(c=='*')
         {
             while(c=='*')
             {
                 fscanf(f,"%c",&c);
                 i++;
             }
             if(cnr>nrmax)
             {
                 nrmax=cnr;
                 co.clear();
                 co.insert(nr);
             }
             else if(cnr==nrmax)
             {
                 co.insert(nr);
             }
             cnr=0;
             nr++;
         }
         else
         {
             ap.insert(c);
             cnr++;
         }
     }
     fclose(f);
     g=fopen("text2.out","w");
     fprintf(g,"%d\n",co.size());
     for(set<int>::iterator it=co.begin();it!=co.end();it++)
     fprintf(g,"%d ",*it);
     fprintf(g,"\n%d",ap.size());
     fclose(g);
    return 0;
}
