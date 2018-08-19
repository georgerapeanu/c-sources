#include<fstream>
#include<iostream>
using namespace std;
ifstream f("vistiernic.in");
ofstream g("vistiernic.out");
long i,n,a,nr2,nr5,l;
int main()
{
    f>>n;
    for(i=1;i<=n;i++)
    {
        f>>a;
        while(a%5==0)
        {
            a=a/5;
            nr5++;
        }
        while(a%2==0)
        {
            a=a/2;
            nr2++;
        }
    }
    cout<<nr5<<" "<<nr2;
    if(nr2<nr5)
        g<<nr2;
    else
        g<<nr5;
    return 0;
}
