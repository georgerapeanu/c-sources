#include <iostream>
#include <algorithm>
using namespace std;
int N;
int V[100005];
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++) cin>>V[i];
    sort(V+1,V+1+N);
    for(int i=3;i<=N;i++)
    {
        if(V[i-2]+V[i-1]>V[i]) {cout<<"YES";return 0;}
    }
    cout<<"NO";
    return 0;
}
