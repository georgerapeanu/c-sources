#include <iostream>
#include <vector>
#include <algorithm>
#define rad 334
using namespace std;
int R[100005];
int K;
int X,T,A,TI;
int Q;
int sens=-1;
int ind=0;
pair<int,int> a,b;
int main()
{
    cin>>X>>K;
    a.first=b.first=0;
    a.second=b.second=X;
    for(int i=1;i<=K;i++)cin>>R[i];
    cin>>Q;
    for(int i=1;i<=Q;i++)
    {
        cin>>T>>A;
        while(ind<K&&R[ind+1]<T)
        {
            a.first+=sens*(R[ind+1]-TI);
            a.second+=sens*(R[ind+1]-TI);
            b.first+=max(0,-a.first);
            b.second-=max(0,a.second-X);
            a.first=max(0,a.first);a.first=min(X,a.first);
            a.second=max(0,a.second);a.second=min(X,a.second);
            sens*=-1;
            TI=R[ind+1];
            ind++;
        }
        a.first+=sens*(T-TI);
        a.second+=sens*(T-TI);
        b.first+=max(0,-a.first);
        b.second-=max(0,a.second-X);
        b.first=min(b.first,b.second);
        a.first=max(0,a.first);a.first=min(X,a.first);
        a.second=max(0,a.second);a.second=min(X,a.second);
        TI=T;
        cout<<min(max(A,b.first),b.second)-b.first+a.first;
        cout<<"\n";
    }
    return 0;
}
