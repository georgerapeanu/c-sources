#include <fstream>
using namespace std;
ifstream f("covor.in");
ofstream g("covor.out");
long long n,k,i,nr,nrromburi,elem,felem,gasit,s,j;
int c;
int main()
{
    f>>n>>k>>c;
    i=1;nr=4;s=7;
    while(nr<n)
    {
        nr=nr+s;
        s=s+4;
        i++;
    }
    nrromburi=i-1;
    nr=nr-s+4;
    if(c==1)
    g<<nrromburi;
    else
    {
        if(nr<k)
        g<<0;
        else
        {
       felem=1;
       for(i=1;i<=nrromburi;i++)
       {
           s=1+nr+i;
           elem=felem+ i*2;
           for(j=felem;j<=elem;j++)
           {
               if(j==elem||j==felem)
               {
                   if(j==k)
                   {
                       g<<i;gasit=1;break;
                   }
               }
               else
               {
                   if(j==k||(s-j)==k)
                   {
                       g<<i;gasit=1;break;
                   }
               }
           }
           if(gasit==1)
           break;
           felem=elem;
       }
        }
    }
    f.close();g.close();
    return 0;
}
