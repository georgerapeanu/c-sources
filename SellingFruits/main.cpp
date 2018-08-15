#include <iostream>

using namespace std;
class SellingFruits
{
public:
    int maxDays(int x,int f,int d,int p)
    {
        long long nr=max(0LL,(1LL*d-1LL*x*f)/(x+p));
        int rez=0;
        rez=max(min(f+nr-1,(d-1LL*(nr-1)*p)/x),1LL*rez);
        rez=max(min(f+nr,(d-1LL*nr*p)/x),1LL*rez);
        rez=max(min(f+nr+1,(d-1LL*(nr+1)*p)/x),1LL*rez);
        return rez;
    }
};
int main()
{
    SellingFruits a;
    cout<<a.maxDays(3,5,100,10);
    return 0;
}
