#include <fstream>
using namespace std;
ifstream f("cifre.in");
ofstream g("cifre.out");
long long int c,n,nrapariti,d=1,z,uc;
int main()
{
    f>>n>>c;
    while(n>=c)
    {
        uc=n%10;n=n/10;
        if(uc>c)
        {
            nrapariti+=(n+1)*d;z=z+uc*d;d=d*10;
        }
        else if(uc==c)
        {
            nrapariti+=n*d+z+1;z=z+uc*d;d=d*10;
        }
        else
        {
            nrapariti+=n*d;z=z+uc*d;d=d*10;
        }
    }
    g<<nrapariti;
    return 0;
}
