#include <iostream>
using namespace std;
int rez;
int V[105];
int N;
int maxim;
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++) cin>>V[i],maxim=max(maxim,V[i]);
    for(int i=1;i<=N;i++) rez+=maxim-V[i];
    cout<<rez;
    return 0;
}
