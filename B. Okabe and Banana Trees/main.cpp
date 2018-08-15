#include <iostream>
using namespace std;
long long m,b;
long long lastx;
long long rez;
long long x,y;
int main()
{
    cin>>m>>b;
    lastx=b*m;
    for(long long x=0;x<=lastx;x+=m)
    {
        y=-x/m+b;
        rez=max(rez,(y*(y+1)/2)*(x+1)+(x*(x+1)/2)*(y+1));
    }
    cout<<rez;
    return 0;
}
