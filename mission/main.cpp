#include <iostream>
#include <cstdio>
#include <algorithm>
#define NMAX 1005
#define PI 3.14159265
#define x first.first
#define y first.second
#define ind second
using namespace std;
typedef struct  pair<pair<long long,long long>,long> point;
point st[NMAX];
bool viz[NMAX];
point P[NMAX];
int N,l;
bool cmp(point a,point b)
{
    if(a.x!=b.x)
        return a.x<b.x;
    return a.y<b.y;
}
short orient(point p1,point p2,point p3)
{
    long long nr=(p2.y-p1.y)*(p3.x-p2.x)-(p3.y-p2.y)*(p2.x-p1.x);
    if(nr<0)
        return -1;
    if(nr>0)
        return 1;
    return 0;
}
int main()
{
    freopen("mission.in","r",stdin);
    freopen("mission.out","w",stdout);
    cin>>N;
    for(int i=0;i<N;i++)
    {
        cin>>P[i].x>>P[i].y;
        P[i].ind=i;
    }
    sort(P,P+N,cmp);
    st[0]=P[0];
    st[1]=P[1];
    l=1;
    for(int i=2;i<N;i++)
    {
        while(l>=1&&orient(st[l-1],st[l],P[i])>0)
        {
            l--;
        }
        st[++l]=P[i];
    }
   for(int i=0;i<=l;i++)
        viz[st[i].ind]=1;
    for(int i=N-1;i>=0;i--)
    {
        if(!viz[P[i].ind])
        {
            st[++l]=P[i];
        }
    }
    int incep=0;
    while(st[incep].ind!=0)
        incep++;
    for(int i=incep;i<N;i++)
        cout<<st[i].ind<<" ";
    for(int i=0;i<incep;i++)
        cout<<st[i].ind<<" ";
    return 0;
}
