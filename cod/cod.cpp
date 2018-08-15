#include<iostream>
#include<fstream>
using namespace std;
ifstream f("cod.in");
ofstream g("cod.out");
int main()
{
    int uc,s=0;
    long n;
    f>>n;
    while(n!=0)
    {
        uc=n%10;
        n=n/10;
        s=s+uc;
        g<<s<<" ";
    }
    f.close();g.close();
    return 0;
}
