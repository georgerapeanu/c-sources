#include <fstream>
using namespace std;
ifstream f("Input.in");
ofstream g("Output.out");
long long n,c1,c2,i,l,uc,on;
int main()
{
    f>>n>>c1>>c2;
    while(c1!=0||c2!=0||n!=0)
    {
        l=1;on=0;
        while(n!=0)
        {
            uc=n%10;
            n=n/10;
            if(uc==c1)
            {
                on=on+c2*l;
                l=l*10;
            }
            else
            {
                on=on+l*uc;
                l=l*10;
            }
        }
        g<<on<<"\n";
        f>>n>>c1>>c2;
    }
    f.close();g.close();
    return 0;
}
