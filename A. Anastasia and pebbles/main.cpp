#include <iostream>
using namespace std;
int S,V;
int K,N;
int main()
{
    cin>>N>>K;
    for(int i=1;i<=N;i++)
    {
        cin>>V;
        S+=(V/K+(V%K!=0));
    }
    S=S/2+S%2;
    cout<<S;
    return 0;
}
