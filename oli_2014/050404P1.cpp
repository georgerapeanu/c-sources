#include<fstream>
using namespace std;
ifstream f("jack.in");
ofstream g("jack.out");
int main()
{
    long long v=1,n,m=0;
    f>>n;
    if(n>=1&&n<=1000000000)
    {
    while(v<n)
    {
        v=v*2;
        m++;
    }
    g<<m;
    }
    else g<<"imposibil";
    f.close();g.close();
    return 0;
}
