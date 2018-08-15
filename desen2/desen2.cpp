#include<fstream>
#include<iostream>
using namespace std;
ifstream f("desen2.in");
ofstream g("desen2.out");
unsigned long long a,b,r,cmmmc,ca,cb;
int main()
{
    f>>a>>b;cmmmc=a*b;ca=a;cb=b;
    r=a%b;
    while(r)
    {
        a=b;
        b=r;
        r=a%b;
    }
    cmmmc=cmmmc/b;
    g<<cmmmc<<"\n"<<((cmmmc*cmmmc)/(ca*cb));
    f.close();g.close();
    return 0;
}
