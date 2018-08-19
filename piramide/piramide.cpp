#include<fstream>
using namespace std;
ifstream f("piramide.in");
ofstream g("piramide.out");
int main()
{
    long long n,x,k,p=0,m=0,c,a,nrcart=0,cart=3,cart2=3,nr,nrmax=0,inceput=1,sfarsit=3,pmax=0;
    f>>n>>x>>k>>a;
    while(nrcart+cart<=n)
    {
        nr=0;
        nrcart+=cart;
        m++;
        while(inceput<=a&&a<=sfarsit)
        {
            nr++;
            f>>a;
        }
        if(nr>nrmax)
        {
            nrmax=nr;pmax=m;
        }
        if(nrcart>x&&p==0)
        {
            p=m;
        }
        inceput+=cart;
        cart=cart+cart2;
        sfarsit+=cart;
        cart2++;
        }
    c=n-nrcart;
    g<<p<<"\n"<<m<<"\n"<<c<<"\n"<<pmax;
    return 0;
}


