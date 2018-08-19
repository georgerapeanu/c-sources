#include <iostream>
using namespace std;
int N;
int V[105];
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)cin>>V[i];
    int i=1;
    while(i<N&&V[i]<V[i+1])i++;
    while(i<N&&V[i]==V[i+1])i++;
    while(i<N&&V[i]>V[i+1])i++;
    if(i<N)cout<<"NO";
    else cout<<"YES";
    return 0;
}
