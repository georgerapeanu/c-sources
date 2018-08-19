#include <iostream>

using namespace std;
int a,b,c;
int main()
{
    cin>>a>>b>>c;
    int minim=min(min(a,b/2),c/4);
    cout<<7*minim;
    return 0;
}
