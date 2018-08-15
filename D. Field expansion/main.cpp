#include <iostream>
#include <algorithm>
#define tp long long
using namespace std;
tp A[100005];
tp N,h,w,a,b;
tp rez=(1<<30);
tp solve(tp h,tp w,tp a,tp b)
{
    tp i=N,nr=0;
    for(;i&&(h<a||w<b);i--)
    {
        nr++;
        if(a/h<b/w)
        {
            w*=A[i];
        }
        else
        {
            h*=A[i];
        }
    }
    if((h<a||w<b))
        return 1<<30;
    return nr;
}
void btr(tp pas,tp cost,tp h,tp w,tp a,tp b)
{
    if(pas>N)
    {
        if(h>=a&&w>=b)
            rez=min(rez,cost);
        return ;
    }
    btr(pas+1,cost,h,w,a,b);
    if(h<a)btr(pas+1,cost+1,h*A[pas],w,a,b);
    if(w<b)btr(pas+1,cost+1,h,w*A[pas],a,b);
}
int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    cin>>a>>b>>h>>w>>N;
    for(int i=1;i<=N;i++)
        cin>>A[i];
    sort(A+1,A+1+N);
    if(N>=9)
    {
        tp rez=min(min(solve(h,w,a,b),solve(h,w,b,a)),min(solve(w,h,a,b),solve(w,h,b,a)));
        if(rez==(1<<30))cout<<-1;
        else cout<<rez;
    }
    else
    {
        btr(1,0,h,w,a,b);
        btr(1,0,h,w,b,a);
        if(rez==(1<<30))cout<<-1;
        else cout<<rez;
    }
    return 0;
}
