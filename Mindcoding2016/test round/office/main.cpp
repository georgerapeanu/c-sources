#include <iostream>
using namespace std;
int N;
int main()
{
    cin>>N;
    if(N%4==0||N%4==3)cout<<15;
    else cout<<16;
    return 0;
}
