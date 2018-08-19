#include <iostream>
using namespace std;
int V[200005];
int sw[200005];
int N,swa;
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
        cin>>V[i];
    for(int i=1;i<=N-i+1;i++)
    {
        sw[i]++;
        sw[N-i+2]--;
    }
    for(int i=1;i<=N-i+1;i++)
    {
        swa+=sw[i];
        if(swa%2==1) swap(V[i],V[N-i+1]);
    }
    for(int i=1;i<=N;i++)
        cout<<V[i]<<" ";
    return 0;
}
