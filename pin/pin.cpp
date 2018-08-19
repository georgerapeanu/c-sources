#include<fstream>
using namespace std;
ifstream f("pin.in");
ofstream g("pin.out");
int k,p;
int prim(int i)
{
    if(i<1)  return 0;
    else
    {
        for(int j=2;j<=i/2;j++)
        {
            if(i%j==0)  return 0;
        }
    }
    return 1;
}
int pin(int i)
{
    int a,b,c,d;
    a=i/1000;
    b=i/100%10;
    c=i/10%10;
    d=i%10;
    if(a!=k&&a!=p)
    {
        if(b!=k&&b!=p)
        {
            if(c!=k&&c!=p)
            {
                if(d!=k&&d!=p)
                    return 1;
                    else
                return 0;
            }
            else
                return 0;
        }
        else
                return 0;
    }
    else
                return 0;
}
int main()
{
    int i,l;
    f>>k>>p;
    for(i=1000;i<=9999;i++)
    {
        if(prim(i)&&pin(i))
        {
            l=i;
        }
    }
    g<<l;
    f.close();g.close();
    return 0;
}
