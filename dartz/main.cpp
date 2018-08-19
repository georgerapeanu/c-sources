#include <fstream>
using namespace std;
ifstream f("dartz.in");
ofstream g("dartz.out");
long long a,b,s;
int main()
{
    f>>s;
    s/=2;
    b=505;
    for(a=1;a*(a+1)*(a+2)<=s;a++)
    {
        while(b*(b+1)*(b+2)>s-a*(a+1)*(a+2))b--;
        if(b*(b+1)*(b+2)+a*(a+1)*(a+2)==s)break;
    }
    g<<a<<" "<<b<<" "<<a<<" "<<b;
    f.close();
    g.close();
    return 0;
}
