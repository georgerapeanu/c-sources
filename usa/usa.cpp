#include<fstream>
using namespace std;
ifstream f("usa.in");
ofstream g("usa.out");
int main()
{
    int n,maxi=0,uc,l;
    long mini=1000000000;
    f>>n;
    while(n!=0)
    {
        uc=n%10;
        n=n/10;
        if(uc>maxi)
            maxi=uc;
        if(uc<mini)
            mini=uc;
    }
    l=maxi*10+mini;
    g<<l;
    f.close();g.close();
    return 0;
}
