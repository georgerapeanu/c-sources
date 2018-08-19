#include <algorithm>
#include <iostream>
using namespace std;
int V[205];
int N;
int main()
{
    cin>>N;
    for(int i=1;i<=2*N;i++)cin>>V[i];
    sort(V+1,V+1+2*N);
    cout<<(V[N]!=V[N+1] ? "YES":"NO");
    return 0;
}
