#include <cstdio>
#include <cstring>
#include <map>
using namespace std;
FILE *f=fopen("degrade.in","r"),*g=fopen("degrade.out","w");
char c[100050];
int i,maxim,nrmax,lg,n;
map <char,int> ORD;
int main()
{
       fgets(c,30,f);
       n=strlen(c);
       for(i=0;i<n;i++)
       {
           ORD[c[i]]=i;
       }
       fgets(c,100050,f);
       n=strlen(c);
       lg=maxim=nrmax=1;
       for(i=1;i<n;i++)
       {
           if(ORD[c[i-1]]<=ORD[c[i]])
               lg++;
            else
            {
                if(lg==maxim)
                {
                    nrmax++;
                }
                else if(lg>maxim)
                {
                    maxim=lg;
                    nrmax=1;
                }
                lg=1;
            }
       }
       fprintf(g,"%d %d",maxim,nrmax);
       fclose(f);
       fclose(g);
       return 0;
}
