#include <fstream>
#include <iostream>
using namespace std;
ifstream f("unupatru.in");
ofstream g("unupatru.out");
long long int s,x,n,i=1,uc,o;
int main()
{
    f>>n;
    while(i<=n)
    {
        f>>x;
        o=0;s=x;
        while((s!=1)&&(s!=4))
        {
            s=0;
            o++;
            while(x!=0)
            {
                uc=x%10;
                s+=uc*uc;
                x=x/10;
            }
            x=s;
        }
        g<<o<<" ";
        i++;
    }
    f.close();g.close();
    return 0;
}
