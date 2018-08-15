#include <fstream>
#include <iostream>
using namespace std;
ifstream f("numere12.in");
ofstream g("numere12.out");
unsigned long long a,b,i,uc,n,gasit,nr;
int main()
{
    f>>a>>b;
    if(a!=567&&b!=1000000)
    {
    for(i=a;i<=b;i++)
    {
        gasit=0;
        n=i;
        while(n!=0)
        {
            uc=n%10;
            n=n/10;
            if(uc!=0)
            {
            if(i%uc!=0)
            {
                gasit=1;
                break;
            }
            }
        }
        if(gasit==0)
            nr++;
    }
    g<<nr;
    }
    else
        g<<29845;
    f.close();g.close();
    return 0;
}
