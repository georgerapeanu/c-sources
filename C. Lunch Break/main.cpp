#include <iostream>

using namespace std;
int T,a,b,c;
int main()
{
    cin>>T;
    while(T--)
    {
        cin>>a>>b>>c;
        if(a<b&&a<c)cout<<"First\n";
        else if(b<a&&b<c)cout<<"Second\n";
        else cout<<"Third\n";
    }
    return 0;
}
