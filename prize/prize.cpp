#include<fstream>
using namespace std;
ifstream f("prize.in");
ofstream g("prize.out");
int main()
{
    long long i,n,p,s=0;
    f>>n;
    for(i=1;i<n;i++)
    {
        f>>p;
        s+=p-1;
    }
    f>>p;
    s+=p;
    g<<s;
    f.close();g.close();
    return 0;
}
