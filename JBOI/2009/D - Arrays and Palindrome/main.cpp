#include <iostream>
using namespace std;
int N,M;
int A[100005];
int p[3];
int main()
{
    cin>>N>>M;
    for(int i=1;i<=M;i++)
    {
        cin>>A[i];
        if(A[i]%2==1)
        {
            p[0]++;
            if(p[0]>2){cout<<"Impossible";return 0;}
            p[p[0]]=i;
        }
    }
    if(p[1])swap(A[1],A[p[1]]);
    if(p[2])swap(A[M],A[p[2]]);
    for(int i=1;i<=M;i++)cout<<A[i]<<" ";cout<<"\n";
    if(M==1)
    {
        if(A[1]==1)cout<<"1\n1";
        else cout<<"2\n"<<A[1]-1<<" "<<1;
        return 0;
    }
    cout<<M-(A[1]==1)<<"\n";
    for(int i=1;i<=M;i++)
    {
        if(i==1&&A[i]==1)continue;
        cout<<A[i]-(i==1)+(i==M)<<" ";
    }
    return 0;
}
