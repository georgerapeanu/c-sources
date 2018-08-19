#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;
int N,S;
long double st=1e9,dr=1e9,t;
int X[100005],dir[100005],V[100005];
long double eval(int x)
{
    if(x<0||x>1000000)return 1e9;
    long double tmp,drmin=1e9,stmin=1e9;
    for(int i=1;i<=N;i++)
    {
        if(dir[i]==1)
        {
            tmp=((long double)X[i])/V[i];
        }
        else
        {
            tmp=((long double)(1e6-X[i]))/V[i];
        }
        long double t=0;
        if(dir[i]==1)
        {
            if(X[i]>x)
            {
                t=1e9;
            }
            else
            {
                t=((long double)(x-X[i]))/(S-V[i]);
                if(x-S*t>=0)
                {
                    t+=(x-S*t)/(V[i]+S);
                }
                else
                    t=1e9;
            }
        }
        else
        {
             if(X[i]<x)
             {
                 t=1e9;
             }
             else
             {
                 t=((long double)(X[i]-x))/(S-V[i]);
                 if(x+S*t<=1e6)
                 {
                    t+=(1e6-(x+S*t))/(V[i]+S);
                 }
                 else
                    t=1e9;
             }
        }
        tmp=min(tmp,t);
        if(dir[i]==1)stmin=min(stmin,tmp);
        else drmin=min(drmin,tmp);
    }
    return max(stmin,drmin);
}
int main()
{
    cin>>N>>S;
    for(int i=1;i<=N;i++)
    {
        cin>>X[i]>>V[i]>>dir[i];
    }
    int poz=0;
    long double cost=eval(poz);
    bool scade=1;
    for(int l=1<<20;l;l>>=scade)
    {
        scade=1;
        long double c1=eval(poz-l);
        long double c2=eval(poz+l);
        if(c1<cost&&c2>=c1){cost=c1;poz-=l;scade=0;}
        else if(c2<cost&&c2<=c1){poz+=l;cost=c2;scade=0;}
    }
    cout<<fixed<<setprecision(10)<<cost;
    return 0;
}
