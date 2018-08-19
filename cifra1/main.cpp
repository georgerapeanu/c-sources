#include <fstream>
#include <iostream>
using namespace std;
ifstream f("cifra1.in");
ofstream g("cifra1.out");
unsigned long long int n,m,s,c,cn,nrc,pc=1;
int main()
{
    f>>n>>m;cn=n;
    while(cn!=0)
    {
     c=cn%10;
     cn=cn/10;
     pc*=10;
    }
    nrc=nrc/10;
    while(s<m)
    {
        c=n/pc;
        n=n%pc;
        pc=pc/10;
        nrc++;
        s+=c;
    }
    g<<c;
    return 0;
}
