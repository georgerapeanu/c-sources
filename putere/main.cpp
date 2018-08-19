#include <fstream>
#include <math.h>
using namespace std;
ifstream f("putere.in");
ofstream g("putere.out");
unsigned long long int n,m,uc,uc1,p,s,nr,ga;
int main()
{
    f>>m>>n;
    while(m!=0)
    {
        uc=n%10;n=n/10;uc1=m%10;m=m/10;
        nr=pow(uc1,uc);
        if(ga!=1)
        {
            p=pow(uc1,uc);ga=1;
        }
        s+=nr;
    }
    g<<p<<"\n"<<s;
    f.close();g.close();
    return 0;
}
