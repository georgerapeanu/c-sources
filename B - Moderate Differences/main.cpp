#include <iostream>

using namespace std;
long long N,A,B,C,D;
bool ok(long long x,long long y)
{
    return min(x*D+y*C,y*D+x*C)<=B&&B<=max(x*D+y*C,y*D+x*C);
}
int main()
{
    cin>>N>>A>>B>>C>>D;
    B-=A;N-=1;
    for(long long x=0;x<=N;x++)
    {
        long long y=N-x;
        if(ok(x,y)){cout<<"YES";return 0;}
        if(ok(x,-y)){cout<<"YES";return 0;}
        if(ok(-x,y)){cout<<"YES";return 0;}
        if(ok(-x,-y)){cout<<"YES";return 0;}
    }
    cout<<"NO";
    return 0;
}
