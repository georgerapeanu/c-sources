#include <iostream>

using namespace std;
int N,K,timp=240;
int main()
{
    cin>>N>>K;
    timp-=K;
    int i=1;
    while(i<=N&&5*i<=timp)
    {
        timp-=5*i;
        i++;
    }
    cout<<i-1;
    return 0;
}
