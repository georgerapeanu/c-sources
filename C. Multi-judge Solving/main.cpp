#include <iostream>
#include <algorithm>
using namespace std;
int N,rez;
long long K;
int V[1005];
int main()
{
    cin>>N>>K;
    for(int i=1;i<=N;i++)cin>>V[i];
    sort(V+1,V+1+N);
    for(int i=1;i<=N;i++)
    {
        if(V[i]<=2*K)K=max(K,0LL+V[i]);
        else
        {
            while(V[i]>2*K)
            {
                K*=2;
                rez++;
            }
            K=max(K,0LL+V[i]);
        }
    }
    cout<<rez;
    return 0;
}
