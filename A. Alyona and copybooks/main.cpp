#include <iostream>
using namespace std;
long long N,a,b,c,rez;
int main()
{
    cin>>N>>a>>b>>c;
    if(N%4==0)
    {
        cout<<0;
    }
    else if(N%4==1)
    {
        rez=3*a;
        rez=min(rez,b+a);
        rez=min(rez,c);
        cout<<rez;
    }
    else if(N%4==2)
    {
        rez=2*a;
        rez=min(rez,b);
        rez=min(rez,2*c);
        rez=min(rez,3*a+c);
        cout<<rez;
    }
    else
    {
        rez=a;
        rez=min(rez,b+c);
        rez=min(rez,3*c);
        cout<<rez;
    }
    return 0;
}
