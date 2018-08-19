#include <iostream>
#include <algorithm>
using namespace std;
int N,V[100005];
int minim=(1<<30);
int maxim=0;
int nr;
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>V[i];
        minim=min(V[i],minim);
        maxim=max(V[i],maxim);
    }
    for(int i=1;i<=N;i++)
        nr+=(minim<V[i]&&V[i]<maxim);
    cout<<nr;
    return 0;
}
