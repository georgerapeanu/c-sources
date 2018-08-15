#include <fstream>
using namespace std;
ifstream f("consiliu.in");
ofstream g("consiliu.out");
int i,n,hs,ms,hf,mf,v[1440],maxim,c,j;
int main()
{
    f>>n;
    maxim=n;
    for(i=1;i<=n;i++)
    {
        f>>hs>>ms>>hf>>mf;
       if(hs*60+ms==hf*60+mf)
        maxim--;
       else if(hs*60+ms<hf*60+mf)
       {
           for(j=hs*60+ms;j<hf*60+mf;j++)
           {
               v[j]++;
           }
       }
       else
       {
           for(j=hs*60+ms;j<1440;j++)
           {
               v[j]++;
           }
           for(j=0;j<hf*60+mf;j++)
           {
               v[j]++;
           }
       }
    }
    for(i=0;i<1440;i++)
    {
        if(v[i] == maxim)
            {c++;}
    }
    g<<c;
    f.close();g.close();
    return 0;
}
