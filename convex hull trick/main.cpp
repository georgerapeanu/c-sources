#include <bits/stdc++.h>
using namespace std;
const long long is_query=1LL<<62;
struct Line
{
    long long m,b;
    mutable long long nxtm,nxtb;
    Line()
    {
        m=b=0;
        nxtm=0;
        nxtb=-is_query;
    }
    Line(long long nm,long long nb)
    {
        m=nm;
        b=nb;
        nxtm=0;
        nxtb=-is_query;
    }
    bool operator <(const Line &other)const
    {
        if(other.b==is_query)
        {
            if(nxtm==0&&nxtb==-is_query)return 0;
            return other.m*(m-nxtm)>(nxtb-b);
        }
        return m>other.m;
    }
};
struct Convex
{
    multiset<Line> S;
    bool bad(auto y)
    {
        multiset<Line> ::iterator z=next(y);
        if(y==S.begin())
        {
            if(z==S.end())return 0;
            return y->m==z->m&&y->b>=z->b;
        }
        multiset<Line> ::iterator x=prev(y);
        if(z==S.end())return x->m==y->m&&y->b>=x->b;
        return (y->b-x->b)*(y->m-z->m)>=(z->b-y->b)*(x->m-y->m);
    }
    void ins(Line a)
    {
        multiset<Line> ::iterator y=S.insert(a);
        if(bad(y)){S.erase(y);return ;}
        while(next(y)!=S.end()&&bad(next(y)))
            S.erase(next(y));
        while(y!=S.begin()&&bad(prev(y)))
            S.erase(prev(y));
        if(y!=S.begin())
        {
            prev(y)->nxtm=y->m;
            prev(y)->nxtb=y->b;
        }
        if(next(y)!=S.end())
        {
            y->nxtm=next(y)->m;
            y->nxtb=next(y)->b;
        }
    }
    long long eval(long long x)
    {
        if(S.empty())return 0;
        multiset<Line> ::iterator it=S.lower_bound(Line(x,is_query));
        if(it==S.end())
            it--;
        assert(it!=S.end());
        return it->m*x+it->b;
    }
}a;
int main()
{
    a.ins(Line(-2,-1));
    a.ins(Line(1,2));
    a.ins(Line(2,3));
    a.ins(Line(-1,2));
    a.ins(Line(2,-1));
    for(int i=-10;i<=10;i++)cout<<a.eval(i)<<" ";
}
