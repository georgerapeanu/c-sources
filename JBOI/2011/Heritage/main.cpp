#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>
#define EPS (1e-9)
using namespace std;
struct{int x,y;} P[505];
int V[10];
long double X[505];
long double Y[505];
int N,M,v;
long double a,rez=1e9;
int j;
bool used[10];
vector<double>tmp,R;
long double arie(long double x1,long double y1,long double x2,long double y2)
{
    return abs((x2-x1)*(y2+y1)/2);
}
long double fi(long double x1,long double y1,long double x2,long double y2,long double x)
{
    long double a=y2-y1;
    long double b=x1-x2;
    long double c=x2*y1-x1*y2;
    return (-c-a*x)/b;
}
void btr(int pas,long double y,int suma)
{
    if(pas>=N)
    {
        if(rez>y)
        {
            rez=y;
            R.assign(tmp.begin(),tmp.end());
        }
        return ;
    }
    for(int i=1;i<=N;i++)
    {
        if(!used[i])
        {
            used[i]=1;
            tmp.push_back(X[suma+V[i]]);
            btr(pas+1,y+Y[suma+V[i]],suma+V[i]);
            tmp.pop_back();
            used[i]=0;
        }
    }
}
int main()
{
    cin>>N>>M;
    for(int i=1;i<=N;i++)
    {
        cin>>V[i];v+=V[i];
    }
    for(int i=1;i<=M;i++)
    {
        cin>>P[i].x>>P[i].y;
        if(i>1)a+=arie(P[i-1].x,P[i-1].y,P[i].x,P[i].y);
    }
    a/=v;
    X[1]=P[1].x;
    Y[1]=P[1].y;
    j=1;
    for(int i=2;i<=v;i++)
    {
        long double ca=a;
        X[i]=X[i-1];Y[i]=Y[i-1];
        while(arie(X[i],Y[i],P[j].x,P[j].y)<=ca)
        {
            ca-=arie(X[i],Y[i],P[j].x,P[j].y);
            X[i]=P[j].x;
            Y[i]=P[j].y;
            j++;
        }
        long double st,dr;
        st=X[i];
        dr=P[j].x;
        while(dr-st>EPS)
        {
            long double mid=(st+dr)/2;
            if(arie(X[i],Y[i],mid,fi(X[i],Y[i],P[j].x,P[j].y,mid))>=ca)dr=mid;
            else st=mid;
        }
        Y[i]=fi(X[i],Y[i],P[j].x,P[j].y,st);
        X[i]=st;
    }
    btr(1,0,1);
    cout<<fixed<<setprecision(5)<<rez<<"\n" ;
    for(auto it:R)
        cout<<it<<" ";
    return 0;
}
