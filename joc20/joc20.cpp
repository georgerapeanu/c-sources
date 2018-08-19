#include<fstream>
#include<iostream>
using namespace std;
ifstream f("joc20.in");
ofstream g("joc20.out");
int n,a,t,v[1000],vec,i,sf,in;
int main()
{
    f>>n;sf=n-1;
    for(i=0;i<n;i++)
    {
        f>>v[i];
    }
    in=0;
    for(i=0;i<n;i++)
    {
        f>>vec;
        if(vec==1)
        {
            if(i%2==0)
            {
               a+=v[in];
            }
            else
            {
                t+=v[in];
            }
            in++;
        }
        else
        {
            if(i%2==0)
            {
               a+=v[sf];
            }
            else
            {
                t+=v[sf];
            }
            sf--;
        }
    }
    if(a>t)
    {
        g<<a<<" 1";
    }
    else if(t>a)
    {
        g<<t<<" 2";
    }
    else
    {
        g<<a<<" 0";
    }
  f.close();g.close();
  return 0;
}
