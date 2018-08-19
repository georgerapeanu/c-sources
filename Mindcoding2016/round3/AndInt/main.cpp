#include <iostream>
#define MOD 1000000007
using namespace std;
int N;
long long x,y;
int rez=0;
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>x>>y;
        rez=0;
        while(x<=y)
        {
            int p2=0;
            long long nx;
            while((1LL<<p2)<=x)
                p2++;
            nx=min(y,(1LL<<p2)-1);
            rez=(1LL*rez+(nx-x+1)*(nx-x+2)/2)%MOD;
            x=nx+1;
        }
        cout<<rez<<"\n";
    }
    return 0;
}
