#include <fstream>
#include <iostream>
using namespace std;
ifstream f("ordine.in");
ofstream g("ordine.out");
long afis[250001],i,j,n,v[250001];
int c;
void ordine1(void)
{
    afis[1]=1;
}
int main()
{
    ordine1();
    cout<<afis[1];
    //f>>n;
  /*  for(i=1;i<=n;i++)
    {
        f>>v[i];
    }
    f>>c;
    if(c==1)
    {
        if(n%2==1)
        g<<v[n/2+1];
        else
        g<<v[n];
    }
    else
    {
        long long afis[250001];
        for(i=n;i>=1;i--)
        {
            if(i%2==1)
            {
                afis[i]=v[i/2+1];
                for(j=i/2+1;j<=n;j++)
                {
                    v[j]=v[j+1];
                }
            }
            else
            afis[i]=v[i];
        }
        for(i=1;i<=n;i++)
        g<<afis[i]<<" ";*/
   //     ordine();
   // }
    f.close();g.close();
    return 0;
}
