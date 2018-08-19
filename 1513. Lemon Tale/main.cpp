#include <iostream>
#include <vector>
#define BASE 1000000000
using namespace std;
int N,K;
vector <int> D[10005];
vector <int> mul(int val,vector<int> a)
{
    vector <int> c(a.size());
    for(int i=a.size()-1;i>=0;i--)
    {
        c[i]=a[i]*2;
    }
    int t=0,n=c.size();
    for(int i=0;i<n||t;i++)
    {
        if(i<n)
        {
            c[i]+=t;
            t=c[i]/BASE;
            c[i]%=BASE;
        }
        else
        {
            c.push_back(t);
            t/=BASE;
        }
    }
    return c;
}
vector <int> add(vector<int> a,vector <int> b)
{
    vector <int> c;
    int n=max(a.size(),b.size());
    int t=0;
    for(int i=0;i<n||t;i++)
    {
        c.push_back((a.size()<=i ? 0:a[i])+(b.size()<=i ? 0:b[i])+t);
        t=c[i]/BASE;
        c[i]%=BASE;
    }
    return c;
}
vector <int> scad(vector <int> a,vector<int> b)
{
    vector <int> c(a.size());
    int n=c.size();
    int t=0;
    for(int i=0;i<n||t;i++)
    {
        c[i]=a[i]-(i>=b.size() ? 0:b[i])-t;
        t=0;
        if(c[i]<0)
        {
            t=1;
            c[i]+=BASE;
        }
    }
    while(c.size()>1&&c.back()==0)
        c.pop_back();
    return c;
}
int main()
{
    cin>>N>>K;
    D[0].push_back(1);
    for(int i=1;i<=K;i++)
    {
        D[i]=mul(2,D[i-1]);
    }
    for(int i=1;i<=K;i++)
    {
        D[i]=add(D[i-1],D[i]);
    }
    D[K+1]=mul(2,D[K]);
    for(int i=K+2;i<=N;i++)
    {
        D[i]=add(D[i-1],scad(D[i-1],D[i-K-2]));
    }
    D[N]=scad(D[N],D[N-1]);
    for(vector<int> :: reverse_iterator it=D[N].rbegin();it!=D[N].rend();it++)
    {
        int cb=BASE/10;
        if(it!=D[N].rbegin())
        {
            while(cb!=1&&*(it)<cb)
            {
                cout<<0;cb/=10;
            }
        }
        cout<<*it;
    }
    return 0;
}
