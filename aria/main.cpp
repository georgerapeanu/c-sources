#include <fstream>
#include <iomanip>
#include <cmath>
#include <algorithm>
#include <vector>
using namespace std;
ifstream f("aria.in");
ofstream g("aria.out");
vector<pair<long double,long double> >V;
int N;
long double rez;
long double det(pair<long double,long double> a,pair<long double,long double> b,pair<long double,long double> c)
{
    return a.first*b.second+b.first*c.second+c.first*a.second-a.first*c.second-b.first*a.second-c.first*b.second;
}
bool cmp(pair<long double,long double> a,pair<long double,long double> b)
{
    return atan2(a.second,a.first)<atan2(b.second,b.first);
}
long double arie(vector<pair<long double,long double> > V)
{
    if(V.empty())return 0;
    long double gx=0,gy=0;
    for(int i=0;i<V.size();i++){gx+=V[i].first;gy+=V[i].second;}
    gx/=V.size();
    gy/=V.size();
    for(auto &it:V){it.first-=gx;it.second-=gy;}
    //sort(V.begin(),V.end(),cmp);
    long double A=0;
    for(int i=0;i<V.size();i++)
    {
        A+=det(V[0],V[i],V[(i+1)%V.size()]);
    }
    A=abs(A/2);
    return A;
}
int main()
{
    f.sync_with_stdio(false);
    g.sync_with_stdio(false);
    f>>N;
    for(int i=1;i<=N;i++)
    {
        long double x,y;
        f>>x>>y;
        V.push_back({x,y});
    }
    rez=arie(V);
    g<<fixed<<setprecision(7)<<rez;
    f.close();
    g.close();
    return 0;
}
