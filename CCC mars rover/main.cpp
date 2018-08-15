#include <iostream>
#include <cstdio>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;
double PI=acos(-1);
double degtorad(double x)
{
    return PI*x/180;
}
double radtodeg(double x)
{
    return 180*x/PI;
}
double level1(double wb,double sa)
{
    return wb/sin(degtorad(sa));
}
pair<pair<double,double>,double> level2(double wb,double dist,double sa)
{
    while(sa>=360)sa-=360;
    while(sa<0)sa+=360;
    if(sa==0)return {{0,dist},0};
    double R=level1(wb,sa);
    double an=dist/R;
    while(an<0)an+=2*PI;
    return {{R*(1-cos(an)),R*sin(an)},radtodeg(an)};
}
pair<double,double> rotorar(pair<double,double> a,double an)
{
    pair<double,double> rez;
    an=degtorad(an);
    rez.first=cos(an)*a.first+sin(an)*a.second;
    rez.second=-sin(an)*a.first+cos(an)*a.second;
    return rez;
}
pair<double,double> rottrig(pair<double,double> a,double an)
{
    return rotorar(a,360-an);
}
pair<pair<double,double>,double> level3(double wb,int N,vector<pair<double,double> > V)
{
    pair<pair<double,double>,double> ans={{0,0},0};
    for(auto it:V)
    {
        pair<pair<double,double>,double> tmp=level2(wb,it.first,it.second);
        tmp.first=rotorar(tmp.first,ans.second);
        ans.first.first+=tmp.first.first;
        ans.first.second+=tmp.first.second;
        ans.second+=tmp.second;
        while(ans.second<0)ans.second+=360;
        while(ans.second>=360)ans.second-=360;
    }
    return ans;
}
double wb,dist,sa,N;
vector<pair<double,double> > V;
int main()
{
    freopen("out","w",stdout);
    freopen("in","r",stdin);
    cin>>wb>>N;
    for(int i=1;i<=N;i++)
    {
        pair<double,double> tmp;
        cin>>tmp.first>>tmp.second;
        V.push_back(tmp);
    }
    pair<pair<double,double>,double> tmp=level3(wb,N,V);
    cout<<fixed<<setprecision(2)<<tmp.first.first<<" "<<tmp.first.second<<" "<<tmp.second;
    return 0;
}
