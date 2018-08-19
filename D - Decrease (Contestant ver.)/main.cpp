#include <iostream>

using namespace std;
long long maxa=(1e16)+1000;
long long V[55];
long long K;
long long T[55];
int main()
{
    cin>>K;
    if(K==0)
    {
        cout<<"4\n3 3 3 3";
        return 0;
    }
    for(int i=1;i<=50;i++)
        T[i]=49+K/50;
    K%=50;
    for(int i=1;i<=K;i++)
    {
        T[i]+=51;
        for(int j=1;j<=50;j++)T[j]--;
    }
    cout<<50<<"\n";
    for(int i=1;i<=50;i++)cout<<T[i]<<" ";
    return 0;
}
