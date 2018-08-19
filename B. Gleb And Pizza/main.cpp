#include <iostream>
#include <cmath>
using namespace std;
int D,R;
int N;
int nr;
long double dist(int x,int y)
{
    long double tmp=1LL*x*x+1LL*y*y;
    return sqrt(tmp);
}
int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    cin>>R>>D>>N;
    for(int i=1;i<=N;i++)
    {
        int x,y,r;
        cin>>x>>y>>r;
        long double tmp=dist(x,y);
        if(R-D<=tmp-r&&tmp+r<=R)nr++;
    }
    cout<<nr;
    return 0;
}
