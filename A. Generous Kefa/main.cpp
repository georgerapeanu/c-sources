#include <iostream>
using namespace std;
int N,K;
int fr[280];
string a;
int main()
{
    cin>>N>>K>>a;
    for(auto it:a)fr[it]++;
    for(int i=0;i<280;i++)if(fr[i]>K){cout<<"NO";return 0;}
    cout<<"YES";
    return 0;
}
