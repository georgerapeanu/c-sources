#include <iostream>

using namespace std;
long long rez;
int l[55];
int r[55];
int N,M;
int main()
{
    cin>>N>>M;
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=M;j++)
        {
            int val;
            cin>>val;
            l[i]+=val;
            r[j]+=val;
        }
    }
    for(int i=1;i<=N;i++)
        rez+=((1LL<<l[i])-1)+((1LL<<(M-l[i]))-1);
    for(int i=1;i<=M;i++)
        rez+=((1LL<<r[i])-1)+((1LL<<(N-r[i]))-1);
    cout<<rez-N*M;
    return 0;
}
