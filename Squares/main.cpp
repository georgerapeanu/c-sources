#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
#define EPS (1e-10)
using namespace std;
int N;
long double rez;
vector<pair<long double,long double> > V[13];
struct segm{
    long double a,b,c;
    pair<long double,long double> st,dr;
    segm(pair<long double,long double> S,pair<long double,long double> D)
    {
        st.first=min(S.first,D.first);
        dr.first=max(S.first,D.first);
        st.second=min(S.second,D.second);
        dr.second=max(S.second,D.second);
        a=D.second-S.second;
        b=S.first-D.first;
        c=S.second*D.first-S.first*D.second;
    }
    bool operator || (segm &other)
    {
        return a*other.b==other.a*b;
    }
};
pair<long double,long double> inter(segm a,segm b)
{
    if((a||b))return {-1005,-1005};
    long double y=(b.c*a.a-a.c*b.a)/(a.b*b.a-b.b*a.a);
    long double x=(b.c*a.b-a.c*b.b)/(b.b*a.a-a.b*b.a);
    if(a.st.first<=x&&a.dr.first>=x&&b.st.first<=x&&x<=b.dr.first)return {x,y};
    return {-1005,-1005};
}
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
    sort(V.begin(),V.end(),cmp);
    long double A=0;
    for(int i=0;i<V.size();i++)
    {
        A+=det(V[0],V[i],V[(i+1)%V.size()]);
    }
    A=abs(A/2);
    return A;
}
bool inside(pair<long double,long double> P,vector<pair<long double,long double> > tmp)
{
    long double A=arie(tmp);
    for(int i=0;i<tmp.size();i++)
    {
        A-=abs(det(P,tmp[i],tmp[(i+1)%tmp.size()])/2);
    }
    return (-EPS<A&&A<EPS);
}
long long corekt(long double ceva)
{
    if(ceva-(long long)ceva-0.5<EPS)return (long long)ceva;
    else return 1+(long long)ceva;
}
int main()
{
    freopen("squares.in","r",stdin);
    freopen("squares.out","w",stdout);
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        long double x1,y1,x2,y2;
        cin>>x1>>y1>>x2>>y2;
        x2-=x1;y2-=y1;
        V[i].push_back({x2,y2});
        V[i].push_back({-y2,x2});
        V[i].push_back({-x2,-y2});
        V[i].push_back({y2,-x2});
        sort(V[i].begin(),V[i].end(),cmp);
        for(auto &it:V[i]){it.first+=x1;it.second+=y1;}
    }
    for(int conf=1;conf<(1<<N);conf++)
    {
        int sgn=-1;
        vector<pair<long double,long double> >tmp,real;tmp.clear();real.clear();
        for(int i=0;i<N;i++)
        {
            if((conf>>i)&1)
            {
                for(auto it:V[i+1])tmp.push_back(it);sgn*=-1;
                for(int j=i+1;j<N;j++)
                {
                    if((conf>>j)&1)
                    {
                        for(int k=0;k<4;k++)
                        {
                            for(int l=0;l<4;l++)
                            {
                                pair<long double,long double> ceva=inter(segm(V[i+1][k],V[i+1][(k+1)%4]),segm(V[j+1][l],V[j+1][(l+1)%4]));
                                if(ceva!=make_pair((long double)-1005,(long double)-1005))tmp.push_back(ceva);
                            }
                        }
                    }
                }
            }
        }
        for(auto it:tmp)
        {
            bool ok=1;
            for(int i=0;i<N;i++)
            {
                if((conf>>i)&1)
                {
                    if(!inside(it,V[i+1])){ok=0;break;}
                }
            }
            if(ok)real.push_back(it);
        }
        rez+=sgn*arie(real);
    }
    cout<<corekt(rez);
    return 0;
}
