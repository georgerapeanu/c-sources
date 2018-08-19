#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <cmath>
using namespace std;
vector<pair<int,int> > F;
int L[200005];
int X1,X2,Y1,Y2;
int N;
long double PI=3.141592653589793238;
int main()
{
    cin>>X1>>Y1>>X2>>Y2;
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        int x,y;
        cin>>x>>y;
        if(min(X1,X2)<=x&&x<=max(X1,X2)&&min(Y1,Y2)<=y&&y<=max(Y1,Y2))
        {
            F.push_back({x,y});
        }
    }
    if(X1>X2){swap(X1,X2);swap(Y1,Y2);}
    if(Y1>Y2)
    {
        for(int i=0;i<F.size();i++)
        {
            F[i].second=-F[i].second;
        }
        Y1*=-1;
        Y2*=-1;
    }
    sort(F.begin(),F.end());
    int l=0;
    for(auto it:F)
    {
        int st=0,dr=l;
        while(st<dr)
        {
            int mid=(st+dr+1)/2;
            if(L[mid]<=it.second)st=mid;
            else dr=mid-1;
        }
        if(l==st)
        {
            l++;
            L[l]=it.second;
        }
        else
        {
            L[st+1]=min(L[st+1],it.second);
        }
    }
    long double rez=(abs(X1-X2)+abs(Y1-Y2))*100;
    if(l==min(abs(X1-X2),abs(Y1-Y2))+1)rez=rez-20*l+(l-1)*5*PI+10*PI;
    else                               rez=rez-20*l+5*PI*l;
    cout<<fixed<<setprecision(15)<<rez;
    return 0;
}
