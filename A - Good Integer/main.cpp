#include <iostream>

using namespace std;
int N;
int main()
{
    cin>>N;
    if(!N)cout<<"No";
    else if((N/10)%111==0||(N%1000)%111==0)cout<<"Yes";
    else cout<<"No";
    return 0;
}
