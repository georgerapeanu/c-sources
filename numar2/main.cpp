#include <fstream>
using namespace std;
ifstream f("numar2.in");
ofstream g("numar2.out");
unsigned long long int primc,uc,n,a,i,nrmaxim,b,c=1,gasit;
int main()
{
    f>>n;
    a=i*i*i;
    if(n>9)
    {
    while(a<=n)
    {
        c=1;
        b=a;
        while(b!=0)
        {
            b=b/10;
            c*=10;
        }
        c=c/10;
        b=a;
        while(b!=0)
        {
            gasit=0;
            primc=b/c;
            uc=b%10;
            b=b%c;
            b=b/10;
            c=c/100;
            if(primc!=uc)
               {
                   gasit=1;
                   break;
               }
        }
        if(gasit==0)
        nrmaxim=a;
        i++;
        a=i*i*i;
    }
    }
    else
    {
        if(n>=8)
        {
            nrmaxim=8;
        }
        else if(n>=1)
        nrmaxim=1;
        else
        nrmaxim=0;
    }
    g<<nrmaxim;
    f.close();g.close();
    return 0;
}
