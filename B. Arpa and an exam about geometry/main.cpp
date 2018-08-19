#include <iostream>
#include <algorithm>
#define x first
#define y second
using namespace std;
pair<long long,long long> V[4];
long long det(pair<long long,long long> a,pair<long long,long long> b,pair<long long,long long> c)
{
    return 1LL*a.x*b.y-1LL*a.x*c.y+1LL*b.x*c.y-1LL*b.x*a.y+1LL*c.x*a.y-1LL*c.x*b.y;
}
long long dist(pair<long long,long long> a,pair<long long,long long> b)
{
    return (b.x-a.x)*(b.x-a.x)+(b.y-a.y)*(b.y-a.y);
}
int main()
{
    for(long long i=1;i<=3;i++)cin>>V[i].x>>V[i].y;
    if(det(V[1],V[2],V[3])==0||dist(V[1],V[2])!=dist(V[2],V[3]))cout<<"No";
    else                      cout<<"Yes";
    return 0;
}
