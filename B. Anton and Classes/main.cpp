#include <iostream>
#include <algorithm>
#define NMAX 200005
#define x first
#define y second
using namespace std;
pair<int,int> A[NMAX],tmp;
pair<int,int> i1,i2;
int N,M,rez;
int gdist(pair<int,int> a,pair<int,int> b)
{
    if((a.x<=b.x&&b.y<=a.y)||(b.x<=a.x&&a.y<=b.y)||(a.x<=b.x&&a.y>=b.x)||(b.x<=a.x&&b.y>=a.x))
        return 0;
    return max(b.x-a.y,a.x-b.y);
}
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>A[i].x>>A[i].y;
    }
    cin>>M;
    i1.y=(1<<30);
    for(int i=1;i<=M;i++)
    {
        cin>>tmp.x>>tmp.y;
        if(tmp.y<i1.y)
            i1=tmp;
        if(tmp.x>i2.x)
            i2=tmp;
    }
    for(int i=1;i<=N;i++)
    {
        rez=max(rez,max(gdist(A[i],i1),gdist(A[i],i2)));
    }
    cout<<rez;
    return 0;
}
