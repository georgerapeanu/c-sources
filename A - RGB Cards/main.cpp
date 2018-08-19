#include <iostream>

using namespace std;
int a,b,c;
int main()
{
    cin>>a>>b>>c;
    cout<<((b*10+c)%4==0 ? "YES":"NO");
    return 0;
}
