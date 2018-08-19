#include <iostream>

using namespace std;
int N;
int L,T,va,vb,ta,tb;
int c,st,d;
int main()
{
    cin>>L>>T>>va>>vb;
    ta=tb=T;
    cin>>N;
    while(N)
    {
        cin>>c>>st>>d;
        if(c==1)
            ta-=d;
        else
            tb-=d;
        N--;
    }
    cout<<(ta*va+tb*vb)/L;
    return 0;
}
