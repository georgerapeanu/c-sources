#include <fstream>
using namespace std;
ifstream f("triunghi3.in");
ofstream g("triunghi3.out");
long long n,i,suma;
int logpow(int a,long long n)
{
    long long p=1;
    while(n)
    {
        if(n%2==1)
            {p*=a;p%=2011;}
        a*=a;
        a%=2011;
        n/=2;
    }
    return p;
}
int main()
{
    f>>n;
    g<<logpow(2,n)-2;
    f.close();
    g.close();
    return 0;
}
